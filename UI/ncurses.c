/*ncurses.c*/

#include <ncurses.h>

int main(){
    
    char letter;

// inicialize screen
    
    initscr();
// ncurses own printf function
    
    printw("Press any key\n");

    refresh();
// ncurses version of getchar
    letter = getch();
    clear();

    printw("You entered: '%c' \n",letter);

    refresh();

    getch();
    endwin();
    return 0;




}