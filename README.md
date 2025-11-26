# FPS 3D Game - Raylib

A first-person 3D game with jump mechanics built with raylib and C.

## Features

- ✅ **3D FPS Camera** - Full first-person controls with mouse look
- ✅ **Jump System** - Realistic physics with gravity
- ✅ **Player Movement** - WASD controls with free camera rotation
- ✅ **Debug Info** - Real-time position and velocity display

## Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward/left/backward/right |
| `Mouse` | Look around |
| `Space` | Jump |
| `Y` | Reset position (debug) |
| `ESC` | Exit gameplay |

## Building

### Requirements
- CMake 3.11+
- C compiler (GCC, Clang, MSVC)
- raylib (automatically downloaded by CMake)

### Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# Build
mkdir build && cd build
cmake ..
make

# Run
./raylib-game-template/raylib-game-template
```

### macOS

```bash
# Install Xcode Command Line Tools
xcode-select --install

# Build
mkdir build && cd build
cmake ..
make

# Run
./raylib-game-template/raylib-game-template
```

### Windows (Visual Studio)

```bash
# Using CMake
mkdir build
cd build
cmake ..
cmake --build . --config Release

# Run
.\build\raylib-game-template\Release\raylib-game-template.exe
```

Or open `projects/VS2022/raylib_game_template.sln` in Visual Studio.

## Project Structure

```
├── src/
│   ├── raylib_game.c       # Main game loop
│   ├── screen_gameplay.c   # FPS gameplay logic
│   ├── screen_title.c      # Title screen
│   ├── screen_logo.c       # Logo screen
│   ├── screens.h           # Screen declarations
│   └── resources/          # Game assets
├── build/                  # Build output (gitignored)
├── CMakeLists.txt          # CMake configuration
└── README.md
```

## Game Physics

The jump system uses realistic physics:

```c
// Configurable values
jumpForce = 8.0f;      // Initial jump velocity
gravity = -20.0f;      // Downward acceleration
groundLevel = 2.0f;    // Player eye height
```

Modify these in `src/screen_gameplay.c` to adjust jump feel.

## Credits

This project is based on [raylib-game-template](https://github.com/raysan5/raylib-game-template) by **Ramon Santamaria** ([@raysan5](https://github.com/raysan5)).

Built with [raylib](https://www.raylib.com/) - A simple and easy-to-use library to enjoy videogames programming.

## License

This project is licensed under the zlib/libpng license - see the [LICENSE](LICENSE) file for details.

The original raylib-game-template is also under the zlib/libpng license.

---

**Author**: JefersonDeLaCruz  
**Year**: 2025
