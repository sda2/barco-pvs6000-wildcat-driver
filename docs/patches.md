# Modifications to the original 3.01-0852 driver

The base is the 3Dlabs package 3.01-0852 dated 2006-02-16 (`wxp3010852.exe`, `w2k3010852.exe`). Three kinds of files are modified: the miniport `3dlmp.sys`, the control panel `3dlcp.dll` (XP only) and the INF files. All other files are byte-identical to the original.

Addresses: VA = virtual address at the image base (`3dlmp.sys` 0x10000, `3dlcp.dll` 0x410000). File offsets refer to the respective original file.

## Checksums

| File | Original (MD5) | Modified (MD5) |
|---|---|---|
| XP `x86/Win2K/3dlmp.sys` | `f0500b46470ec174398c0b2bc9ed7be0` | `461f2a0d6cf9ec8615b1c395adcaa33a` |
| XP `x86/Common/3dlcp.dll` | `be89b6552641953b3e5e98ee922af402` | `4eda3948c8bf46924ee3c07e1d2f39e3` |
| XP `3DL.inf` | `b9fc841d649052b8671b09ca917cc442` | `d3884efcd586134b297a315baa2430ae` |
| W2K `x86/Win2K/3dlmp.sys` | `5edbeba5873a88210abf063dbba6007c` | `b2c3c3047eb03a15e853e962eec4b6fb` |
| W2K `3DL.inf` | `b9fc841d649052b8671b09ca917cc442` | `d3884efcd586134b297a315baa2430ae` |

The PE checksum of `3dlmp.sys` is recalculated (XP `0x34D76`, W2K `0x3BD2E`). `3dlcp.dll` has checksum 0, which is not verified for user-mode DLLs.

## Miniport `3dlmp.sys`

| XP offset | W2K offset | XP VA | Original → modified | Effect |
|---|---|---|---|---|
| `0x89F8` | `0x8AF0` | `0x189F8` | `3D3D0000 24000000 02` → `A4110000 40000000 04` | PCI table entry 10: subsystem `3D3D:0024`/board 2 becomes `11A4:0040`/board 4 |
| `0x2067D` | – | `0x3067D` | `EB 07` → `EB 09` | DVI check for board 4 skipped, flag `0x80` always set |
| – | `0x2113E` | – | `75 1C` → `90 90` | same in the W2K build |
| `0x1F4B1` | `0x1F904` | `0x2F4AE` | `and ecx,0x4000` → `and ecx,0` | Alternate clock no longer sets flag `0x4000` |
| `0x1C8FF` | – | `0x2C8FF` | `5F 5E 5D B0 01` → `E9 AD F4 00 00` | Jump into code cave 1 at the end of the unit configuration |
| `0x2BDB1` | – | `0x3BDB1` | 79 × `00` → code | Code cave 1: hardware and clock report, part 1 (see below) |
| `0x79C6` | – | `0x179C6` | 56 × `00` → code | Code cave 2: hardware and clock report, part 2 |
| `0x258` | – | header | `0xFA31` → `0xFA80` | VirtualSize of section `PAGE`, so that cave 1 is mapped |
| `0x1E0` | – | header | `0x76C6` → `0x7700` | VirtualSize of section `.text`, so that cave 2 is mapped |

### PCI table (`0x18928`, 15 entries of 20 bytes `{VEN, DEV, SVID, SSID, board ID}`)

The miniport looks up the vendor, device and subsystem from PCI configuration space in this table. If no entry matches, `HwFindAdapter` fails and the device reports code 10. Entry 10 (MiniMiranda ROMless, a development board) is rewritten for the PVS6000. Board 4 selects the profile "3Dlabs Wildcat VP560" in the board table (`.rdata`, 14 entries of `0x30` bytes).

### DVI check (`0x301E0` / `0x30650`, XP)

For board 4, initialisation reads register `0x0B` of a DVI transmitter via I²C (address `0x70`) and requires the value 2. The PVS6000 has a different output device, so the check fails and `HwInitialize` aborts. The patch jumps directly to the branch that sets flag `0x80` (DVI present).

### Alternate-clock flag (`0x2F39E`, clock calculation mode 3 = core)

The flash contains two core clocks (see [hardware.md](hardware.md)). If `P10.UseAltClock` is missing or ≠ 0, the driver selects the alternate clock (270 MHz). In the original driver this also sets miniport flag `0x4000`. That flag is passed to `3dldd.dll` as display flag `0x1000` (`0x36896`). There it disables Direct3D binning, overlap mode and the allocation of the bin/overlap buffers; in the OpenGL ICD it disables binning. With the patch the flag is never set. Clock selection is unchanged.

### Hardware and clock report (code caves at `0x3BDB1` and `0x179C6`)

Function `0x2C6B8` configures the active texture pipes and vertex processors through PCI configuration register `0xEC` and register `0x1A4`. At its end, the caves write two REG_DWORD values to `HKLM\SYSTEM\CurrentControlSet\Services\miranda\Global` via the miniport routine `0x16910` (`RtlWriteRegistryValue`).

`PVS`, the active units:

| Bits | Content | Source |
|---|---|---|
| 0–7 | Register `0xFF8` (disable bits) | stack `[esp+0x18]`; if `P10.TexturePipeMask` is set: `0xFF8 \| ~mask` |
| 8–15 | Active vertex processors | `[board+0x27C]` |
| 16–23 | Active texture pipes | `[board+0x280]` |
| 24–31 | Top byte of PCI configuration register `0xEC` | read back after the driver has written it |

`PVSC`, the clocks from the flash of the board (clock block `[board+0x84]`, built from flash records type 1 and 4 by `0x2CC24`/`0x2CCF9`):

| Bits | Content | Source |
|---|---|---|
| 0–8 | Base core clock, MHz | block word `+4` |
| 9–17 | Alternate core clock, MHz (equal to the base clock if the flash has no type 4 record) | block word `+8` |
| 18–27 | Memory clock, MHz | block word `+0xC` |
| 28–31 | Texture pipes of the alternate mode (0 = all) | block word `+0xA` |

`PVSC` is 0 if the board has no clock block; the driver then uses 200 MHz core and 400 MHz memory clock.

Cave 1 (79 bytes, the free end of section `PAGE`) computes both values and builds the value name `L"PVS"` on the stack. Cave 2 (56 of 58 free bytes at the end of `.text`) writes `PVS`, appends `C` to the name and writes `PVSC`. The code is position-independent. A new section was not an option: with a header size of `0x300` there is no room for another section table entry.

## Control panel `3dlcp.dll` (XP)

The "Advanced" page (dialog 310) has additional controls. Their function and registry values are described in [control-panel.md](control-panel.md). Implementation details:

| Location | Change |
|---|---|
| `0x41ED70` (constructor) | 11 × `ShowWindow(…, SW_HIDE)` → `SW_SHOW`: clock/memory sliders, edit fields, labels, heading, separators, warning |
| `0x414919`, `0x4149EB`, `0x4149F2` | Memory slider and edit field limit 800 → 600 MHz |
| `0x41F09A`, `0x41F0BA`, `0x41F2E0` | Jumps into section `.pvs`: load, save and reset of the clock controls. The factory clocks and the default number of texture pipes come from `PVSC`/`PVS`. Without `PVSC` the panel assumes 260/270/450 MHz and 1 pipe for the alternate mode. If the base and alternate clocks are equal, the panel uses `P10.CoreClockSpeed` in both pipeline positions, as the miniport does |
| `0x424C50` (end of `.text`, 386 bytes) | Earlier version of the clock code with fixed PVS6000 values, no longer referenced |
| vtable `0x42554C`, slots 1, 2, 3, 4, 7 | Point to wrapper functions in the new section `.pvs`. Each wrapper calls the original method and then handles texture pipes, binning and the information text |
| New section `.pvs` (VA `0x5F0000`, 44 KB, RWX) | Code, strings, variables, extended dialog templates 310 (10 languages), string block 63 |
| Resources | Data entries of dialog 310 and string block 63 point into `.pvs` |

All added code is position-independent. The base address is obtained with `call`/`pop`, and the vtable slots that were redirected are relocated by the loader.

## INF `3DL.inf`

| Section | Change |
|---|---|
| `[Version]` | `DriverVer=02/16/2006,3.01.0852.8` (XP and W2K); same in `3DLdl.inf` |
| `ExcludeFromSelect` | `%DEV_P9A%&%SSI_PVS6000_PCI%` added |
| Models | `%BARCO_PVS6000% = pvs6000, %DEV_P9A%&%SSI_PVS6000_PCI%` |
| `[pvs6000]`, `.CoInstallers`, `.Services`, `.SoftwareSettings`, `.OpenGLSoftwareSettings`, `.GeneralConfigData` | Same files, services and registry sections as `miranda`, plus `pvs6000_SoftwareDeviceSettings` and `pvs6000_SoftwareGlobalSettings` |
| `[pvs6000_SoftwareDeviceSettings]` (HKR) | `GlintDMA.UseAGP=0`, `GlintDMA.SBADisable=1`, `GlintDMA.FWDisable=1`, `GlintDMA.AGPWriteDisable=1` |
| `[pvs6000_SoftwareGlobalSettings]` (`MIA_GLOBAL`) | `Direct3DHAL.DisableAGPHeap=1` (original 0) and the same four `GlintDMA.*` values |
| `[miranda.SoftwareSettings]` | Additional `DelReg = miranda_PVS6000_DelReg`: removes the four `GlintDMA.*` values from `MIA_GLOBAL`, so that an AGP board installed after a PVS6000 runs with the original AGP settings |
| `MIA_GLOBAL` (all boards) | `Direct3DHAL.P9BinMode=0`, `Direct3DHAL.P9OverlapMode=0` |
| `[Strings]` | `SSI_PVS6000_PCI = "SUBSYS_004011A4"`, `BARCO_PVS6000 = "Barco PVS6000 (3Dlabs Wildcat VP560 compatible)"` |

AGP boards such as the Wildcat VP560 use the original install section `miranda` and therefore the original AGP settings. `MIA_GLOBAL` is shared by all 3Dlabs boards in a system; with a PVS6000 and an AGP board in the same computer, the board installed last determines the `GlintDMA.*` values there.

The catalog `3DL-IA32.CAT` is already 0 bytes in the original package, so the driver is unsigned.
