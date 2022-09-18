---
title: "Bootlin embedded Linux Labs"
excerpt: "Notes and solution for Bootlin embedded Linux Labs"
tags:
  - bash
  - embedded
  - linux
categories:
  - linux
---

Notes and solution for [Bootlin embedded Linux Labs](https://bootlin.com/training/embedded-linux/). Thank you Michael for giving this course, I really can recommend it!

## Toolchain

### Build crosstool NG

```bash
# get crosstool
git clone https://github.com/crosstool-ng/crosstool-ng.git
cd crosstool-ng/
git checkout 79fcfa17

# build
./bootstrap
./configure --enable-local
make

# use crosstool
./ct-ng help
./ct-ng list-samples

./ct-ng arm-cortexa5-linux-uclibcgnueabihf
./ct-ng menuconfig
# follow to doc for settings
./ct-ng build
```

### Use

```bash
# add compiler to path
PATH=$PATH:$HOME/x-tools/arm-training-linux-uclibcgnueabihf/bin

cd <HERE>/embedded-linux-labs/toolchain
arm-linux-gcc -o hello hello.c
# to link clib static 
# arm-linux-gcc -o hello --static ./hello.c

# run on qemu
sudo apt install qemu-user

# this will fail, cause missing uclib
qemu-arm hello

# file info 
file hello 

# find uclib location
find ~/x-tools -name ld-uClibc.so.0

qemu-arm -L ~/x-tools/arm-training-linux-uclibcgnueabihf/arm-training-linux-uclibcgnueabihf/sysroot hello

# clean if you're limited in space, will give you ~10 GB
./ct-ng clean 
```

## Das U-Boot

### Compile and Flash

```bash
cd <HERE>/embedded-linux-labs/bootloader

# get Microchip Flashing Tool 
wget https://ww1.microchip.com/downloads/en/DeviceDoc/sam-ba_3.3.1-linux_x86_64.tar.gz
tar xf sam-ba_3.3.1-linux_x86_64.tar.gz

# get uboot source
git clone https://gitlab.denx.de/u-boot/u-boot
cd u-boot
git checkout v2020.07

# get device tree compiler
apt install device-tree-compiler

# add user to serial group, for serial operations
sudo add user ${USER} dialout
# logout/login

# get configs in ./configs
make sama5d3_xplained_nandflash_defconfig
make menuconfig

# compile UBoot
export CROSS_COMPILE=arm-linux-
export ARCH=arm
make

# Boot Target in Boot Monitor Mode 
# remove NAND Jumper and reset
 
# erase NAND, command will find /dev/ttyACM0 itsself
./sam-ba_3.3.1/sam-ba -p serial -b sama5d3-xplained -a nandflash -c erase
# flash the U-Boot SPL
./sam-ba_3.3.1/sam-ba -p serial -b sama5d3-xplained -a nandflash -c writeboot:u-boot/spl/u-boot-spl.bin
# flash the U-Boot binary
./sam-ba_3.3.1/sam-ba -p serial -b sama5d3-xplained -a nandflash -c write:u-boot/u-boot.bin:0x40000

# Check Uboot on Serial line

# open console
picocom -b 115200 /dev/ttyUSB0

# reset and check U-Boot SPL and U-Boot for Date
```

### Setup TFTP

```bash
# install server and client
apt install tftpd-hpa tftp

# check status, you might need to start it
service tftpd-hpa status

# create content
cd /srv/tftp
echo "Hello" > hello.txt

# test tftp locally
tftp localhost
tftp> get hello.txt

# connect the board to Ethernet and start
# configure network in U Boot
=> setenv ipaddr 192.168.1.101
=> setenv serverip 192.168.1.9
 
# fist time you can also set a MAC
=> setenv ethaddr 12:34:56:ab:cd:ef
=> saveenv

# test the tftp connection
=> tftp 0x22000000 hello.txt

# memory dump
=> md 0x22000000

```

## Kernel

### get and build

```bash
# get and uncompress
mkdir -p <HERE>/embedded-linux-labs/kernel
cd <HERE>/embedded-linux-labs/kernel

wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.11.22.tar.gz
tar -xf linux-5.11.9.tar.gz

# set Path and compile variable
# it might be a good idea do source the environment from a script
export PATH=$PATH:$HOME/x-tools/arm-training-linux-uclibcgnueabihf/bin
export CROSS_COMPILE=arm-linux-
export ARCH=arm

# set config
make help # shows you all defconfigs and some more stuff
# config is named after the cpu
make defconfig sama5_defconfig

# most common config tools
make xconfig
make menuconfig # note the shortcuts m y n ? / and from search you can directly jump to the option, by pressing the number in ()

# install libssl-dev, why?
apt install libssl-dev

# make, use option -j, number of jobs with N-cpu*2
time make -j 8 
```

### load over TFTP

Get Kernel and DTB from TFTP and boot it from there. This will be useful while developing Kernel and Devicetree

```bash
# copy output to tftp server
sudo cp arch/arm/boot/zImage /srv/tftp/
sudo cp ./arch/arm/boot/dts/at91-sama5d3_xplained.dtb /srv/tftp/

# get the stuff from uboot
=> tftp 0x21000000 zImage
=> tftp 0x22000000 at91-sama5d3_xplained.dtb
=> bootz 0x21000000 - 0x22000000
# kernel will boot, but end up in a kernel panic since we havent provided a rootfs yet

# we can automate above steps by setting boot command
# orignal bootcmd
=> echo $bootcmd
nand read 0x21000000 0x180000 0x80000;nand read 0x22000000 0x200000 0x600000;bootz 0x22000000 - 0x21000000

# our development bootcmd, loading kernel from tftp
=> setenv bootcmd 'tftp 0x21000000 zImage; tftp 0x22000000 at91-sama5d3_xplained.dtb; bootz 0x21000000 - 0x22000000'
=> saveenv
=> reset
```

### flash to NAND

Load Kernel and DTB from TFTP, flash it to NAND, boot from NAND

```bash
# erase NAND areas for DTB and Kernel
# nand erase <offset> <size>
=> nand erase 0x180000 0x20000
=> nand erase 0x1a0000 0x500000

# load Kernel and DTB into RAM
=> tftp 0x21000000 zImage
=> tftp 0x22000000 at91-sama5d3_xplained.dtb

# and flash the stuff to NAND
# nand write <RAM addr> <offset> <size>
=> nand write 0x22000000 0x180000 0x20000
=> nand write 0x21000000 0x1a0000 0x500000

# powercycle the board to clear NAND

# Load image from NAND
=> nand read 0x22000000 0x180000 0x20000
=> nand read 0x21000000 0x1a0000 0x500000
=> bootz 0x21000000 - 0x22000000

# save the tftp bootcommand for later
=> setenv bootcmdtftp ${bootcmd}

# set the bootcommand to boot from NAND (editenv or setenv)
=> setenv bootcmd 'nand read 0x22000000 0x180000 0x20000; nand read 0x21000000 0x1a0000 0x500000; bootz 0x21000000 - 0x22000000'
=> setenv bootcmdnand ${bootcmd} # just for later use
=> savenv
=> run bootcmd

# you might want to script flashing NAND
=> setenv flash_tftp2nand 'nand erase 0x180000 0x20000; nand erase 0x1a0000 0x500000; tftp 0x21000000 zImage; tftp 0x22000000 at91-sama5d3_xplained.dtb; nand write 0x22000000 0x180000 0x20000; nand write 0x21000000 0x1a0000 0x500000'
=> savenv
=> run flash_tftp2nand
```

## Tiny Rootfs Busybox

Build a tiny rootfs, mount it over nfs for development

### Kernel requirements

```bash
# make shure your Kernel supports DEVTMPFS_MOUNT, NFS_FS, ROOT_NFS
# what about NFS_FSCACHE?
```

### Setup NFS Server

```bash
# create nfsroot folder to store our file system
mkdir -p <HERE>/embedded-linux-labs/tinysystem/nfsroot
cd <HERE>/embedded-linux-labs/tinysystem/

# install NFS Server
apt install nfs-kernel-server

# add following line to /etc/export
/home/tin/tech_knowledge/embedded-linux-labs/tinysystem/nfsroot 192.168.1.101(rw,no_root_squash,no_subtree_check)

# and restart (to reload the folders)
service nfs-kernel-server restart

# set bootargs from uboot and boot
=> setenv bootargs ${bootargs} root=/dev/nfs ip=192.168.1.101:::::eth0 nfsroot=192.168.1.9:/home/tin/tech_knowledge/embedded-linux-labs/tinysystem/nfsroot,nfsvers=3,tcp rw
=> saveenv
=> run bootcmd
# you should see: 
# VFS: Mounted root (nfs filesystem) on device 0:14.
# devtmpfs: error mounting -2

# if you have any errors mounting NFS, look in the NFS server logs (/var/log/syslogs)

# devtmpfs tries to mount /dev from rootfile system
mkdir -p <HERE>/nfsroot/dev

# reboot and you will see the kernel complaining about "no init found"
# for guidance see: https://elixir.bootlin.com/linux/latest/source/Documentation/admin-guide/init.rst
```

### BusyBox

```bash
wget https://busybox.net/downloads/busybox-1.33.1.tar.bz2
tar -xf busybox-1.33.1.tar.bz2

# load provided config
cd busybox-1.33.1
cp ../data/busybox-1.33.config .config
make menuconfig

# set install folder "PREFIX [=../nfsroot]"
# set options you want

make install

# reboot target, you should reach the shell now
```

### Virtual file systems

```bash
# we dont have the virtual /proc filesystem now
# run ps, it will complain

# create dirs in the nfsroot
mkdir -p embedded-linux-labs/tinysystem/nfsroot/{proc,sys}

# mount -t type device mountpoint
mount -t proc nodev proc/
mount -t sysfs nodev sys/

```

### inittab

```bash
mkdir -p embedded-linux-labs/tinysystem/nfsroot/etc

# create an inittab confile (used by /sbin/init)
# for config see https://elixir.bootlin.com/busybox/latest/source/examples/inittab
vim etc/inittab

# we use a minimal init
::sysinit:/etc/init.d/rcS     # thats our system init script
ttyS0::askfirst:/bin/sh       # set shell on the real serial terminal
::shutdown:/bin/umount -a -r  # unmount and mount in readonly (-r) for shutdown
::restart:/sbin/init

# and create the startup script
mkdir etc/init.d
vim etc/init.d/rcS

# mount the virtual file system, be aware bash is not in busybox
#!/bin/sh
mount -t proc nodev proc/
mount -t sysfs nodev sys/

# make rcS executable
chmod +x etc/init.d/rcS

# sidenote: #!/bin/sh # redirects file content to its shell input
```

### switch to shared libs

Don't do that in realworld. It's just to get an understanding of minimal files used..

```bash
# compile hello.c, use --static to to include uClibc
arm-linux-gcc hello.c -o hello
cp hello ../nfsroot/

# running that on target leads in the strange error
# /bin/sh: ./hello: not found
# we're missing ld-uClibc.so.0

# cp the missing file to nfsroot
mkdir  nfsroot/lib
cp ~/x-tools/arm-training-linux-uclibcgnueabihf/arm-training-linux-uclibcgnueabihf/sysroot/lib/ld-uClibc.so.0 nfsroot/lib
# cp libc.so.0

# compile busybox without the static option, busybox size before
# -rwxrwxr-x 1 tin tin 415448 Jul 20 12:53 busybox
STATIC=n
STATIC_LIBGCC=n

make 
make install

# size after 
# -rwxrwxr-x 1 tin tin 272428 Jul 23 19:13 busybox

```

### Initramfs

Rootfile system from memory

- fast booted
- you would need to recompile kernel every time you update rootfs

```bash
# preapare rootfs
cd tinysystem/nfsroot

# link init to /sbin/init
ln -s sbin/init .

# you  need to mount the console device in /etc/init.d/rcS
mount -t devtmpfs nodev /dev

# config Kernel
cd kernel/linux-5.11.22
make menuconfig
#set  CONFIG_INITRAMFS_SOURCE=<my NFS root>

make
# the zImage is bigger now, since it contains a rootfs
# size before 3584872
# size after  4018144

# copy zImage to tftp (or where ever you boot from..)
cp arch/arm/boot/zImage /srv/tftp/

=> setenv bootcmd ${bootcmdtftp}; saveenv; boot

# check whats mounted on /
mount
# none on / type rootfs (rw)

# bootime "benchmark" from "starting Kernel" to console
# intitramfs 10 s
# regular /  11 s

```

## Blockfilesystem

Flash the tiny rootfs to and SD card (or an emmc)

### preparation (kernel and SD)

setup webserver first

```bash
make menuconfig
# CONFIG_INITRAMFS_SOURCE=
# CONFIG_SQUASHFS=y
# CONFIG_EXT4_FS=y

# build and Kernel load to nand
make 
sudo cp arch/arm/boot/zImage /srv/tftp/
=> run flash_tftp2nand
=> setenv bootcmd ${bootcmdnand}; saveenv; boot

# check support for squashfs and ext4
cat /proc/filesysystems

# insert SD, check device enumaration (dmesg), umount if necessary
umount /dev/sdb*

# create partitions we're going to use
cfdisk /dev/sdb
# sdb1 64M Bootable
# sdb2  8M
# sdb3  1G
```

### RW Data partition

```bash
# create journaled filesystem for data on sdb3
# -L assigns volume name
# -E nodiscard, no bad block discarding (will save os some minutes, but useful to isolate bad blocks?)
mkfs.ext4 -L data -E nodiscard /dev/sdb3

# mount and copy www data
mount /dev/sdb3 /media/mysd/
cp tinysystem/data/www/upload/files/* /media/mysd/

# move SD to target, check partitions, and mount
cat /proc/partitions # will show you the mmcblk0
mount /dev/mmcblk0p3 /www/upload/files/

# add mount instruction to startup script
echo "mount -t ext4 /dev/mmcblk0p3 /www/upload/files/" >> /etc/init.d/rcS
```

### RW tmpfs

temporary file system,
used for tmp logs, ....

```bash
# create folder and mount tmpfs
mkdir -p var/log
mount -t tmpfs log /var/log

# if it works add mount to /etc/init.d/rcS
echo "mount -t tmpfs log /var/log" >> etc/init.d/rcS

# confiugure the webserver to store the logfile in our tmpfs
# these logfiles will be stored in RAM, and are lost on reboot
vim www/cgi-bin/upload.cfg
```

### Rootfs RO SquashFS

store the rootfs

```bash
# prepare and flash image on host
apt install squashfs-tools
mksquashfs nfsroot/ rootfs.sqfs -noappend
dd if=rootfs.sqfs of=/dev/sdb2

# test squashfs on target, and see if there is my rootfs
mount dev/mmcblk0p2 tmp/

# boot from sqashfs, set bootcmd, set rootwait
=> setenv bootargsnfs ${bootargs} # just for later use
=> setenv bootargs console=ttyS0 root=/dev/mmcblk0p2 ip=192.168.1.101:::::eth0 rootwait
=> saveenv

```

### Kernel

```bash
# create fat32 partition called boot
mkfs.vfat -F 32 -n boot /dev/sdb1

# copy zImage and DTB so the new partition

# load DTB and Kernel from sd card
=> setenv bootcmd 'fatload mmc 0:1 0x22000000 at91-sama5d3_xplained.dtb; fatload mmc 0:1 0x21000000 zImage; bootz 0x21000000 - 0x22000000'
=> setenv bootcmdsd ${bootcmd}
=> saveenv

# we migth wanna mount the bootpartition, just for info
```

### U-Boot

```bash
# store the U-Boot variables in a textfile
=> printenv 
# copy paste to bootloader/uboot_env.txt

# recompile uboot with the mmc options 
make sama5d3_xplained_mmc_defconfig

# copy spl/boot.bin and u-boot.img to the /dev/sdb1 partition

# reboot and check your uboot version
=> version
```

## Raw Flash, UBI

### prepare

```bash
apt install mtd-utils

# remove SD card Uboot compiled with mmc config is incompatible with UBI/Linux (bug)

# recompile Kernel kernel with UBIFS support and cmdline partition table
MTD_UBI=y
UBIFS_FS=y
MTD_CMDLINE_PARTS=y
```
