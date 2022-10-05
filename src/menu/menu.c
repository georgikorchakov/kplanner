#include <stdlib.h>
#include <string.h>
#include "menu.h"

struct kp_menu_element_t
{
  char *name;
  int id;
};

struct kp_menu_t
{
  WINDOW *window;

  int active_element;
  int highlight;

  int num_elements;
  struct kp_menu_element_t **menu_elements;
};

void kp_menu_debug(struct kp_menu_t *menu)
{
  mvprintw(1,1,"active = %d", menu->active_element);
}

struct kp_menu_t* kp_menu_init(WINDOW *window)
{
  struct kp_menu_t *menu = malloc( sizeof ( struct kp_menu_t ) );

  if ( menu == NULL )
    return NULL;

  menu->window = window;
  menu->num_elements = 0;
  menu->active_element = 0;
  menu->highlight = 1;

  return menu;
}

int kp_menu_add_element(struct kp_menu_t *menu, char *name, int id)
{
  struct kp_menu_element_t *menu_element =
    ( struct kp_menu_element_t* ) malloc( sizeof ( struct kp_menu_element_t ) );

  if ( menu_element == NULL )
    return 0;

  menu_element->name = name;
  menu_element->id = id;

  if ( menu->num_elements++ == 0 )
    menu->menu_elements =
      (struct kp_menu_element_t**) malloc ( sizeof ( struct kp_menu_element_t* ) );
  else
    menu->menu_elements = 
      (struct kp_menu_element_t**) realloc ( menu->menu_elements,
        menu->num_elements * sizeof ( struct kp_menu_element_t* ) );

  if ( menu->menu_elements == NULL )
    return 0;

  menu->menu_elements[menu->num_elements - 1] = menu_element;

  return 1;
}

void kp_menu_remove_element(struct kp_menu_t *menu,
                            int id);

// Returns the ID of the selected element.
int kp_menu_move_up(struct kp_menu_t *menu)
{
  if ( --menu->active_element < 0 )
    menu->active_element = 0;
  return menu->menu_elements[menu->active_element]->id;
}

// Returns the ID of the selected element.
int kp_menu_move_down(struct kp_menu_t *menu)
{
  if ( ++menu->active_element > menu->num_elements - 1 )
    menu->active_element = menu->num_elements - 1;
  return menu->menu_elements[menu->active_element]->id;
}

int kp_menu_activate(struct kp_menu_t *menu, int id)
{
  for ( int element_position = 0; element_position < menu->num_elements; ++element_position )
    if ( menu->menu_elements[element_position]->id == id )
      {
        menu->active_element = element_position;
        return 1;
      }

  return 0;
}

void kp_menu_highlight_on(struct kp_menu_t *menu)
{
  menu->highlight = 1;
}

void kp_menu_highlight_off(struct kp_menu_t *menu)
{
  menu->highlight = 0;
}

int kp_menu_get_active_id(struct kp_menu_t *menu)
{
  return menu->menu_elements[menu->active_element]->id;
}

char* kp_menu_get_element_name(struct kp_menu_t *menu, int id)
{
  for ( int element_position = 0; element_position < menu->num_elements; ++element_position )
    if ( menu->menu_elements[element_position]->id == id )
      {
        return menu->menu_elements[element_position]->name;
      }

  return NULL;
}

void kp_menu_draw(struct kp_menu_t *menu)
{
  int win_end_y, win_end_x;
  getmaxyx ( menu->window, win_end_y, win_end_x );

  int text_length;
  int line_length = win_end_x;
  int printing_y_position = 0;

  for ( int element_position = 0; element_position < menu->num_elements; ++element_position )
    {
      text_length = strlen ( menu->menu_elements[element_position]->name );

      if ( ( element_position == menu->active_element ) && menu->highlight )
        wattron ( menu->window, A_REVERSE | A_BOLD );

      mvwprintw ( menu->window, 
                  ++printing_y_position, 
                  ( line_length - text_length ) / 2,
                  "%s", menu->menu_elements[element_position]->name );

      wattroff ( menu->window, A_REVERSE | A_BOLD );
    }
  wrefresh ( menu->window );
}

void kp_menu_destroy(struct kp_menu_t *menu);

