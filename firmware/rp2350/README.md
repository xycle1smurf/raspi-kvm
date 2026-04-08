# RP2350 Firmware

## Ziel

- USB Keyboard HID zum Zielserver
- UART-Empfang galvanisch getrennt vom Pi 4
- ASCII-Kommandos parsen und in HID-Events umsetzen

## Status

Dieses Verzeichnis enthält ein PoC-Skeleton. Für einen echten Build werden Raspberry-Pi-Pico-SDK und TinyUSB benötigt.

## UART-Annahmen

- 115200 Baud, 8N1
- UART0
- Standard-Pins laut `main.c`; bei Bedarf auf das konkrete Board anpassen
