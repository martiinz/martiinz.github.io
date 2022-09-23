---
title: "Windows Terminal Settings"
excerpt: "make Win terminal tool feel like the KDE/Gnome one"
tags:
  - tools
categories:
  - tools
---    

I love WSL, with the terminal tool, it feel almost like home. Thank you Microsoft.

Keybindings for a look and feel more or less like KDE Konsole Programm. [Find Doc at MS](https://docs.microsoft.com/en-us/windows/terminal/customize-settings/actions)

```json
    "actions":
    [
        {
            "command": 
            {
                "action": "copy",
                "singleLine": false
            },
            "keys": "ctrl+shift+c"
        },
        {
            "command": "find",
            "keys": "ctrl+shift+f"
        },
        {
            "command": "paste",
            "keys": "ctrl+shift+v"
        },
        {
            "command": 
            {
                "action": "splitPane",
                "split": "auto",
                "splitMode": "duplicate"
            },
            "keys": "alt+shift+d"
        },
        { 
            "command": "duplicateTab", 
            "keys": "ctrl+shift+t"
        },
        { 
            "command": "nextTab", 
            "keys": "shift+right"
        },
        { 
            "command": "prevTab", 
            "keys": "shift+left"
        },
        { 
            "command": { "action": "moveTab", "direction": "backward" }, 
            "keys": "ctrl+shift+left"
        },
        { 
            "command": { "action": "moveTab", "direction": "forward" }, 
            "keys": "ctrl+shift+right"
        },
        { 
            "command": "scrollUp", 
            "keys": "shift+up"
        },
        {
            "command": "scrollDown", 
            "keys": "shift+down"
        }
    ],
```
