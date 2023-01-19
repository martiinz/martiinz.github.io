---
title: "Yocto cheat sheet"
excerpt: "Basic Yocto Flow sumarized"
tags:
  - bash
  - embedded
  - linux
  - yocto
categories:
  - linux
---

## Resources

- [The Manual](https://docs.yoctoproject.org/dev/singleindex.html)

- [search for available recipes in the layer index](
  http://layers.openembedded.org/layerindex/branch/master/recipes/)

## Setup

```bash
# get all used tools
apt install gawk wget git diffstat unzip texinfo gcc build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm python3-subunit mesa-common-dev curl python libncurses-dev

# install repotool
mkdir ~/bin
curl https://storage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
chmod a+x ~/bin/repo

# add it to bashrc
export PATH=~/bin:$PATH

# get bsp and Layers
repo init -u https://path-to-bsp-repo -b gatesgarth
repo sync
```

## Basic Build

```bash
# set machine and build folder, initially you need to run it twice
DISTRO=my-distro MACHINE=my-machine source setup-environment build-folder/

# build image
bitbake image-minimal

# build SDK,  SDK = compiler, header, ++
bitbake image-minimal -c populate_sdk
# find sdk in tmp/deploy/sdk 

# build package
bitbake iproute2

# search an copy package
cd tmp/deploy/rpm/
find | grep iproute2
```

## Some Commands

```bash
# find all those variables you set in recipices
# replace my-image by any command/package
bitbake my-image -e | less

# find available images
ls layers/meta*/recipes*/images/*.bb

# show available recipes
bitbake-layers show-recipes

# show append files
bitbake-layers show-appends

# where is my kernel source
bitbake linux-karo -e | grep '^S='
# somewhere like: build/tmp/work-shared/qsmp-1570/kernel-source

# lists tasks and order
bitbake package -c listtasks
cat ./tmp/work/<machine_toolchain>/<package_name>/<package_version>/temp/log.task_order
```

## Kernel and Devicetree

### Kernel dev

```bash
# Kernel is provided by xyz
# PREFERRED_PROVIDER_virtual/kernel="xyz"
 
# configure and enter devshell
bitbake virtual/kernel -c configure
bitbake virtual/kernel -c devshell

# once you're in the devshell
# config
make menuconfig
make savedefconfig
 
## or do the same task with bitbake commands
# list tasks
bitbake -c listtasks virtual/kernel

# config kernel according recipes
bitbake virtual/kernel -c configure

# savedefconfig (to use ad complete kernelconfig)
bitbake virtual/kernel -c savedefconfig 

# menuconfig
bitbake virtual/kernel -c menuconfig 

# save diff to fragment
# to create a diff, first you need to create ".config" with default configuration (run menuconfig twice)
# then make your settings and create diff
bitbake virtual/kernel -c diffconfig

# to integrate changes in to image, add fragment in following folder
meta-my-layer/recipes-kernel/linux/xyz/cfg
# add it in following bbappend
meta-my-layer/recipes-kernel/linux/xyz_%.bbappend

# clean
bitbake virtual/kernel -c clean
```

### Devicetree dev

```bash
# compile in devshell, configure linux and open devshell and run make "devicetree name"
bitbake virtual/kernel -c configure
bitbake virtual/kernel -c devshell
make my-devictree.dtb

# find devicetree somewhere in the build folder
# tmp/work/poky-linux-gnueabi/mylinux/5.10-r0/build/arch/arm/boot/dts/my-devictree.dtb

# you can decompile a devictree manually with dtc
# follow all the includes and patches is annyoing, so this can help

# decompile
dtc -I dtb -O dts ./arch/arm/boot/dts/my-devictree.dtb > out.dts
# compile
dtc -I dts -O dtb -o my-devictree.dtb my-devictree.dts
```

### update on Target

```bash
# shows available disks
lsblk
# mount boot partition
mount /dev/mmcblk0p2 /boot/

# now update following files
/boot/ my-devictree.dtb
/boot/uImage
```
