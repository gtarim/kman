#ifndef INCLUDE_LSMOD
#define INCLUDE_LSMOD

#include "command.hpp"

class Lsmod : public Command
{
public:
    void run() override 
    {
        std::cout << exec("lsmod | head -n5") << std::endl;
    };
    
    static void callback()
    {
        Command::exec("lsmod | head -n5");
    }

private:
    bool isStop;
};

#endif