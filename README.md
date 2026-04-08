# usb-hid-kvm

PoC-Repository für eine zentral gesteuerte, galvanisch getrennte HID-Injektionslösung.

Primärarchitektur:

- Raspberry Pi 4 als Zentrale
- interner 7-Port-USB-Hub im Gehäuse
- 4x CP2102 als USB-UART-Bridges am Pi 4
- 4x ADUM1201/MCU1201 als galvanische Trennung pro Kanal
- 4x RP2350 One als USB-HID-Endpunkte zu den Zielservern
- Zielserver werden über USB-A-Verlängerungskabel an die RP2350-Endpunkte angeschlossen

## Ziel

Jeder Zielserver sieht dauerhaft ein dediziertes USB-HID-Gerät. Es findet kein mechanisches USB-Umschalten zwischen den Servern statt. Die Steuerung erfolgt zentral vom Pi 4 über einen galvanisch getrennten UART-Kanal pro Endpoint.

## Repository-Struktur

- `docs/ai/` – Anforderungen, Architekturentscheidungen und Gesprächszusammenfassung
- `docs/hardware/` – Stücklisten, Bestellliste, Verdrahtung, PoC-Plan
- `docs/protocol/` – UART-Protokoll und HID-Mapping
- `control/pi4/` – Python-Daemon und CLI auf dem Pi 4
- `firmware/rp2350/` – Firmware-Skeleton für RP2350 One
- `firmware/attiny85/` – optionale Minimalvariante als Referenz
- `scripts/` – Build- und Setup-Skripte

## PoC-Reihenfolge

1. Einen Kanal auf Breadboard aufbauen.
2. RP2350-Firmware flashen und lokale HID-Funktion am Testrechner prüfen.
3. CP2102 -> ADUM1201 -> RP2350 UART testen.
4. Pi-CLI verwenden und Text an den Endpoint schicken.
5. Erst danach mechanischen Endausbau im Gehäuse planen.

## Sicherheit

Wichtig: CP2102, USB-Hub und Pi 4 liegen auf der Pi-Seite. RP2350 und USB zum Zielserver liegen auf der Zielseite. Die Verbindung zwischen beiden Seiten muss pro Kanal galvanisch getrennt sein.

## Status

Dieses Repository ist ein belastbares PoC-Grundgerüst. Es enthält bewusst noch keine voll ausentwickelte Produktionsfirmware, sondern ein sauberes, erweiterbares Ausgangssystem.
