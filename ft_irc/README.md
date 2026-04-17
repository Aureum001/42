# ft_irc starter

Minimal C++98 IRC server base to start collaborative development.

## Build

```bash
make
```

## Run

```bash
./ircserv 6667 secret
```

- `port`: 1024-65535
- `password`: required by `PASS`

## Quick test (netcat)

Terminal 1:
```bash
./ircserv 6667 secret
```

Terminal 2:
```bash
nc 127.0.0.1 6667
PASS secret
NICK alice
USER alice 0 * :Alice
PING :hello
QUIT
```

## Implemented starter behavior

- Multi-client accept loop using `select`
- Basic command parsing by line (`\r\n` or `\n`)
- `PASS`, `NICK`, `USER`, `PING`, `QUIT`
- Numeric replies (`001`, `431`, `433`, `451`, `461`, `464`)
- Graceful shutdown on `Ctrl+C`

## Suggested next steps

- Add an `IRCMessage` parser class (prefix, command, params, trailing)
- Add proper registration state checks and RFC-compliant numerics
- Add operator commands (`KICK`, `INVITE`, `TOPIC`, `MODE`)
- Add test scripts for protocol flows
