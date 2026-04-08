# Sort Visualizer

A Raylib-based sorting visualizer with a menu, step-by-step playback, speed control, and array size slider.

## Build

```bash
gcc main.c sort_trace.c Sort_Algorithms/*.c -I. -o main \
  -lraylib -lm -lpthread -ldl -lrt -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXxf86vm
```

## Run

```bash
./main
```

## Controls

**Menu**
- `Up/Down`: select algorithm
- `Enter`: start visualization

**Visualizer**
- `Space`: play/pause
- `Right`: step one operation
- `R`: shuffle and reset
- `M`: back to menu
- `+ / -`: speed up/down
- **Sliders**: adjust speed and array size with the mouse

## Algorithms

- Bubble Sort
- Insertion Sort
- Selection Sort
- Quick Sort
- Merge Sort
- Heap Sort
- Shell Sort
- Counting Sort
- Radix Sort
- Bucket Sort

## Notes

The visualizer records a trace of swaps/writes/compares, then replays it. This keeps animation smooth and consistent across algorithms.
