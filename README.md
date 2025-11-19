# Embedded Systems Projects

This repository contains lab exercises and embedded-systems project code used for learning and experimentation with microcontrollers (C, Assembly). The projects are organized by lab and utility folders. Each lab directory contains source files, headers, and any supporting build/startup files required for that exercise.

## Repository structure

- Lab 2, Lab 3, Lab 4, Lab 5, Lab 6, Lab 7, Lab 8
- Lab2Final
- Util

(Each lab directory contains the source code and build files for that lab. See the README in a lab folder or the code comments for build/run instructions.)

## Languages
This repository contains mostly C code, with some Assembly and build scripts.

## How to build and run (general)
1. Open the lab folder you want to build.
2. Use your toolchain for the target microcontroller (e.g., TI CCS, gcc-arm, or another toolchain depending on your board).
3. Follow comments in the source files for pin mappings and hardware notes.
4. For projects requiring startup scripts or linker files, ensure your toolchain uses the included startup and linker files.

## Contributing
- Prefer creating a branch per change (git checkout -b my-change).
- Keep commits focused and include descriptive messages.
- If adding new projects, include a short README in that project folder describing hardware, build steps, and expected behavior.

## Archiving or removing projects
If you need to remove a completed project from the main branch (for example, to keep the main branch minimal), consider:
- Moving the project to an `archive/` folder or a separate branch so history is preserved.
- Creating a PR that documents the removal and links to an archive branch or a downloadable archive.

## License
Include your license here (e.g., MIT, GPL) or add a LICENSE file to the repository.

## Contact
Repository owner: ak23bar
