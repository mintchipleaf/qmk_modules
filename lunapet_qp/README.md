# Luna Keyboard Pet in Quantum Painter

This adds @HellSingCoder's Luna keyboard pet through Quantum Painter as a community module. This works for both the `oled driver` feature and for `quantum painter`.

This is currently a work in progress.

It can be integrated into your keymap by adding the following to your `keymap.json`:

```json
{
    "modules": ["mintchipleaf/lunapet_qp"]
}
```

Quantum Painter support requires initializing your own `painter_device_t` and passing it `to luna_set_display()` in your `keymap.c` file. (See [QMK Quantum Painter Drivers](https://docs.qmk.fm/quantum_painter#quantum-painter-drivers))
