# Anforderungen

## Funktional

- Mindestens 4 Zielserver
- Kein USB-Connect/Disconnect beim Umschalten, weil gar nicht umgeschaltet werden soll
- Jeder Zielserver sieht dauerhaft sein eigenes USB-HID-Gerät
- Unterstützung für mindestens Keyboard und perspektivisch Maus
- Text-Paste / String-Injection vom Pi 4 auf einen ausgewählten Zielserver
- Steuerung ohne Netzwerkverbindung zwischen den Zielsystemen

## Nicht-funktional

- Netzwerktrennung / Airgap zwischen Zielsystemen erhalten
- Keine mechanische KVM-Switch-Umschaltung
- Galvanische Trennung zwischen Pi-Seite und serverversorgter HID-Seite
- Breadboard-tauglicher PoC vor mechanischem Endaufbau
- Später mechanisch sauberer Gehäuseaufbau mit interner Verkabelung

## PoC-Hardware-Idee

- Pi 4 im Gehäuse
- interner USB-Hub im Gehäuse
- CP2102-Module direkt auf dem Hub gesteckt
- CP2102 fest mit ADUM1201 verbunden
- ADUM1201 fest mit RP2350 verbunden
- RP2350 nicht direkt in Serverport, sondern über konfektionierte USB-A-Verlängerung zum Zielserver
- Zugentlastung in der Gehäusewand
