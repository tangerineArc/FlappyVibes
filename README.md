# Flappy Vibes

**Flappy Vibes** is a game largely inspired by the classic Flappy Bird game, but has random emojis as sprites on top of random background themes.

## Repo Structure

Below is a list of all the files and directories that the project contains:
- `/arc.c` - primary file where the driver code for the application is
- `/helpers.c` - contains helper functions used in `arc.c`
- `/Makefile` - compilation instructions
- `/SDL2.dll` - (part of SDL2) dynamic link library for SDL2
- `/SDL2_image.dll` - (part of SDL2) contains driver functions for handling image loading and decoding
- `/SDL2_ttf.dll` - (part of SDL2) wrapper around the FreeType and Harfbuzz libraries, allowing to use TrueType fonts to render text
- `/sdlImage/*`, `/sdlMain/*`, `/sdlTTF/*` - (part of SDL2) contains the library code
- `/headers/` - contains custom header files
  - `./background.h` - structure definiton for game background
  - `./environment.h` - constant declarations for environment parameters
  - `./paths.h` - constant declaration for asset paths
  - `./pipe.h` - structure definiton for in-game obstacles (pipes)
  - `./sprite.h` - structure definition for the main sprite
- `/assets/*` - contains visual game assets such as graphics, backgrounds and fonts

## Tech Stack

- **C** - main programming language
- **SDL2** - library for low-level access to graphics and media hardware

## Snapshots

| [![flappy-vibes1.png](https://i.postimg.cc/zBQsYnpC/flappy-vibes1.png)](https://postimg.cc/jwzgznp2) | [![flappy-vibes2.png](https://i.postimg.cc/Xqh69XJg/flappy-vibes2.png)](https://postimg.cc/1VpdQmDg) |
| --- | --- |
| [![flappy-vibes3.png](https://i.postimg.cc/cJVD7YMC/flappy-vibes3.png)](https://postimg.cc/2q7Fr1tN) | |

