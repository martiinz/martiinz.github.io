---
title: "Bash cheat sheet"
excerpt: ""
tags:
  - linux
  - bash
categories:
  - linux
---

```bash
# find in files
grep -rne 'pattern'    # recursive,lineno,regex
rgrep
```

## some screen stuff

### very basics

```bash
screen -S %name         # create session
screen -ls              # list sessions
screen -d -R %name      # reatach session, -d will detach from other location if attached somewhere
screen -X -S %name quit # Kill all windows and terminate entire screen session
ctl+a c                 # new shell
ctl+a #                 # switch shell, where # is the session number 
ctl+a "                 # show current shells
ctl+a d                 # detach session 
```

### splitting

```bash
ctl+a S                 # Split horizontally
ctl+a |                 # Split vertically
ctl+a X                 # remove current view
ctl+a tab               # focus splits
```





