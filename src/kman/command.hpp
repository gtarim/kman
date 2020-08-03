#ifndef INCLUDE_COMMAND
#define INCLUDE_COMMAND

#include "common.hpp"

class Command
{
public:
    Command() = default;
    virtual void run() = 0;

    std::string exec(const char* cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
private:
};

#endif