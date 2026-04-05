@echo off
setlocal enabledelayedexpansion

set OUT=bin\NESort
if not exist bin mkdir bin

set SRC=
for /r src %%f in (*.c *.a65) do set SRC=!SRC! "%%f"

cl65 -T -Ois -g -t none -C nrom-256.l65 -Wl --dbgfile,%OUT%.dbg %SRC% -o %OUT%.nes

for /r %%f in (*.o) do del /f /q "%%f"
