# NESort

A sorting visualizer... for the NES/Famicom.

~~24~~ 16 sorting algorithms:

1. Selection Sort
2. Heap Sort
3. Insertion Sort
4. Shell Sort
5. Bubble Sort
6. Comb Sort
7. Gnome Sort
8. Cocktail Shaker Sort
9. Quick Sort (Hoare partition, LR pointers)
10. Merge Sort (Top-down, recursive)
11. Introspective Sort
12. ~~Tim Sort~~
13. Counting Sort
14. ~~LSD Radix Sort (base 4)~~
15. ~~MSD Radix Sort (base 4)~~
16. ~~Cycle Sort~~
17. ~~Circle Sort~~
18. ~~Pancake Sort~~
19. Bitonic Merge Sort (iterative)
20. ~~Ford-Johnson Algorithm (merge-insertion sort)~~
21. ~~Block Merge Sort (WikiSort)~~
22. Stooge Sort
23. Slow Sort
24. Bogo Sort

*Crossed out sorts coming soon*

## Usage

Pre-built binary: [Latest release](https://github.com/sriouxsmith/NESort/releases)

[Mesen](https://www.mesen.ca/) is the recommended emulator
due to its accuracy and compatibility with the generated
debug symbols. Despite this, any reasonably accurate emulator
should be able to run it (FCEUX, BizHawk, RetroArch, etc.).

The ROM is usable with flash cartridges on actual productions ([see Cartridge Production](#cartridge-production))
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

NESort uses a typical NROM-256 mapper (iNES mapper 0 with
32 KiB PRG ROM, 8 KiB CHR ROM). A full 32 KiB ROM (as
opposed to 16 KiB) is necessary to contain the binary.

### Mirroring

The provided iNES header prescribes vertical mirroring (PPU
A10 -> CIRAM A10), but this program is agnostic to the
nametable configuration. The rendering only interacts with
the nametable at PPU $2000, making it compatible with all
nametable configurations (mirrored, single-screen, etc.)
without any ROM modification.

### Limitations

#### PAL

The bar graph renderer sends up to 240 bytes to the PPU
during NMI if the auxiliary array is not shown, but only
120 bytes if shown. For NTSC, it is necessary to adjust
the scroll value when the auxiliary array is not visible
to account for rendering overrunning VBLANK by a few
scanlines. The longer blanking period on PAL makes this
unnecessary, and will cause the screen to be slightly
vertically shifted.

Always writing #0 to the scroll and address registers
will fix this (this is a simple patch, but not yet
implemented).

#### CHR-RAM

To ensure consistent cycle timing without much extra logic,
the graph renderer writes dummy values to PPU $0000. If
this area of memory is RAM instead of ROM, and no
write-locking is implemented, The first two tiles in the
pattern table will be corrupted, resulting in some obvious
graphical artifacts.

Fixing this requires a small patch (replace hi byte of the
write location for column value $3c to $24/$28), but this
also makes the program dependent on the mirroring
configuration in the cartridge and loses compatibility with
single-screen mirroring.
