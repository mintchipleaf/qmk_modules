# Luna Keyboard Pet

This adds @HellSingCoder's Luna keyboard pet through Quantum Painter as a community module. Currently only works with `quantum painter`, but intended to eventually add option to use `oled_driver` feature for greater compatibility.

This is currently a work in progress.

## Use
Add the following to your `keymap.json`:

```json
{
    "modules": ["mintchipleaf/lunapet"]
}
```

Initialize a `painter_device_t` for your display device (See [QMK Quantum Painter Drivers](https://docs.qmk.fm/quantum_painter#quantum-painter-drivers)), and call
```c
void luna_set_display(painter_device_t luna_display);
```
once in your `keymap.c` file's initialization functions. (ex. `keyboard_post_init_user()`).

***NOTE:*** Luna currently requires 10 frames to be loaded in order to function. If you are already loading images with QP, define `QUANTUM_PAINTER_NUM_IMAGES` as 10 + that number. (This module will define the number as 10, if user hasn't defined a number.)

## Configuration

| Setting                             | Default   | Description                                                                             |
| ----------------------------------- | --------- | --------------------------------------------------------------------------------------- |
| `LUNA_MIN_WALK_WPM`                 | `10`      | WPM required to trigger 'walk' animation. WPM under this will trigger 'sit' animation.  |
| `LUNA_MIN_RUN_WPM`                  | `40`      | WPM required to trigger 'run' animation.                                                |
| `LUNA_FRAME_DURATION`               | `200`     | How long each animation frame lasts in ms.                                              |
| `LUNA_JUMP_HEIGHT`                  | `1`       | How many pixels the luna sprite will move up when 'jumping'.                            |
| `LUNA_START_DISABLED`               | `undef`   | Whether Luna should start disabled, to be toggled on with `LUNA` keycode.               |

## API

| Setting                                    | Type   | Default | Description                                                                                                                                  |
| ------------------------------------------ | -------| ------- | ------------------------------------------------------------------------------------------------------------------------ |
| `luna_set_display(painter_device_t device)`| `void` | `NULL`  | [**REQUIRED**] Quantum Painter device to draw Luna on.                                                                   |
| `luna_set_position(int x,int y)`           | `void` | `0, 0`  | Position on the QP device where Luna will be drawn (the frame's top left pixel.)                                         |
| `luna_draw(bool flush, bool jump_cleanup)` | `void` |         | Performs the Luna rendering manually.<br>`flush`: whether a `qp_flush()` should be perfomed after drawing (For use in `keyboard.c`,see `luna_auto_draw`)<br> `jump_cleanup`: Whether to blank out the sprite lines left rendered from prev frame if a jump was started/ended. |
| `luna_timer_elapsed(void)`                 | `bool` |         | Returns `true` if Luna's frame timer is greater than `LUNA_FRAME_DURATION`. (Useful when manually calling `luna_draw()`) |
| `luna_enabled`                             | `bool` | `true`  | Whether Luna should be rendered currently.                                                                               |
| `luna_auto_draw`                           | `bool` | `true`  | Whether Luna rendering should be handled by this module. (If false, call `luna_draw()` from `keyboard.c` manually.)      |

## Keycodes

`LUNA` is used to toggle rendering of Luna (toggles `luna_enabled`).
