# Analog Clock

Simple analog clock rendered with raylib. The hands are updated in real time using the local system time.

## Build

From this folder:

```bash
make
```

If `pkg-config` is not available:

```bash
sudo apt install pkg-config
```

## Run

```bash
./app
```

## Notes

This project links against raylib and the system graphics libraries. The `Makefile` uses `pkg-config` when available and falls back to explicit linker flags.
