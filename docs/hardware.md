# Hardware: Barco PVS6000

## PCI

| Field | Value |
|---|---|
| Vendor / Device | `3D3D` / `0024` (3Dlabs P9) |
| Subsystem | `11A4` (Barco) / `0040` |
| Revision | `01` |
| BAR0 | 256 KB, control registers (MMIO) |
| BAR1 | 64 MB, framebuffer aperture |
| Bus | 32-bit PCI, no AGP |

## BIOS / flash

File: `bios/Barco_PVS6000_102642-01_VideoBIOS_v3.4_2003-05-30.bin`

| | |
|---|---|
| Size | 65,536 bytes (entire flash) |
| MD5 | `d2643a4dfe13540cd689d7a6a18c7f92` |
| Acquisition | read-only under Linux, using the same method as the miniport: register `BAR0+0x10 := 2`, read 64 KB from `BAR1+0`, restore the register |
| Signature | `55 AA`; PCIR: vendor `3D3D`, device `0024`, image length 64 KB |
| Identification | `BarcoView,LLC` · `PVS6000` · `102642` · `01` · date `05/30/ 3` · Phoenix base (© 1984–1996), 3Dlabs (© 1996–1999) |
| BIOS version | bytes 7/8 = 3.4 (evaluated by the driver) |
| Subsystem in ROM | offset `0x34`: `A4 11 40 00` |

A shadow copy taken from `C000:0000` contains only the x86 VGA part. It does not contain the configuration data in the upper half of the flash, which the driver needs.

### Configuration records (parsed by the miniport at `0x2CB10`)

`DWORD [0xFFFC]` = `0x3FC1`, so the table is at `0xFF04`. `DWORD [table+0x14]` = `0x00180036` is written to register `0x5000` without validation. A record chain starts at `table+0x18`. Each record header is `[length/4][type][3D 3D]`, and the chain ends at `0xFFDC`.

| Type | Length | Content | Use in the driver |
|---|---|---|---|
| 0 | 104 B | Memory controller register list: `0x3020=0x380`, `0x3088=0x1A548C4B`, `0x3090=0x2581086B`, `0x3098=0x28`, `0x30A0=0x00420032`, `0x30A8=3`, `0x30B0=0xFF`, `0x30B8=0x45444554`, `0x30C8=0x8877AAAA`, `0x30D8=3`, `0x30E0=0xFF`, `0x30E8=0x44544445`, `0x30F8=0xAAAA7878` | written during initialisation (`board+0x7C`) |
| 1 | 8 B | `04 01 00 18 C2 01 00 34` | Clock block (`board+0x84`): core base clock `0x104` = 260 MHz, memory clock `0x1C2` = 450 MHz; `0x18`/`0x34` are clock sources |
| 2 | 32 B | ASCII `00-000000-001…` | not evaluated |
| 3 | 16 B | byte 0 = `00` | registers `0x2104 := 0`, `0x8104 := 0` |
| 4 | 12 B | `0E 01 00 18 42 31 00 00 01 00 00 00` | Alternate core clock `0x10E` = 270 MHz. The word at byte 8 (= 1) is the texture pipe count in alternate-clock mode. Bytes 4–7 go to `board+0x284…0x287` and are overwritten with `1,2,0,3` during P9 initialisation. |

The type 0 values match the registers programmed by the Barco BIOS at boot. Values that differ while the card runs under the BIOS: `0x3020=0x381`, `0x5000=0x00F00022`, `0x2104=0x1400`, `0x8104=0x01`.

## Clocks

| | Value | Source | Registry override (Hz) | Driver limit |
|---|---|---|---|---|
| Reference | 14.318 MHz | driver default | `P10.ExtRefClockSpeed` | 100 MHz |
| Core, alternate clock (default) | 270 MHz | flash type 4 | `P10.AltCoreClockSpeed` | 400 MHz |
| Core, base clock | 260 MHz | flash type 1 | `P10.CoreClockSpeed` | 400 MHz |
| Memory | 450 MHz | flash type 1 | `P10.MemoryClockSpeed` | 600 MHz |

`P10.UseAltClock` selects the core clock: if the value is missing or ≠ 0, the alternate clock is used. The PLL is programmed in `HwInitialize` (`0x2F600`). The driver then polls the lock bit up to 100,000 times. Initialisation fails if the PLL does not lock.

## Functional units

The units are configured in `0x2C6B8` through PCI configuration register `0xEC` and MMIO register `0x1A4`.

| Unit | Maximum | Enabled count | Hardware disable |
|---|---|---|---|
| Vertex processors | `((0xEC >> 27) & 3) × 8` (if `0xEC` = 0: `0x90000000` → 16) | min(maximum, `P10.VertexProcessors`), in groups of 8 | register `0xFF8` bits 4/5 |
| Texture pipes | `0xEC >> 29` (if `0xEC` = 0: 4) | `P10.TexturePipes` if set; otherwise the flash type 4 value (1) in alternate-clock mode, or the maximum in base-clock mode | register `0xFF8` bits 0–3, plus `P10.TexturePipeMask` |

Pipes are enabled in the order 1, 2, 0, 3, and disabled pipes are skipped. The mask of pipes that are not enabled is written to register `0x1A4`. The driver reports the units that are actually active in the registry value `PVS` (see [patches.md](patches.md#hardware-and-clock-report-code-caves-at-0x3bdb1-and-0x179c6)).

## Outputs

The card drives a DVI output. The VP560 profile of the driver checks for a DVI transmitter at I²C address `0x70`, which the PVS6000 does not have. The modified driver skips this check (see [patches.md](patches.md)).
