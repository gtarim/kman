#ifndef INCLUDE_LSMOD
#define INCLUDE_LSMOD

#include "common.hpp"
#include "command.hpp"
#include "menu.hpp"

class Lsmod : public Command
{
public:
 
    Lsmod() = default;

    static bool runFlag;
    
    static void run()
    {
        // std::cout << exec("cat /proc/meminfo | head -n5") << std::endl;

        // std::string resultCmd = exec("lsmod");
        std::string resultCmd = exec("cat /proc/meminfo | head -n5");

        std::vector<std::string> resultSplit = split(resultCmd,"\n");
        
        int index = 0;
        for (std::string str : resultSplit)
        {
            std::cout << index++ << " == " << str << std::endl;
        }
    }

};

bool Lsmod::runFlag {false};



// class Lsmod : public Command
// {
// public:
//     Lsmod() = default;

//     bool runFlag {false};

//     void run() override
//     {
//         std::cout << exec("lsmod | head -n5") << std::endl;
//     };

//     static void run1()
//     {
//         std::cout << exec("lsmod | head -n5") << std::endl;
//     };

// };

#endif