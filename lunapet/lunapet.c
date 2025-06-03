#include QMK_KEYBOARD_H
#include <qp.h>
#include <stdint.h>
#include "assets/lunasit1.qgf.h"
#include "lunapet.h"
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
/* Separate from  */
bool luna_enabled = true;

/* Whether Luna rendering should be handled by this module */
/* If false, call luna_draw() from keymap.c to render Luna manually */
bool luna_auto_draw = true;

static int luna_x = 0;
static int luna_y = 0;

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
void luna_set_position(int LUNA_X, int LUNA_Y) {
    luna_x = LUNA_X;
    luna_y = LUNA_Y;
}

/* KEYBOARD PET START */

/* timers */
static uint32_t luna_anim_timer = 0;

/* current frame */
static uint8_t current_frame = 0;

/* status variables */
static int current_wpm = 0;
static led_t led_usb_state;

static bool is_sneaking = false;
static bool is_jumping = false;
static bool jump_dirty = false;

bool is_luna_timer_elapsed(void) {
    return timer_elapsed32(luna_anim_timer) > LUNA_FRAME_DURATION;
}

/* Draws Luna on screen at the defined coordinates */
int current_y;
void luna_draw(bool FLUSH, bool JUMP_CLEANUP) {
    if(!luna_enabled || luna_display == NULL) {
        return;
    }

    /* check frame timer */
    if(is_luna_timer_elapsed()) {
        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* reset frame timer */
        luna_anim_timer = timer_read32();
    } else if (!jump_dirty) {
        return;
    }

    if(jump_dirty) {
        if(is_jumping) {
            /* perform jump */
            current_y = luna_y - LUNA_JUMP_HEIGHT;

            if (JUMP_CLEANUP) {
                /* clear */
                qp_rect(luna_display, luna_x, (current_y + lunasit1->height), (luna_x + lunasit1->width), (current_y + lunasit1->height + LUNA_JUMP_HEIGHT), 0, 0, 0, true);
            }
        } else {
            /* perform landing */
            if (JUMP_CLEANUP) {
                /* clear */
                qp_rect(luna_display, luna_x, current_y, (luna_x + lunasit1->width), current_y + LUNA_JUMP_HEIGHT, 0, 0, 0, true);
            }
        }

        jump_dirty = false;
    }

    if(!is_jumping) {
        current_y = luna_y;
    }

    /* current status */
    if(led_usb_state.caps_lock) {
        if(current_frame == 1) {
            qp_drawimage(luna_display, luna_x, current_y, lunabark1);
        } else {
            qp_drawimage(luna_display, luna_x, current_y, lunabark2);
        }
    } else if(is_sneaking) {
        if(current_frame == 1) {
            qp_drawimage(luna_display, luna_x, current_y, lunasneak1);
        } else {
            qp_drawimage(luna_display, luna_x, current_y, lunasneak2);
        }
    } else if(current_wpm <= LUNA_MIN_WALK_WPM) {
        if(current_frame == 1) {
            qp_drawimage(luna_display, luna_x, current_y, lunasit1);
        } else {
            qp_drawimage(luna_display, luna_x, current_y, lunasit2);
        }
    } else if(current_wpm <= LUNA_MIN_RUN_WPM) {
        if(current_frame == 1) {
            qp_drawimage(luna_display, luna_x, current_y, lunawalk1);
        } else {
            qp_drawimage(luna_display, luna_x, current_y, lunawalk2);
        }
    } else {
        if(current_frame == 1) {
            qp_drawimage(luna_display, luna_x, current_y, lunarun1);
        } else {
            qp_drawimage(luna_display, luna_x, current_y, lunarun2);
        }
    }

    if(FLUSH) {
        qp_flush(luna_display);
    }
}

/*==QMK API==*/

/* Draw Luna as housekeeping task */
void housekeeping_task_lunapet(void) {
    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    if(luna_auto_draw) {
        luna_draw(true, true);
    }
}

/* Load assets */
void keyboard_post_init_lunapet(void) {
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

#ifdef LUNA_START_DISABLED
    luna_enabled = false;
#endif //LUNA_START_DISABLED
}

/* Monitor key-based animation state changes */
void post_process_record_lunapet(uint16_t KEYCODE, keyrecord_t *RECORD) {
    switch (KEYCODE) {
        case KC_LCTL:
        case KC_RCTL:
                is_sneaking = RECORD->event.pressed;
            break;
        case KC_SPC:
                is_jumping = RECORD->event.pressed;
                jump_dirty = true;
            break;
        case LUNA:
            if (RECORD->event.pressed) {
                luna_enabled = !luna_enabled;
            }
            break;
        default:
            break;
    }
}
