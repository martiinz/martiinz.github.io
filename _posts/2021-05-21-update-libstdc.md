---
title: "Update libstdc++ on Ubuntu"
excerpt: ""
tags:
  - linux
  - admin
categories:
  - linux
---

Fist things first, get a new OS!

If you cant, install the newest libstdc++6 on Ubuntu 16.04

In case an application misses **GLIBCXX_3.4.22** on the Target:

```bash
# check installed versions
# we (or any libraray) wants GLIBCXX_3.4.22
strings /usr/lib/arm-linux-gnueabihf/libstdc++.so.6 | grep GLIBCXX


# create file /etc/apt/sources.list.d/toolchain.list
# xenial -> ubuntu 16.04
# and add following lines
deb http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu xenial main   
deb-src http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu xenial main 

# add key
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 1E9377A2BA9EF27F

sudo apt update
sudo apt install libstdc++6
```
