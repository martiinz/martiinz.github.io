```bash
# find in file
grep -rnw . -e 'search term'
# grep -recursive,lineno,word <FOLDER> -e <PATTERN>
```

# some screen stuff

## very basics
```bash
screen -S name          # create session
screen -ls              # list sessions
screen -d -R name       # reatach session, -d will detach from other location if attached somewhere
ctl+a c                 # new shell
ctl+a #                 # switch shell, where # is the session number 
ctl+a "                 # show current shells
ctl+a d                 # detach session 
```

## splitting
```bash
ctl+a S                 # Split horizontally
ctl+a |                 # Split vertically
ctl+a X                 # remove current view
ctl+a tab               # focus splits
```





