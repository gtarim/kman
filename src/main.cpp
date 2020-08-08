#include "menu.hpp"
#include "curses.hpp"
#include "common.hpp"
#include "lsmod.hpp"

Curses curses {};
Window menuWindowTop {0,0};
Window menuWindowBottom {0,(LINES/2)};
Menu menuTop {};
Menu menuBottom {};

int x, y;
static int lsmodCallback()
{

    // std::vector<std::string> list = split(Command::exec("lsmod | head -n5"),'\n');
    std::string str = "lsmod | head -n" + std::to_string((LINES/2)-2);
    std::vector<std::string> list = split(Command::exec(str.c_str()),'\n');

    menuTop.unpost();
    menuTop.freeMenuItems();
    menuTop.updateMenu(list);
    box(menuWindowTop.getWindow(), 0, 0);
    getyx(menuWindowTop.getWindow(), y, x); 
    menuTop.post();
    move(y,x);
    
    if(y == 1) // checking lsmod head title
        y++;

    for (uint8_t index = 1; index < y; index++)
    {
           menuTop.driveMenu(REQ_DOWN_ITEM);
    }
     
    menuWindowTop.refresh();
    curses.refreshWin();
    
    Timer timerLsmod(100, false, &lsmodCallback);
}

static int dmesgCallback()
{

    std::string str = "ps | head -n" + std::to_string((LINES/2)-2);
    std::vector<std::string> list = split(Command::exec(str.c_str()),'\n');

    menuBottom.unpost();
    menuBottom.freeMenuItems();
    menuBottom.updateMenu(list);
    box(menuWindowBottom.getWindow(), 0, 0);
    getyx(menuWindowBottom.getWindow(), y, x); 
    menuBottom.post();
    move(y,x);
    
    if(y == 1) // checking lsmod head title
        y++;

    for (uint8_t index = 1; index < y; index++)
    {
        menuBottom.driveMenu(REQ_DOWN_ITEM);
    }
     
    menuWindowBottom.refresh();
    curses.refreshWin();
    
    Timer timerDmesg(1000, false, &dmesgCallback);
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

	keypad(stdscr, TRUE);   // enable keypad
    curs_set(0);            // invisible cursor

    //////////////////////////////////////////

    // creting lsmod menu
    std::vector<std::string> listMenuTop;
    listMenuTop.push_back("");

    // creting lsmod menu
    std::vector<std::string> listMenuBottom;
    listMenuBottom.push_back("gokhantarim");

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

    Timer timerLsmod(0, true, &lsmodCallback);
    Timer timerDmesg(0, true, &dmesgCallback);

    //////////////////////////////////////////

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
            {
                // lsmod check window head
                if(y==2)
                    break;
                menuTop.driveMenu(REQ_UP_ITEM);
            }
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
