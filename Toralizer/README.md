# Toralizer

Small LD_PRELOAD wrapper that intercepts `connect()` and routes TCP connections through a SOCKS4 proxy (default `127.0.0.1:9050`, e.g. Tor).

## Build

```bash
make
```

This produces a shared library named `toralize`.

## Usage

```bash
LD_PRELOAD=./toralize <command>
```

Example:

```bash
LD_PRELOAD=./toralize curl https://example.com
```

## Notes

- Requires a SOCKS4 proxy listening on `127.0.0.1:9050`.
- The proxy settings are in `toralizer.h` (`PROXY`, `PROXYPORT`, `USERNAME`).
