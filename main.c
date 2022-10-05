#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "src/menu/menu.h"

#define KEY_ESCAPE 27
void init_stdscr();

int main (  )
{
  init_stdscr();

  int menu_width = COLS / 2;
  int menu_height = LINES / 2;

  int menu_start_x = (COLS - menu_width)/2;
  int menu_start_y = (LINES - menu_height)/2;

  WINDOW *win = newwin ( menu_height, menu_width, menu_start_y, menu_start_x );
  box ( win, 0, 0 );
  refresh();
  wrefresh ( win );

  struct kp_menu_t *menu = kp_menu_init ( win );
  kp_menu_add_element ( menu, "Workspace 1", 1 );
  kp_menu_add_element ( menu, "Workspace 2", 2 );
  kp_menu_add_element ( menu, "Workspace 3", 3 );
  kp_menu_add_element ( menu, "Workspace 4", 4 );
  kp_menu_add_element ( menu, "+ ADD NEW WORKSPACE", 5 );

  int c;
  do
    {
      c = getch();
      if (c == KEY_UP)
        kp_menu_move_up(menu);
      else if (c == KEY_DOWN)
        kp_menu_move_down(menu);

      kp_menu_draw ( menu );
    }
  while (c != KEY_ESCAPE);

  delwin ( win );
  endwin (  );
  return EXIT_SUCCESS;
}

void init_stdscr()
{
  initscr();
  cbreak();
  noecho();
  halfdelay(1);
  curs_set(0);
  keypad(stdscr, TRUE);
  use_default_colors();
  start_color();
}


