# Tic-Tac-Toe in C

Console Tic-Tac-Toe project written in C with two game modes:

- `PvP`: player vs player
- `PvM`: player vs machine

## Team

- Pedro Jr
- Joao Gabriel
- Gleicy
- Leonel

## Project Structure

- `main.c`: menu and mode selection
- `pvp.c`: player-vs-player logic
- `pvm.c`: player-vs-machine logic

`main.c` includes both mode files directly and starts a terminal menu:

1. PvP  
2. PvM  
3. Exit

## Build

From the project folder:

```bash
gcc main.c -o tic_tac_toe
```

## Run

```bash
./tic_tac_toe
```

## Gameplay Notes

- Board is displayed in the terminal.
- In `PvP`, players alternate turns using `X` and `O`.
- In `PvM`, the player uses `X` and the CPU uses `O`.
- The screen is cleared between turns (`system(\"clear\")`), so this is intended for Unix-like terminals.
