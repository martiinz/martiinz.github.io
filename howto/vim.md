## some basics..
```bash
# open multiple files
vim -p file1 file2 file3

# save as sudo 
:w !sudo tee %
```

## some more in editor basics
```bash
## tabs
:tabnew file    # new
:tabn           # next  
:tabp           # previous
:tabr           # rewind (first)
:tabl           # last
:tabs           # list
:tabn x         # forward x

:r              # reload
```


## a small .vimrc
```bash
# replace tab with spaces
set tabstop=4 shiftwidth=4 expandtab

# map tab moves to ctl-T, Arrows
map <C-t><up> :tabr<cr>
map <C-t><down> :tabl<cr>
map <C-t><left> :tabp<cr>
map <C-t><right> :tabn<cr>
```
