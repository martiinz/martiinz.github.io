```bash
# find in file
grep -rnw . -e 'search term'
# grep -recursive,lineno,word <FOLDER> -e <PATTERN>
```

# some screen stuff

```bash
# create session
screen -S sessionname

# list sessions
screen -ls

# reatach session, -d will detach from other location if attached somewhere
screen -d -R sessionname

# new shell
ctl+a c

# switch shell, where # is the session number 
ctl+a #

# show current shells
crl+a "

# detach session 
ctl+a d
```
