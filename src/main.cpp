#include "menu.hpp"
#include "curses.hpp"
#include "common.hpp"
#include "lsmod.hpp"

Curses curses {};
Window menuWindowTop {0,0};
Window menuWindowBottom {0,(LINES/2)};
Menu menuTop {};
Menu menuBottom {};

static int callback()
{
    std::vector<std::string> list = split(Command::exec("ps | head -n5"),'\n');
    
    // for(std::string str : list)
    //     std::cout << str << std::endl;
    

    menuTop.unpost();
    menuTop.freeMenuItems();
    menuTop.updateMenu(list);
    menuTop.post();
    menuWindowTop.refresh();
    curses.refreshWin();
    
    Timer timer(3000, false, &callback);

}

int main()
{
    int c;

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
    // listMenuTop.push_back("gkhantarim");
    // listMenuTop.push_back("gtarima");
    // listMenuTop.push_back("asdasddf");
    // listMenuTop.push_back("asfaf");
    // listMenuTop.push_back("gkhantaaarim");
    // listMenuTop.push_back("gtarffim");

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
    
    menuTop.create(listMenuTop);
    menuBottom.create(listMenuBottom);
    
    //////////////////////////////////////////

    menuWindowTop.keypadEnable(true);
    menuWindowTop.create(menuTop.getMenu());

    menuWindowBottom.keypadEnable(true);
    menuWindowBottom.create(menuBottom.getMenu());

    //////////////////////////////////////////

    curses.refreshWin();
    menuTop.post();
    menuWindowTop.refresh();
    menuBottom.post();
    menuWindowBottom.refresh();

    //////////////////////////////////////////

    // Timer timer(1000, false, &callback);

    //////////////////////////////////////////
    std::vector<std::string> list;
    list.clear();
    list.push_back("123457890");
    list.push_back("asd123457890");
    list.push_back("1asd23457890");
    list.push_back("gdsg123457890");
    list.push_back("xvb123457890");

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

        case 't':
            /// TODO: update mechanism will check

            menuTop.unpost();
            menuTop.freeMenuItems();
            menuTop.updateMenu(list);
            menuTop.post();
            menuWindowTop.refresh();
            curses.refreshWin();
            
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
