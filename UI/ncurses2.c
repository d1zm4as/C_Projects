/*ncurses2.c*/

#include <ncurses.h>

int main(){
    
    int x,y;

    initscr();
    clear();
    // gets the coordinates of the cursor
    getyx(stdscr,y,x);
    printw( "x = %d\n"
            "y = %d"
    );

    refresh();
    y = 5;
    x = 10;
    //moves the cursor
    move(y,x)   ;
    printw("Over here!");
    refresh();
    getch();
    endwin();
    return 0;

}