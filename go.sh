#!/bin/bash
#rm -rf /usr/geniux/img/geniusos.img
nasm -I ./include/ -o mbr.bin mbr.S
dd if=mbr.bin of=../geniusos.img bs=512 count=1 conv=notrunc
echo "disk write success!!"
nasm -I ./include/ -o loader.bin loader.S
dd if=loader.bin of=../geniusos.img bs=512 count=2 seek=2 conv=notrunc
