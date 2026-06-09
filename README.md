# OpenGL Engine

OpenGL Engine is a small C++ learning project that renders a colored rectangle with OpenGL. It uses GLFW for window creation and input, GLAD for OpenGL function loading, and a simple shader abstraction for loading vertex and fragment shaders from a runtime resource file.

## Demo

![OpenGL Engine demo](assets/opengl-engine.gif)

## Features

- OpenGL rendering through a GLFW window.
- GLAD-based OpenGL function loading.
- Vertex array, vertex buffer, element buffer, and vertex buffer layout helper classes.
- Indexed rectangle rendering with per-vertex colors.
- Runtime shader loading from `shaders/basic.shader`.
- Object movement with `W`, `A`, `S`, `D`.
- Object rotation with `Q` and `E`.
- Runtime shader resources are copied next to the executable during the CMake build.

## Requirements

This project is currently set up for Windows.

Install the following tools before building:

1. **Visual Studio 2022** or **Visual Studio Build Tools 2022**
   - Install the `Desktop development with C++` workload.
   - Make sure the MSVC compiler and Windows SDK components are selected.
2. **CMake 3.20 or newer**
   - Download it from <https://cmake.org/download/> or install it with WinGet:

   ```powershell
   winget install Kitware.CMake
   ```

3. **Git**
   - Required if you want to clone the repository from the command line.

   ```powershell
   winget install Git.Git
   ```

4. **OpenGL 3.3 support**
   - Make sure your graphics driver supports OpenGL 3.3 or newer.

## Source Layout

```text
assets/                    Demo media used by this README
project/
  CMakeLists.txt           Main CMake project
  app/                     Application source, headers, and shader resources
  third_party/             Vendored GLFW, GLAD, and KHR dependencies
```

## Build Tutorial

Run the following commands from the repository root.

Create the build directory and generate the build system. This step only needs to be done once:

```powershell
cmake -S project -B build
```

Build the Release configuration:

```powershell
cmake --build build --config Release
```

After a successful Visual Studio generator build, the executable is typically located at:

```text
build/app/Release/opengl-engine.exe
```

The build also copies the required `shaders/` resource directory next to the executable.

## Running

1. Run `opengl-engine.exe`.
2. Use `W`, `A`, `S`, and `D` to move the rectangle.
3. Use `Q` and `E` to rotate the rectangle.
4. Press `Esc` to close the window.

If the shader resource directory is missing, make sure the executable is launched from the build output directory where CMake copied `shaders/basic.shader`.

## Development Notes

- The application target is defined in `project/app/CMakeLists.txt`.
- GLFW, GLAD, and KHR are included through `project/third_party`.
- Rendering setup is implemented in `project/app/src/main.cpp`.
- OpenGL wrapper classes are implemented under `project/app/src` with headers in `project/app/include`.
- The shader source is stored in `project/app/resources/shaders/basic.shader`.
