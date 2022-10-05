#include <stdlib.h>
#include <ncurses.h>
#include "menu.h"


int
main (  )
{
  initscr();
  cbreak();
  noecho();
  halfdelay(1);
  keypad(stdscr, TRUE);
  use_default_colors();
  start_color();

  WINDOW *win = newwin ( 10, 30, 10, 10 );
  box ( win, 0, 0 );
  refresh();
  wrefresh ( win );
  
  struct kp_menu_t *menu = kp_menu_init ( win );
  kp_menu_add_element ( menu, "Hello World", 666 );
  kp_menu_add_element ( menu, "University Lectures", 31 );
  kp_menu_add_element ( menu, "Programming", 32 );
  kp_menu_add_element ( menu, "Noise, Waves & Fields", 33 );
  kp_menu_add_element ( menu, "+ ADD NEW WORKSPACE", 34 );


  int c = getch();

  while (c != 27)
    {
      if (c == KEY_UP)
        {
          kp_menu_move_up(menu);
        }
      else if (c == KEY_DOWN)
        {
          kp_menu_move_down(menu);
        }

      kp_menu_draw ( menu );
      c = getch();

    }

  delwin ( win );
  endwin (  );

  return EXIT_SUCCESS;
}
