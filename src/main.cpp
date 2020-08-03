#include "menu.hpp"
#include "curses.hpp"
#include "common.hpp"
#include "lsmod.hpp"

void callbackLsmod()
{
    Lsmod::runFlag = true;
    while (Lsmod::runFlag)
    {
        Timer timer(1000, false, &Lsmod::run);
    }
};

int main()
{
    // std::thread thLsmod(callbackLsmod);

    // char c;
    // while (true)
    // {
    //     std::cin >> c;
    //     switch (c)
    //     {
    //     case 'a':
    //         std::cout << "######  exit  ######" << std::endl;
    //         Lsmod::runFlag = false;
    //         thLsmod.join();
    //         break;
    //     }
    // }

    int c;
    Curses curses {};

    // checking window size
    if(!curses.checkWindowSize())
    {
        curses.refreshWin();
        printw("WINDOW size is should be greater then %dx%d",COLS,LINES);
        getch();
        curses.clearWin();
        curses.endWin();
    }

    keypad(stdscr, TRUE);

    //////////////////////////////////////////

    // creting lsmod menu
    std::vector<std::string> listMenuTop;
    listMenuTop.push_back("gokhantarim");
    listMenuTop.push_back("gtarim");
    listMenuTop.push_back("gkhantarim");
    listMenuTop.push_back("gtarima");
    listMenuTop.push_back("asdasddf");
    listMenuTop.push_back("asfaf");
    listMenuTop.push_back("gkhantaaarim");
    listMenuTop.push_back("gtarffim");

    // creting lsmod menu
    std::vector<std::string> listMenuBottom;
    listMenuBottom.push_back("gokhantarim");
    listMenuBottom.push_back("gtarim");
    listMenuBottom.push_back("gkhantarim");
    listMenuBottom.push_back("gtarima");
    listMenuBottom.push_back("asdasddf");
    listMenuBottom.push_back("asfaf");
    listMenuBottom.push_back("gkhantaaarim");
    listMenuBottom.push_back("gtarffim");

    //////////////////////////////////////////

    Menu menuTop {};
    menuTop.create(listMenuTop);

    Menu menuBottom {};
    menuBottom.create(listMenuBottom);

    //////////////////////////////////////////

    Window menuWindowTop {0,0};
    menuWindowTop.keypadEnable(true);
    menuWindowTop.create(menuTop.getMenu());

    Window menuWindowBottom {0,(LINES/2)};
    menuWindowBottom.keypadEnable(true);
    menuWindowBottom.create(menuBottom.getMenu());

    //////////////////////////////////////////

    //////////////////////////////////////////

    curses.refreshWin();
    menuTop.post();
    menuWindowTop.refresh();
    menuBottom.post();
    menuWindowBottom.refresh();

    bool enabledWindow = true; // true = top, false = bottom

    while((c = getch()) != KEY_F(1))
    {
        switch(c)
        {
        case '\t':
            enabledWindow = !enabledWindow;
            // if(enabledWindow)
            // {
            //     wbkgd(menuWindowTop.getWindow(),COLOR_PAIR(2));
            //     wbkgd(menuWindowBottom.getWindow(),COLOR_PAIR(1));
            // }
            // else
            // {
            //     wbkgd(menuWindowBottom.getWindow(),COLOR_PAIR(2));
            //     wbkgd(menuWindowTop.getWindow(),COLOR_PAIR(1));
            // }

            break;

        case KEY_DOWN:
            if(enabledWindow)
                menuTop.driveMenu(REQ_DOWN_ITEM);
            else
                menuBottom.driveMenu(REQ_DOWN_ITEM);
    		break;

    	case KEY_UP:
            if(enabledWindow)
                menuTop.driveMenu(REQ_UP_ITEM);
            else
                menuBottom.driveMenu(REQ_UP_ITEM);
    		break;
    	}
        menuWindowTop.refresh();
        menuWindowBottom.refresh();
    }

    menuTop.unpost();
    menuBottom.unpost();

    curses.refreshWin();
    curses.clearWin();
    curses.endWin();
    return 0;
}
