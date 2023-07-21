# rubiks-cube
A Rubik's Cube simulator written in C++ and OpenGL.
![Application screenshot](https://github.com/oliver-hamilton/rubiks-cube/blob/main/assets/screenshot-1.png?raw=true)

# Setup
On Linux, run the following command from within the `src/` directory:
```bash
$ g++ rubiks-cube.cpp shader.cpp -I . -lglut -lGLU -lGL -lGLEW -lglfw -o rubiks-cube
```
This will produce a binary `rubiks-cube` inside the `src/` directory that can then be run.

## Controls
To change the camera position, use the arrow keys.
To rotate a face of the cube, press one of the following letters on the keyboard:
- U - Up
- D - Down
- L - Left
- R - Right
- F - Front
- B - Back
