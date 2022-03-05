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

string exec(const char* cmd, const string& error_message="Error!") {
    std::array<char, 128> buffer;
    std::string result;

    auto pipe = popen(cmd, "r"); // get rid of shared_ptr

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }

    auto rc = pclose(pipe);

    if (rc != EXIT_SUCCESS) { // == 0
        throw std::runtime_error(error_message);
    }
    return result;
}
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