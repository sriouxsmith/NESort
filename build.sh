#!/usr/bin/env bash

OUT=bin/NESort
SRC=$(find src -type f \( -name '*.c' -o -name '*.a65' \))

mkdir -p bin
cl65 -T -Ois -g -t none -C nrom-256.l65 -Wl --dbgfile,$OUT.dbg $SRC -o $OUT.nes

find . -name '*.o' -delete
