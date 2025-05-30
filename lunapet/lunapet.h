#pragma once

#include QMK_KEYBOARD_H
#include <stdint.h>
#include <qp.h>

/* settings */
// WPM-responsive animation stuff here
#ifndef LUNA_MIN_WALK_SPEED
    #define LUNA_MIN_WALK_WPM 10 // WPM required to go from sit -> walk
#endif //LUNA_MIN_WALK_SPEED

#ifndef LUNA_MIN_RUN_WPM
    #define LUNA_MIN_RUN_WPM 40 // WPM required to go from walk -> run
#endif //LUNA_MIN_RUN_SPEED

/* advanced settings */
#ifndef LUNA_FRAME_DURATION
#   define LUNA_FRAME_DURATION 200 // how long each frame lasts in ms
#endif //LUNA_FRAME_DURATION

#ifndef LUNA_JUMP_HEIGHT
#   define LUNA_JUMP_HEIGHT 8 // how many pixels the luna sprite will move up when 'jumping'
#endif //LUNA_JUMP_HEIGHT

#ifndef QUANTUM_PAINTER_NUM_IMAGES
#    define QUANTUM_PAINTER_NUM_IMAGES 10 // make sure we can at least load all 10 frames
#endif //QUANTUM_PAINTER_NUM_IMAGES

bool luna_enabled;
bool luna_auto_draw;

void luna_set_display(painter_device_t);

void luna_set_position(int, int);

void luna_draw(bool, bool);

bool is_luna_timer_elapsed(void);
