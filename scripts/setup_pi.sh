#!/usr/bin/env bash
set -euo pipefail

sudo apt-get update
sudo apt-get install -y python3 python3-pip minicom screen
python3 -m pip install --user -r control/pi4/requirements.txt

echo "Fertig. Als Nächstes channels.example.json anpassen."
