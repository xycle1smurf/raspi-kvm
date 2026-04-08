# UART-Protokoll v0

ASCII-basiertes PoC-Protokoll, damit sich der Datenstrom mit `screen`, `minicom` oder `cat` einfach debuggen lässt.

## Transport

- 115200 Baud
- 8N1
- Zeilenende `\n`

## Kommandos

### Ping
`PING`

Antwort:
`PONG`

### Device Info
`INFO`

Antwortbeispiel:
`INFO RP2350-HID v0 channel=1 features=keyboard`

### Text senden
`TYPE hello world`

Antwort:
`OK TYPE 11`

### Einzelnen HID-Key drücken
`KEY 0x04`

Antwort:
`OK KEY 0x04`

### Leeren Zustand senden
`RELEASE`

Antwort:
`OK RELEASE`

## Fehler

- `ERR UNKNOWN`
- `ERR ARG`
- `ERR BUSY`
