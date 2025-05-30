# @mintchipleaf's QMK Community Modules

In order to use these community modules with a build of QMK, this repo should be added to your external userspace as a submodule.

```sh
cd /path/to/your/external/userspace
git submodule add https://github.com/mintchipleaf/qmk_modules.git modules/mintchipleaf
git submodule update --init --recursive
```

Each child directory is a separate module, and has instructions on how to add it to your build.

| Module | Description |
| ----------------------- | ----------- |
| [Luna Keyboard Pet](./lunapet) | Adds the adorable [Luna keyboard pet](https://github.com/HellSingCoder/qmk_firmware/tree/33d7fa1180d232dcdb024c68a8f4629dced32afb/keyboards/sofle/keymaps/helltm) using Quantum Painter |
