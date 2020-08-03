#include <iostream>
#include <vector>
#include <menu.h>
#include <utility>
#include <memory>
#include <list>

class Window
{
private:
    std::shared_ptr<WINDOW*> window_ptr;
public:
    Window() 
    {
        window_ptr = std::make_shared<WINDOW*>(newwin(LINES/2, COLS, 0, 0));
    }
    
    Window(int x, int y) 
    {
        window_ptr = std::make_shared<WINDOW*>(newwin(LINES/2, COLS, y, x));
    }

    void setWindow(int x, int y)
    {
        window_ptr = std::make_shared<WINDOW*>(newwin(LINES/2, COLS, y, x));
    }

    

    void create(MENU * menu_ptr)
    {
        set_menu_win(menu_ptr, *window_ptr.get());
        set_menu_sub(menu_ptr, derwin(*window_ptr.get(), LINES/2-2, COLS-1, 1, 1));
	    set_menu_format(menu_ptr, LINES/2-2, 1);
        set_menu_mark(menu_ptr, " ");

        box(*window_ptr.get(), 0, 0);
    }

    void changeEnable(bool enable)
    {
            wattron(getWindow(),COLOR_PAIR(1));
            box(getWindow(),0,0);
            wattroff(getWindow(),COLOR_PAIR(2));
    }

    WINDOW* getWindow() const { return *window_ptr.get(); }

    void keypadEnable(bool flag) const { keypad(*window_ptr.get(),flag); }
    
    void refresh()
    {
        wrefresh(*window_ptr.get());
    }
    
};

class Menu
{
private:
    std::vector<ITEM *> itemList;
    std::unique_ptr<MENU *> menu_ptr;
public:
    Menu() = default;

    void create(std::vector<std::string> &list)
    {
        /* Initialize items */
        for(int i = 0; i < list.size(); ++i)
        {
            itemList.push_back(new_item(list.at(i).c_str(), ""));
        }

        /* Create menu */
        menu_ptr = std::make_unique<MENU *>(new_menu((ITEM **) &itemList[0]));
    }

    void post()
    {
        post_menu(*menu_ptr.get());
    }

    void unpost()
    {
        unpost_menu(*menu_ptr.get());
    }

    MENU* getMenu() const 
    { 
        return *menu_ptr.get();
    }

    void driveMenu(int type)
    {
        menu_driver(*menu_ptr.get(), type);
    }

    void freeMenuItems()
    {
        ITEM **items = menu_items(static_cast<const MENU*>(getMenu()));
        int itemCount = item_count(static_cast<const MENU*>(getMenu()));

        for(int i = 0; i < itemCount; i++)
        {
            free_item(items[i]);
        }
        free_menu(getMenu());
    }

    void updateMenu(std::vector<std::string> &list)
    {
        std::vector<ITEM *> iList;
        for(int i = 0; i < list.size(); ++i)
            iList.push_back(new_item(list.at(i).c_str(), ""));

        int ret = set_menu_items(*menu_ptr.get(),(ITEM **) &iList[0]);
    }
};