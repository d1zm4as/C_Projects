# XOR Encryption Demo (C)

Small C example showing how XOR can encrypt and decrypt a character with the same key.

## What it demonstrates

- `ciphertext = cleartext ^ key`
- `newcleartext = ciphertext ^ key`

The second XOR operation restores the original value.

## Build and run

```bash
gcc xor.c -o xor_demo
./xor_demo
```
