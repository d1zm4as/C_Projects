# DNS Client

A small C DNS lookup client that sends a UDP query to a nameserver and prints the returned `A`, `AAAA`, or `CNAME` records.

## Build

```bash
make
```

This produces a `dnscli` binary in the project root.

## Usage

```bash
./dnscli <name> [nameserver] [A|AAAA|CNAME]
```

Examples:

```bash
./dnscli example.com
./dnscli example.com 1.1.1.1 AAAA
./dnscli openai.com 8.8.8.8 CNAME
```

If no nameserver is provided, the client defaults to `8.8.8.8`.
If no query type is provided, the client defaults to `A`.

## Output

The client prints each matching record on its own line. For example:

```text
93.184.216.34
```

## Notes

- The client currently uses UDP DNS queries directly.
- The sandbox used for development does not allow outbound network access, so live lookup testing may need to be done locally on your machine.
