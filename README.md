# Barco PVS6000 – angepasster 3Dlabs-Wildcat-VP-Treiber (Windows XP / 2000)

Die Barco PVS6000 ist eine PCI-Grafikkarte mit 3Dlabs-P9-Grafikprozessor (Wildcat-VP560-Klasse). Barco hat für Windows keinen 3D-fähigen Treiber veröffentlicht. Dieses Repository enthält einen angepassten 3Dlabs-Treiber 3.01-0852, mit dem die Karte unter Windows XP mit Direct3D und OpenGL läuft. Dazu gehören die zugehörige Dokumentation und die Build-Skripte.

Alle Anpassungen betreffen ausschließlich den Treiber. Das Flash/BIOS der Karte wird nicht verändert.

## Unterstützte Hardware

| | |
|---|---|
| Karte | Barco PVS6000 |
| PCI-ID | `PCI\VEN_3D3D&DEV_0024&SUBSYS_004011A4&REV_01` |
| Grafikprozessor | 3Dlabs P9 (Device `0024`), Treiberprofil „Wildcat VP560“ (Board 4) |
| Speicher | 64 MB DDR (BGA), Speichertakt laut Flash 450 MHz |
| Chiptakt | 270 MHz (Alt-Takt, Standard) bzw. 260 MHz (Basistakt), Werte aus dem Flash |
| Bus | PCI (kein AGP) |
| Getestet | Windows XP SP3 x86, Pentium Dual-Core E5700, DirectX 9.0c; Ausgabe DVI, 1600×1200×32 @ 60 Hz |

## Inhalt

| Pfad | Inhalt |
|---|---|
| `driver/PVS6000_XP/` | Installierbares Treiberpaket Windows XP, `DriverVer 3.01.0852.8` |
| `driver/PVS6000_W2K/` | Installierbares Treiberpaket Windows 2000, `DriverVer 3.01.0852.8` (ohne Panel-Erweiterung und ohne Hardware-Meldung) |
| `original/` | Unveränderte 3Dlabs-Installer `wxp3010852.exe`, `w2k3010852.exe` |
| `build/` | `build.py` erzeugt die Pakete aus dem Original und prüft das Ergebnis per MD5 |
| `tools/` | Entpacker für InstallShield-5-CABs, 3DMark2001-Projektdecoder, Flash-Dump (Linux), Diagnose (Windows), Disassembly-Hilfe |
| `registry/` | `.reg`/`.bat` zum Setzen und Zurücksetzen einzelner Treiberwerte |
| `docs/` | Technische Dokumentation |

## Funktionsumfang

- Die Karte wird als Wildcat VP560 initialisiert. Die DVI-Sender-Prüfung des VP560-Profils ist übergangen, weil die PVS6000 einen anderen Ausgangsbaustein hat.
- Direct3D (DDI 9) und OpenGL-ICD funktionieren. 3DMark2001 SE läuft vollständig durch, Quake 3 Arena ebenso.
- Hardware-Binning (3Dlabs „Slipstream“) lässt sich getrennt für Direct3D und OpenGL schalten. Es hängt nicht mehr an der Taktwahl.
- Chiptakt, Speichertakt, Zahl der Textur-Pipes und die Binning-Modi sind im 3Dlabs-Control-Panel einstellbar.
- Der Miniport meldet die tatsächlich aktive Einheiten-Konfiguration (Textur-Pipes, Vertex-Prozessoren, Sperrbits). Das Panel zeigt sie an.

Details: [docs/patches.md](docs/patches.md), [docs/control-panel.md](docs/control-panel.md), [docs/binning-und-einheiten.md](docs/binning-und-einheiten.md).

## Installation (Kurzfassung)

1. Vorhandenen Treiber im Geräte-Manager deinstallieren, `registry/Neuinstallation_Registry_bereinigen.reg` einspielen, neu starten.
2. Im Assistenten „Treiber selbst wählen“ → „Datenträger“ → `driver/PVS6000_XP/3DL.inf` → „Barco PVS6000 (3Dlabs Wildcat VP560 compatible)“.
3. Den Hinweis auf die fehlende Signatur mit „Installation fortsetzen“ bestätigen und neu starten.

Ausführlich: [docs/installation.md](docs/installation.md).

## Pakete selbst erzeugen

```
python tools/isc_extract.py original/wxp3010852/data1.hdr original/wxp3010852/data1.cab orig_wxp
python build/build.py --os xp --src orig_wxp --out PVS6000_XP
```
Die Installer-EXE ist ein selbstentpackendes Archiv. `data1.hdr`/`data1.cab` lassen sich z. B. mit 7-Zip daraus entnehmen. Voraussetzungen: Python 3, `pefile`, `keystone-engine` (`build/requirements.txt`). Das Skript prüft die MD5 der Eingabe und des Ergebnisses gegen die Referenzwerte der Pakete in `driver/`.

## Status

| Komponente | Zustand |
|---|---|
| XP: Initialisierung, Bild, D3D, OpenGL | auf der Karte bestätigt |
| XP: Panel-Regler (Takt, Pipes, D3D-/OpenGL-Binning) | auf der Karte bestätigt |
| XP: OpenGL-Binning | auf der Karte bestätigt, erhöht die Bildrate in Quake 3 |
| XP: Hardware-Meldung im Miniport, Anzeige im Panel | ungetestet |
| W2K-Paket | ungetestet |

Messwerte und offene Punkte: [docs/binning-und-einheiten.md](docs/binning-und-einheiten.md), [docs/offene-punkte.md](docs/offene-punkte.md).

## Rechtliches

Die Treiberdateien sind Software der 3Dlabs Inc. Das Unternehmen existiert nicht mehr. Die Rechte bestehen dennoch fort und liegen bei einem Rechtsnachfolger. Die Original-Lizenz (`license.txt` im Paket) untersagt Weitergabe und Reverse Engineering. Die Dateien in `driver/` und `original/` werden ausschließlich zur Erhaltung und zum Betrieb vorhandener Hardware bereitgestellt. Die Analyse diente der Herstellung der Interoperabilität mit der PVS6000. Skripte und Dokumentation in diesem Repository stammen nicht von 3Dlabs.
