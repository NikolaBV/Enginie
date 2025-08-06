# 2D Engine

A simple 2D game engine built with SDL2, featuring sprite rendering, tile maps, and an entity component system.

## Features

- **SDL2 Integration**: Cross-platform graphics, input, and audio
- **Sprite Rendering**: Animated character sprites with movement
- **Tile Map System**: Render tile-based maps from arrays
- **Entity Component System**: Modular game object architecture
- **Resource Management**: Texture loading and management

## Quick Start

### Prerequisites

- Visual Studio 2019 or later (with C++ development tools)
- Windows 10/11

### Clone and Run

1. **Clone the repository**
   ```bash
   git clone <your-repo-url>
   cd Enginie/2D Engine/2D Engine
   ```

2. **Option A: Use the batch file (Easiest)**
   ```bash
   run_game.bat
   ```
   This will automatically:
   - Copy all required resources and DLLs
   - Build the project (if needed)
   - Run the game

3. **Option B: Build in Visual Studio**
   - Open `2D Engine.sln` in Visual Studio
   - Build the project (Ctrl+Shift+B)
   - Run the executable from `x64/Debug/2D Engine.exe`

## Project Structure

```
2D Engine/
├── 2D Engine.sln              # Visual Studio solution
├── 2D Engine.vcxproj          # Project file with auto-copy settings
├── run_game.bat               # Automated setup and run script
├── README.md                  # This file
├── TROUBLESHOOTING.md         # Common issues and solutions
├── Main.cpp                   # Entry point
├── Game.cpp/h                 # Main game loop and initialization
├── GameObject.cpp/h           # Game object base class
├── TextureManager.cpp/h       # Texture loading and rendering
├── Map.cpp/h                  # Tile map system
├── EntityComponentSystem.cpp/h # ECS implementation
├── Components.cpp/h           # Component definitions
├── resources/                 # Game assets
│   ├── standard/             # Character sprites
│   ├── tiles/               # Map tiles
│   ├── fonts/               # Font files
│   └── sound/               # Audio files
├── dlls/                    # SDL2 and dependency DLLs
└── x64/                     # Build output directory
    └── Debug/
        ├── 2D Engine.exe
        ├── resources/        # Copied during build
        └── *.dll            # Copied during build
```

## How It Works

### Game Loop
1. **Initialize**: SDL2, window, renderer, load textures
2. **Handle Events**: Process input and window events
3. **Update**: Update game objects and entities
4. **Render**: Draw map tiles and sprites
5. **Repeat**: Continue until window is closed

### Current Demo
- A character sprite that moves diagonally across the screen
- A tile map with grass, dirt, and water tiles
- Entity component system tracking position

## Configuration

### Build Settings
The project is configured for:
- **Platform**: x64 (64-bit)
- **Configuration**: Debug/Release
- **Toolset**: Visual Studio 2022 (v143)

### Post-Build Events
The project automatically:
- Copies all DLLs from `dlls/` to output directory
- Copies `zlib1.dll` from SDL2_image library
- Copies all resources to output directory

## Troubleshooting

If you encounter issues:

1. **"Error loading texture" messages**: Check `TROUBLESHOOTING.md`
2. **Missing DLL errors**: Ensure all DLLs are in the output directory
3. **Build errors**: Verify Visual Studio C++ tools are installed

## Dependencies

- **SDL2**: Core graphics and input
- **SDL2_image**: PNG texture loading
- **SDL2_mixer**: Audio support (included but not used yet)
- **SDL2_ttf**: Font rendering (included but not used yet)

All dependencies are included in the `lib/` directory and `dlls/` folder.

## Development

### Adding New Features
1. **New Sprites**: Add PNG files to `resources/standard/`
2. **New Tiles**: Add PNG files to `resources/tiles/` and update `Map.cpp`
3. **New Components**: Extend `Components.h` and `EntityComponentSystem.cpp`

### Building for Distribution
1. Build in Release mode
2. Copy the entire `x64/Release/` directory
3. All dependencies are included automatically

## License

This project uses SDL2 libraries which are licensed under the zlib license.