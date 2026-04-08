# PoC-Plan

## Phase 1: Einzelkanal

1. RP2350-Firmware flashen
2. RP2350 direkt an Testrechner als HID prüfen
3. UART ohne Isolator zwischen CP2102 und RP2350 testen
4. Isolator dazwischen setzen
5. Pi-CLI auf `/dev/ttyUSBX` testen
6. End-to-End-Test am Zielserver

## Phase 2: Mehrkanal

1. zweiten Kanal hinzufügen
2. Namenszuordnung der USB-UART-Geräte per udev rules
3. Pi-Daemon für mehrere Ports aktivieren
4. Text auf selektierten Kanal routen

## Phase 3: Mechanik

1. Hub im Gehäuse fixieren
2. CP2102 intern stecken
3. Isolator- und Endpoint-Verkabelung finalisieren
4. Zugentlastung für USB-A-Verlängerungen vorsehen
