#!/bin/bash

# install dep
sudo apt update
sudo apt install -y overlayroot

mkdir -p /tmp/test
cd /tmp/test

# gzip
sudo cp /boot/initrd initrd.gz
gzip -d initrd.gz

# lz4
lz4 -d /boot/initrd.img-5.10.104-tegra initrd

sudo cpio -idv < initrd




./init
./conf
./scripts
./usr/lib/modules/5.10.104-tegra/kernel/fs/overlayfs/overlay.ko
./usr/lib/modprobe.d

(/usr/bin/find . |/bin/cpio -R 0:0 -o -H newc) |/bin/gzip > /boot/initrd.qomolo
