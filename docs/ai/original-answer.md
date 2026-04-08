# Ursprüngliche Architekturantwort (konsolidiert)

Das Zielsystem ist kein klassischer KVM-Switch, sondern ein verteiltes HID-Emulationssystem mit zentraler Steuerung.

Geeignete Primärarchitektur:

- zentraler Raspberry Pi 4
- ein dedizierter USB-HID-Endpoint pro Zielserver
- keine USB-Umschaltung zwischen Zielservern
- Text-Injection und Tastaturevents werden zentral erzeugt und an genau einen Endpoint gesendet
- HID-Endpunkte werden von den jeweiligen Zielservern versorgt
- UART-Kommunikation zwischen Pi 4 und Endpunkt pro Kanal
- galvanische Trennung auf dem Steuerpfad

Verworfene Varianten:

- normale USB-Switches: verursachen Re-Enumeration
- Bluetooth-Dongles: Pairing/Stack/Funkproblem und schlechter für BIOS/Boot
- ESP8266 als Hauptendpoint: kein nativer USB-Device-Controller
- ATTiny85 als Hauptlösung: nur Minimal-/PoC-geeignet, nicht robust genug als Primärlösung
