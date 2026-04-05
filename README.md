# NESort

A sorting visualizer... for the NES/Famicom.

## Usage

Pre-built binaries coming soon...

[Mesen](https://www.mesen.ca/) is the recommended emulator
due to its accuracy and compatibility with the generated
debug symbols. Despite this, any reasonably accurate emulator
should be able to run it (FCEUX, BizHawk, RetroArch, etc.).

The ROM *should* be usable with both flash cartridges and
actual productions ([see Cartridge Production](#cartridge-production))
but console functionality is unverified.

## Building

The only requirement for building the ROM and debug symbols
is the [cc65 development suite](https://cc65.github.io/).

### Windows

Install cc65 and (optional) add it to your PATH environment
variable. Run [build.bat](build.bat). The Windows snapshot
linked to in [cc65's website](https://cc65.github.io/) should
be sufficient.

### Linux

Install cc65 and ensure that it is accessible via PATH. **Unless
your distro is rolling release, it is unlikely that the version
included will be compatible with this project. It is recommended
to compile and install manually or add a (trusted) repository.**

Run [build.sh](build.sh).

## Cartridge Production

NESort uses a typical NROM-256 mapper (iNES mapper 0 with 32 KiB
PRG ROM, 8 KiB CHR ROM) and vertical mirroring (PPU A10 -> CIRAM
A10).
