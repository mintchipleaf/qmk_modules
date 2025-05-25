#pragma once

#include QMK_KEYBOARD_H
#include <stdint.h>
#include <qp.h>

/* settings */
// WPM-responsive animation stuff here
#define LUNA_MIN_WALK_SPEED 10
#define LUNA_MIN_RUN_SPEED 40

/* advanced settings */
#ifndef LUNA_FRAME_DURATION
#   define LUNA_FRAME_DURATION 200 // how long each frame lasts in ms
#endif //LUNA_FRAME_DURATION

bool luna_enabled;
bool luna_auto_draw;

void luna_set_position(int16_t, int16_t);

void luna_set_display(painter_device_t);

void luna_draw(void);
