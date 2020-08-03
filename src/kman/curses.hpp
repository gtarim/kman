#ifndef INCLUDE_CURSES
#define INCLUDE_CURSES

#include "common.hpp"
#include <curses.h>

#define MIN_COLS    40
#define MIN_LINES   10

class Curses
{
public:
    Curses()
    {
        window = std::make_shared<WINDOW>(*initscr());
        cbreak();
        noecho();
        start_color();
	    init_pair(1, COLOR_WHITE, COLOR_BLACK);
	    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }

    WINDOW* getWindow() { return window.get();}

    int clearWin()
    {
        return clear();
    }
    
    int endWin()
    {
        return endwin();
    }

    int refreshWin()
    {
        return refresh();
    }

    bool checkWindowSize()
    {
        return ((COLS < MIN_COLS) || (LINES < MIN_LINES)) ? false : true;
    }
private:
    std::shared_ptr<WINDOW> window;
    int windowMax;
    int windowMin;
};

#endif

    // std::thread thLsmod(Lsmod::thLsmodCallback);
    // later later_test1(1000, false, &timerCallback);

// #include <cstdio>
// #include <memory>
// #include <stdexcept>
// #include <string>
// #include <array>
// std::string exec(const char* cmd) {
//     std::array<char, 128> buffer;
//     std::string result;
//     std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//     if (!pipe) {
//         throw std::runtime_error("popen() failed!");
//     }
//     while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//         result += buffer.data();
//     }
//     return result;
// }

// #include <functional>
// #include <chrono>
// #include <future>
// #include <cstdio>
// class Timer
// {
// public:
//     template <class callable, class... arguments>
//     Timer(int after, bool async, callable&& f, arguments&&... args)
//     {
//         std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
//         if (async)
//         {
//             std::thread([after, task]() {
//                 std::this_thread::sleep_for(std::chrono::milliseconds(after));
//                 task();
//             }).detach();
//         }
//         else
//         {
//             std::this_thread::sleep_for(std::chrono::milliseconds(after));
//             task();
//         }
//     }
// };

// void timerCallback()
// {    
//     Lsmod ls {};

//     std::string cmd = "cat /proc/meminfo | head -n5";
//     std::string str = ls.exec(cmd.c_str());

//     printw("%s\n",cmd.c_str());
//     printw(str.c_str());

//     // later later_test1(1000, false, &timerCallback);
// }

// void Lsmod::thLsmodCallback()
// {
//     while(1)
//     {
//         clear();
//         Timer timer(1000, false, &timerCallback);
//         refresh();
//     }

//     std::terminate();
        
// }


    // thLsmod.detach();
