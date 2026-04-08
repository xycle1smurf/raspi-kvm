# Architekturentscheidung

## Gewählte PoC-Architektur

```text
Pi 4
 └─ interner USB-Hub
     ├─ CP2102 #1 ─ ADUM1201 #1 ─ RP2350 #1 ─ USB-A-Verlängerung ─ Zielserver 1
     ├─ CP2102 #2 ─ ADUM1201 #2 ─ RP2350 #2 ─ USB-A-Verlängerung ─ Zielserver 2
     ├─ CP2102 #3 ─ ADUM1201 #3 ─ RP2350 #3 ─ USB-A-Verlängerung ─ Zielserver 3
     ├─ CP2102 #4 ─ ADUM1201 #4 ─ RP2350 #4 ─ USB-A-Verlängerung ─ Zielserver 4
     ├─ Tastatur
     └─ Maus
```

## Grund für diese Wahl

- Keine USB-Reconnect-Ereignisse an den Zielsystemen
- Zentrale Steuerung über den Pi 4
- Günstiger und kompakter als mehrere Linux-Einzelknoten
- UART ist für das Protokoll einfacher und robuster als I2C oder SPI
- Galvanische Trennung vermeidet GND-Brücken und Masseschleifen

## Elektrische Zonen

### Pi-Seite

- Raspberry Pi 4
- interner USB-Hub
- CP2102-Module
- Versorgung aus Pi/Hub-Zone

### Zielseite

- RP2350-Endpunkte
- Versorgung aus dem jeweiligen Zielserver-USB
- HID-Ausgabe zum Zielserver

Zwischen beiden Seiten liegt der Isolator.
