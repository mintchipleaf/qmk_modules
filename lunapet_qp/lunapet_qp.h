#pragma once

#include QMK_KEYBOARD_H
#include <stdint.h>
#include <qp.h>

bool luna_enabled;
bool luna_auto_draw;

void luna_set_position(int16_t, int16_t);

void luna_set_display(painter_device_t);

void luna_draw(void);
