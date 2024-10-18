# Flappy Vibes

**Flappy Vibes** is a game largely inspired by the classic Flappy Bird game, but has random emojis as sprites on top of random background themes.

This project was done by me and my team for the **CS102: Programming & Data Structures** course under the B.Tech program offered by the **Indian Institute of Technology Patna**.

## Technological Design Choices

Here is a list of the various technologies I used in this project:

### C
The C programming language is a powerful, general-purpose language known for its efficiency and control, making it a popular choice for system programming, including operating systems, embedded systems, and high-performance applications such as games. Also, it was mandatory to use C as part of the project as it was the prescribed programming language for the CS102 course.

### SDL
Simple DirectMedia Layer (SDL) is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. Since the native graphics library in C is not sufficiently capable, we used SDL2 for our project.

## Filesystem Explanation
Below is a list of all the files and directories that the project contains:
- `arc.c` - The primary file where the driver code for the application is.
- `helpers.c` - Contains helper functions used in `arc.c`.
- `Makefile` - Instructions on how to compile the application.
- `SDL2.dll` - (Part of SDL2) Dynamic Link Library for SDL2.
- `SDL2_image.dll` - (Part of SDL2) Contains procedures and driver functions for handling image loading and decoding.
- `SDL2_ttf.dll` - (Part of SDL2) Wrapper around the FreeType and Harfbuzz libraries, allowing to use TrueType fonts to render text.
- `/sdlImage`, `/sdlMain`, `/sdlTTF` - (Part of SDL2) Contains the library code.
- `/headers` - Contains custom header files.
  - `background.h` - Structure definiton for game background.
  - `environment.h` - Constant declarations for environment parameters.
  - `paths.h` - Constant declaration for asset paths.
  - `pipe.h` - Structure definiton for in-game obstacles (pipes).
  - `sprite.h` - Structure definition for the main sprite.
- `/assests` - Contains visual game assets such as graphics, backgrounds and fonts.

## Setting Up the Project for Local Development
Clone this repository:
```
git clone https://github.com/tangerineArc/FlappyVibes.git
```

To compile the application, use `make`:
```
make
```

> [!NOTE]
> If `make` is not installed on your device, install it first for the command to work.

To run the game, execute the `arc.exe` file:
```
./arc
```

## Project Contributors
- Swagatam Pati (me)
- Azariah Peter
- Lakshmi Narasimham
- Asritha Pathivada
- Pratibha Mondal
- Ajay Kumar Saini
- Shubham Prakash
- Saikumar Malavath
- Saatvik Pandey
- Venkatesh Mishra
