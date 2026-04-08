# Verdrahtung pro Kanal

## Grundtopologie

```text
Pi 4 / USB-Hub
  -> CP2102
  -> ADUM1201 Seite A
  || galvanische Trennung ||
  -> ADUM1201 Seite B
  -> RP2350 UART
  -> USB zum Zielserver
```

## Signale

### CP2102-Seite
- TXD -> ADUM A1 Eingang
- RXD <- ADUM A2 Ausgang
- VCC_A -> ADUM VDD1
- GND_A -> ADUM GND1

### RP2350-Seite
- ADUM B1 Ausgang -> RP2350 RX
- RP2350 TX -> ADUM B2 Eingang
- VCC_B -> RP2350 3V3 / ADUM VDD2
- GND_B -> RP2350 GND / ADUM GND2

## Wichtige Regel

GND_A und GND_B dürfen nicht direkt verbunden werden.

## RP2350 UART-Vorschlag

- `GPIO0` = UART0 TX
- `GPIO1` = UART0 RX

Bei konkreter Board-Revision immer das Pinout des gelieferten RP2350-One gegenprüfen.
