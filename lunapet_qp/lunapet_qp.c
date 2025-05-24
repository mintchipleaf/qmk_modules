#include QMK_KEYBOARD_H
#include "lunapet_qp.h"
#include "assets/lunasit1.qgf.h"
#include "assets/lunasit2.qgf.h"
#include "assets/lunawalk1.qgf.h"
#include "assets/lunawalk2.qgf.h"
#include "assets/lunarun1.qgf.h"
#include "assets/lunarun2.qgf.h"
#include "assets/lunasneak1.qgf.h"
#include "assets/lunasneak2.qgf.h"
#include "assets/lunabark1.qgf.h"
#include "assets/lunabark2.qgf.h"


/* Whether Luna should be rendered */
bool luna_enabled = true;

/* Whether Luna rendering should be handled by this module */
/* If false, call luna_draw() from keymap.c to render Luna manually */
bool luna_auto_draw = true;

static int16_t luna_x = 0;
static int16_t luna_y = 0;

static painter_device_t luna_display = NULL;
static painter_image_handle_t lunasit1;
static painter_image_handle_t lunasit2;
static painter_image_handle_t lunawalk1;
static painter_image_handle_t lunawalk2;
static painter_image_handle_t lunarun1;
static painter_image_handle_t lunarun2;
static painter_image_handle_t lunasneak1;
static painter_image_handle_t lunasneak2;
static painter_image_handle_t lunabark1;
static painter_image_handle_t lunabark2;


/* Sets which display to render Luna on */
void luna_set_display(painter_device_t DISPLAY) {
    luna_display = DISPLAY;
}

/* Sets the position Luna will be rendered on the display */
void luna_set_position(int16_t LUNA_X, int16_t LUNA_Y) {
    luna_x = LUNA_X;
    luna_y = LUNA_Y;
}

/* Draws Luna on screen at the defined coordinates */
void luna_draw(void) {
    if(!luna_enabled || luna_display == NULL) {
        return;
    }

    qp_drawimage(luna_display, luna_x, luna_y, lunasit1);
    qp_flush(luna_display);
}


/* Draw Luna as housekeeping task */
void housekeeping_task_lunapet_qp_user(void) {
    if(luna_auto_draw) {
        luna_draw();
    }
}

/* Load assets */
void keyboard_post_init_lunapet_qp_user(void) {
    lunasit1 = qp_load_image_mem(gfx_lunasit1);
    lunasit2 = qp_load_image_mem(gfx_lunasit2);
    lunawalk1 = qp_load_image_mem(gfx_lunawalk1);
    lunawalk2 = qp_load_image_mem(gfx_lunawalk2);
    lunarun1 = qp_load_image_mem(gfx_lunarun1);
    lunarun2 = qp_load_image_mem(gfx_lunarun2);
    lunasneak1 = qp_load_image_mem(gfx_lunasneak1);
    lunasneak2 = qp_load_image_mem(gfx_lunasneak2);
    lunabark1 = qp_load_image_mem(gfx_lunabark1);
    lunabark2 = qp_load_image_mem(gfx_lunabark2);

}
