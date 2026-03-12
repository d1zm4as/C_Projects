# FibBenchmark

Small CLI to benchmark Fibonacci implementations with big integers.

## Build

```bash
make
```

## Run

```bash
./fib_bench --n 100000 --runs 3 --warmup 1 --mode user --print-len
./fib_bench --n -25 --mode user --print
```

## Replace the algorithm

Edit `user_fib.c` and implement `fib_user` with your algorithm.

## Notes

- `--verify` compares your result with the reference fast-doubling implementation.
- `--print` can be very slow for large `n`.
