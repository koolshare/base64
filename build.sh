#!/bin/sh

CC=arm-brcm-linux-uclibcgnueabi-gcc
STRIP=arm-brcm-linux-uclibcgnueabi-strip
#CC=gcc
#STRIP=strip

rm -f base64_encode
$CC -Os -std=gnu99 base64_encode.c -o base64_encode

$STRIP base64_encode
ln -sf base64_encode base64_decode 
