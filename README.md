# PS2 GSKit 2D Test
This is a simple 'game' designed to run on a PlayStation 2. It is built using PS2DEV and gsKit. The core
design goal of this code is to hide the platform specific code in a way where most of the logic never
touches it. Because of this, the game can be compiled for PC too, building on an SDL2 backend.

## Why?
I love the PlayStation 2. It was my first console and I have always been fascinated by the idea of
building my own game for it.

## Building
You will need the PS2SDK and associated tools to build this project. It also relies on gsKit, which is a
complementary project abstracting away many of the details of memory transfers powering PS2 graphics. 

romfs may also be required from a collection of PS2 ports in the PS2DEV project, too. I am
investigating how to package Playstation 2 games most effectively, and romfs has been in and out of the
build

After you have installed PS2DEV, the PS2 binutils, PS2SDK, gsKit and romfs you should just be able to run
make. The elf produced can be run on a PS2 through any custom software loader, or launched in PCSX2, but the
reccomended way to run for now is through ps2link. This is currently the only way to run which has loading
resources.

## The Plan
Once I have a few more features working in this project, I am going to split out the core drawing, system,
event and game-loop code into a static library. I will then start a new project for a specific game building
on it.

## Style Guide
- Write sensible C code!
- In function defintions, the opening curly brace goes on a new line.
- In if/while statements, the opening curly brace stays on the same line.
- Function names are in ```this_format()```
- Variable names are in the same format, with constants in capitals.
- Comments are all lower case ;D

## TODO
- Cleanup commenting, remove @date, comment remaining files (eg room, menu functionality)
- Simplify abstractions - platform and sys seem awfulyl similar
- Trim fat
- Better texture loading for SDL
- Make the SDL version actually run!

