#include <stdlib.h>
#include <ncurses.h>

struct kp_menu_t;

struct kp_menu_t* kp_menu_init(WINDOW *window);

void kp_menu_debug(struct kp_menu_t *menu);

int kp_menu_add_element(struct kp_menu_t *menu,
                         char *name,
                         int id);

void kp_menu_remove_element(struct kp_menu_t *menu,
                            int id);

// Returns the ID of the selected element.
int kp_menu_move_up(struct kp_menu_t *menu);

// Returns the ID of the selected element.
int kp_menu_move_down(struct kp_menu_t *menu);

int kp_menu_activate(struct kp_menu_t *menu,
                      int id);

void kp_menu_highlight_on(struct kp_menu_t *menu);
void kp_menu_highlight_off(struct kp_menu_t *menu);

int kp_menu_get_active_id(struct kp_menu_t *menu);
char* kp_menu_get_element_name(struct kp_menu_t *menu, int id);

void kp_menu_draw(struct kp_menu_t *menu);

void kp_menu_destroy(struct kp_menu_t *menu);
