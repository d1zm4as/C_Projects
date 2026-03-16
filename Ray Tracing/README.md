# Ray Tracing (2D Raycasting)

Simple SDL2-based 2D raycasting demo. A point light emits many rays in all directions and they stop when they hit the occluder circle or the screen bounds. Drag the mouse (with a button held) to move the light source.

## Build

Requires SDL2.

```bash
gcc main.c -o raytracing $(sdl2-config --cflags --libs) -lm
```

## Run

```bash
./raytracing
```

## Controls

- Mouse drag: move the light source
