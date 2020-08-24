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

bool initDmesg {false};
std::mutex mutexLsmod,mutexDmesg;
int yLsmod {1}, yDmesg {1};

static int lsmodCallback()
{
    std::vector<std::string> list = split(Command::exec("lsmod | head -100"),'\n');
    menuTop.unpost();
    menuTop.freeMenuItems();
    menuTop.updateMenu(list);
    set_menu_sub(menuTop.getMenu(), 
                derwin(menuWindowTop.getWindow(), LINES/2-2, COLS-2, 1, 1));
    box(menuWindowTop.getWindow(), 0, 0);
    menuTop.post();
    mutexLsmod.lock();
    for (uint8_t index = 1; index < yLsmod; index++)
    {
        menuTop.driveMenu(REQ_DOWN_ITEM);
    }
    mutexLsmod.unlock();
    menuWindowTop.refresh();
    curses.refreshWin();
    
    Timer timerLsmod(2000, false, &lsmodCallback);
}

static int dmesgCallback()
{
    std::vector<std::string> listD = split(Command::exec("dmesg"),'\n');
    std::reverse(listD.begin(),listD.end());
    menuBottom.unpost();
    menuBottom.freeMenuItems();
    menuBottom.updateMenu(listD);
    set_menu_sub(menuBottom.getMenu(), 
                derwin(menuWindowBottom.getWindow(), LINES/2-2, COLS-2, 1, 1));
    box(menuWindowBottom.getWindow(), 0, 0);
    menuBottom.post();
    mutexDmesg.lock();
    for (uint8_t index = 1; index < yDmesg; index++)
    {
        menuBottom.driveMenu(REQ_DOWN_ITEM);
    }
    mutexDmesg.unlock();
    menuWindowBottom.refresh();
    curses.refreshWin();
    
    Timer timerDmesg(1500, false, &dmesgCallback);
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
    scrollok(stdscr, TRUE); // scroll ok

    //////////////////////////////////////////

    // creting lsmod menu
    std::vector<std::string> listMenuTop;
    listMenuTop.push_back("gokhantarim");

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
            {
                mutexLsmod.lock();
                yLsmod++;
                mutexLsmod.unlock();
                menuTop.driveMenu(REQ_DOWN_ITEM);
            }else
            {
                mutexDmesg.lock();
                yDmesg++;
                mutexDmesg.unlock();
                menuBottom.driveMenu(REQ_DOWN_ITEM);
            }
			break;
            
		case KEY_UP:
            if(enabledWindow)
            {
                mutexLsmod.lock();
                yLsmod--;
                mutexLsmod.unlock();
                menuTop.driveMenu(REQ_UP_ITEM);
            }
            else
            {
                mutexDmesg.lock();
                yDmesg--;
                mutexDmesg.unlock();
                menuBottom.driveMenu(REQ_UP_ITEM);
            }
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
