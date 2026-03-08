# UI (ncurses)

Terminal UI experiments using the `ncurses` library.

## Files

- `ncurses.c`: basic input/output flow (`printw`, `getch`, `refresh`).
- `ncurses2.c`: cursor position and movement demo (`getyx`, `move`).
- `arrow.c`: simple movement with arrow keys.

## Build examples

```bash
gcc ncurses.c -o ncurses_demo -lncurses
gcc ncurses2.c -o ncurses2_demo -lncurses
gcc arrow.c -o arrow_demo -lncurses
```

Run with `./<binary>`.
