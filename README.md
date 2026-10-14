# Barco PVS6000 – patched 3Dlabs Wildcat VP driver (Windows XP / 2000)

The Barco PVS6000 is a PCI graphics board with a 3Dlabs P9 graphics processor, the same chip as on the 3Dlabs Wildcat VP560. Barco did not release a 3D-capable Windows driver for it. This repository contains a patched version of the 3Dlabs Wildcat VP driver 3.01-0852 that runs the board under Windows XP with Direct3D and OpenGL, together with the technical documentation.

All modifications are made to the driver. The flash/BIOS of the board is not modified.

## Supported hardware

| | |
|---|---|
| Board | Barco PVS6000 |
| PCI ID | `PCI\VEN_3D3D&DEV_0024&SUBSYS_004011A4&REV_01` |
| Graphics processor | 3Dlabs P9 (device `0024`), driver profile "Wildcat VP560" (board 4) |
| Memory | 64 MB DDR (BGA), memory clock 450 MHz (from flash) |
| Core clock | 270 MHz alternate clock (default) or 260 MHz base clock (from flash) |
| Bus | 32-bit PCI, no AGP |
| Tested with | Windows XP SP3 x86, Pentium Dual-Core E5700, DirectX 9.0c, DVI output at 1600×1200×32, 60 Hz |

The driver is not tested on a genuine Wildcat VP560. AGP boards use the unmodified install section of the INF and keep the original AGP settings.

## Repository contents

| Path | Content |
|---|---|
| `driver/PVS6000_XP/` | Driver package for Windows XP, `DriverVer 3.01.0852.8` |
| `driver/PVS6000_W2K/` | Driver package for Windows 2000, `DriverVer 3.01.0852.8` (original control panel, no hardware report) |
| `driver/reset_clocks.reg` | Removes all clock overrides (recovery after a clock change) |
| `original/` | Unmodified 3Dlabs installers `wxp3010852.exe`, `w2k3010852.exe` |
| `bios/` | Read-only dump of the PVS6000 flash (64 KB), for reference |
| `docs/hardware.md` | PCI resources, flash layout, clocks, functional units |
| `docs/patches.md` | All modifications with offsets, original and new bytes, checksums |

## Features

- The board is initialised with the Wildcat VP560 profile. The DVI transmitter check of that profile is skipped, because the PVS6000 uses a different output device.
- Direct3D (DDI 9) and the OpenGL ICD work. 3DMark2001 SE and Quake 3 Arena run.
- Hardware binning (3Dlabs "Slipstream") can be switched separately for Direct3D and OpenGL. In the original driver it is tied to the clock selection; here it is independent.
- Core clock, memory clock, number of texture pipes and the binning modes can be set in the 3Dlabs control panel (XP).
- The miniport reports the active functional units (texture pipes, vertex processors, disable bits) and the factory clocks stored in the flash. The control panel displays them and uses the flash clocks as defaults.
- The AGP functions of the miniport and the Direct3D AGP heap are switched off for the PVS6000 only.

Technical details are in [docs/patches.md](docs/patches.md) and [docs/hardware.md](docs/hardware.md).

## Installation (Windows XP)

1. Uninstall any existing 3Dlabs driver in Device Manager and restart.
2. When Windows reports new hardware, choose "Install from a list or specific location" → "Don't search. I will choose the driver to install" → "Have Disk" and select `driver/PVS6000_XP/3DL.inf`.
3. Select "Barco PVS6000 (3Dlabs Wildcat VP560 compatible)".
4. The driver is unsigned (the catalog file of the original package is empty). Confirm the warning with "Continue Anyway" and restart.

Do not let Windows search for the driver automatically, otherwise it may pick up an older copy. The Windows 2000 package is installed the same way from `driver/PVS6000_W2K/3DL.inf`.

## Control panel (Windows XP)

Display Properties → Settings → Advanced → 3Dlabs → page "Advanced" (3Dlabs display settings):

| Control | Registry value (`HKLM\SYSTEM\CurrentControlSet\Services\miranda\Global`) | Takes effect |
|---|---|---|
| Pipeline optimizations: Max. texture / Max. geometry | `P10.UseAltClock` 0 / 1 (base / alternate clock) | after restart |
| Clock speed 100–400 MHz | `P10.CoreClockSpeed` or `P10.AltCoreClockSpeed` (Hz, 0 = flash value) | after restart |
| Memory speed 200–600 MHz | `P10.MemoryClockSpeed` (Hz, 0 = flash value) | after restart |
| Texture pipes 1–4 | `P10.TexturePipes` (in `...\miranda\Adapter00`) | after restart |
| Direct3D binning (Slipstream) | `Direct3DHAL.P9BinMode` 2 / 0, `Direct3DHAL.P9OverlapMode` 1 / 0 | after restart |
| OpenGL binning | `OpenGL.ApplicationControl` bit 0 | next start of the application |
| Information text | `PVS`, `PVSC` (written by the miniport, read-only) | – |

On the PVS6000, "Max. geometry" (default) runs the core at 270 MHz with one texture pipe; "Max. texture" runs it at 260 MHz with all texture pipes. Both binning modes are off after installation.

If the board does not start after a clock change: boot into Safe Mode (F8), import `driver/reset_clocks.reg` and restart.

## Status

| Component | State |
|---|---|
| XP: initialisation, display output, Direct3D, OpenGL | confirmed on the board |
| XP: control panel clock, pipe and binning controls | confirmed on the board |
| XP: OpenGL binning | confirmed on the board |
| XP: hardware and clock report, flash clock defaults in the control panel | not yet tested on the board |
| XP: separate INF install section for the PVS6000 | not yet tested on the board |
| Windows 2000 package | not tested |
| Genuine Wildcat VP560 | not tested |

## Legal

The driver files are software by 3Dlabs Inc. The company no longer exists, but the rights still apply and are held by a legal successor. The original license (`license.txt` in the driver packages) prohibits redistribution and reverse engineering. The files in `driver/` and `original/` are provided solely to preserve and operate existing hardware. The analysis was carried out to achieve interoperability with the PVS6000. The documentation in this repository was not written by 3Dlabs.
