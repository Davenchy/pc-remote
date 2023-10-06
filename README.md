# PC-Remote

- Control your Linux Machine from anywhere.

## Build

- use __make__ command to build this project.

```bash
$ make build clean
$ ./pc_remote
```

## Configuration and Environment Variables

| Env Var | Default | Description |
|:-------:|:-----------:|:-----------:|
| PC_REMOTE_PORT | 5050 | Port to listen on. |
| PC_REMOTE_SCRIPTS_PATH | $HOME/.config/remote_scripts/ `if XDG_CONFIG_HOME is set` __or__ $HOME/remote_scripts/ | Path to scripts directory. |

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
