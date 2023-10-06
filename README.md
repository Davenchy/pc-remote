# PC-Remote

- Control your Linux Machine from anywhere inside LAN.

## Build

- use __make__ command to build this project.

```bash
$ make build clean
$ ./pc_remote
```

## Config

- By default PC-Remote will listen on port __5050__, you can set the env var `PC_REMOTE_PORT` to change the port.

- By default PC-Remote will load scripts from `$HOME/.config/remote_scripts/` path, you can set the env var `PC_REMOTE_SCRIPTS_PATH` to change the scripts path.

## Scripts

- Any executable file is a script and will be called by sending its name from the client to PC-Remote.

- Example Script at path `$HOME/.config/remote_scripts/lock`:

```bash
#!/bin/bash
# lock and turn off screen
xset dpms force suspend
```

- Don't forget to set executable permission to scripts otherwise it won't work.

```bash
$ chmod +x $HOME/.config/remote_scripts/lock
```

## Client

- Using __netcat__ as a client to connect to PC-Remote.

```bash
$ nc 0 5050
> ls
lock
> lock
!> Executing script: lock
>
```

## PC-Remote Commands

- PC-Remote has a list of built-in commands.

| Command | Description               |
|:-------:|:------------------------- |
| help    | Display this help message |
| ls      | List all loaded scripts   |
| reload  | Reload all scripts        |
| quit    | Exit PC-Remote            |
