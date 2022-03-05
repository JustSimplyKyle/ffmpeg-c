//general
#include <iostream>
#include <string>
//for exec command
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdio>

using std::string;
using std::cout;
using std::cin;
using std::endl;

void exec_print(const char* cmd, const string& error_message="Error!") {
    std::array<char, 64> buffer;
    string result;

    auto pipe = popen(cmd, "r"); // get rid of shared_ptr

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), 64, pipe) != nullptr) {
            result += buffer.data();
            cout << result;
        }
    }

    auto rc = pclose(pipe);

    if (rc != EXIT_SUCCESS) { // == 0
        throw std::runtime_error(error_message);
    }
}

void convert_into_another(){
    cout << "Select a file to convert.(Including file extensions)\n";
    string file_name;
    cin.ignore();
    std::getline(cin,file_name);
    file_name='\"'+file_name+'\"';
    cout.flush();
    cout << "Select a format to convert to(filename extensions).\n";
    string format;
    cin >> format;
    string command = "ffmpeg -i " + file_name + " " + file_name.substr(file_name.find_last_of(".")+ 1) + "_converted." + format;
    exec_print(command.c_str());
}

void extract_audio(){
    cout << "Select a file to extract audio from.(Including file extensions)\n";
    string file_name;
    cin.ignore();
    std::getline(cin,file_name);
    file_name='\"'+file_name+'\"';
    cout << "Do you want to re-encode the audio?(y/n)\n";
    string re_encode;
    cin >> re_encode;
    if(re_encode == "y"){
        cout << "Select a format to convert to(filename extensions).\n";
        string format;
        cin >> format;
        string command = "ffmpeg -i " + file_name + " -map 0:a " + file_name.substr(file_name.find_last_of(".")+ 1) + "_converted." + format;
        exec_print(command.c_str());
    }
    else{
        string command = "ffmpeg -i " + file_name + " -map 0:a -c copy " + file_name.substr(0, file_name.find_last_of(".")) + "_audio.wav";
        exec_print(command.c_str());
    }
}

void extract_video(){
    cout << "Select a file to extract video from.(Including file extensions)\n";
    string file_name;
    cin.ignore();
    std::getline(cin,file_name);
    file_name='\"'+file_name+'\"';
    cout << "Do you want to re-encode the video?(y/n)\n";
    string re_encode;
    cin >> re_encode;
    if(re_encode == "y"){
        cout << "Select a format to convert to(filename extensions).\n";
        string format;
        cin >> format;
        string command = "ffmpeg -i " + file_name + " -map 0:v " + file_name.substr(file_name.find_last_of(".")+ 1) + "_extracted." + format;
        exec_print(command.c_str());
    }
    else{
        string command = "ffmpeg -i " + file_name + " -map 0:v -c copy " + file_name.substr(0, file_name.find_last_of(".")) + "_extracted." + file_name.substr(file_name.find_last_of(".")+ 1);
        exec_print(command.c_str());
    }
}

void cut_video_l(){
    cout << "Select a file to cut video from.(Including file extensions)\n";
    string file_name;
    cin.ignore();
    std::getline(cin,file_name);
    file_name='\"'+file_name+'\"';
    cout << "Select a start time(00:00:02).\n";
    string start_time;
    cin >> start_time;
    cout << "Select an end time(00:00:25) NOT duration.\n";
    string end_time;
    cin >> end_time;
    string command = "ffmpeg -ss " + start_time + " -i " + file_name + " -copyts -to " + end_time + " -c copy " + file_name.substr(0, file_name.find_last_of(".")) + "_cut." + file_name.substr(file_name.find_last_of(".")+ 1);
    exec_print(command.c_str());
}
void cut_video_d(){
    cout << "Select a file to cut video from.(Including file extensions)\n";
    string file_name;
    cin.ignore();
    std::getline(cin,file_name);
    file_name='\"'+file_name+'\"';
    cout << "Select a start time(00:00:02).\n";
    string start_time;
    cin >> start_time;
    cout << "Select an end time(00:00:25) by duration.\n";
    string end_time;
    cin >> end_time;
    string command = "ffmpeg -ss " + start_time + " -i " + file_name + " -t " + end_time + " -c copy " + file_name.substr(0, file_name.find_last_of(".")) + "_cut." + file_name.substr(file_name.find_last_of(".")+ 1);
    exec_print(command.c_str());
}
int main(){
    cout << "What do you want to do?\n"
         << "Select by typing\n1\n"
         << "(1) Convert into another format.\n"
         << "(2) Extract audio.\n"
         << "(3) Extract video.\n"
         << "(4) Cut video by length.\n"
         << "(5) Cut video by duration.\n";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            convert_into_another();
            break;
        case 2:
            extract_audio();
            break;
        case 3:
            extract_video();
            break;
        case 4:
            cut_video_l();
            break;
        case 5:
            cut_video_d();
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }

}