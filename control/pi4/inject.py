#!/usr/bin/env python3
"""Einfache CLI zum Senden von PoC-Kommandos an einen UART-Kanal."""

from __future__ import annotations

import argparse
import sys
import time

import serial


def main() -> int:
    parser = argparse.ArgumentParser(description="Sendet ein UART-Kommando an einen RP2350-Endpoint")
    parser.add_argument("--port", required=True, help="z.B. /dev/ttyUSB0 oder /dev/serial/by-id/... ")
    parser.add_argument("command", nargs="+", help="z.B. TYPE hello world")
    parser.add_argument("--baud", type=int, default=115200)
    args = parser.parse_args()

    line = " ".join(args.command).strip() + "\n"

    with serial.Serial(args.port, args.baud, timeout=1) as ser:
        ser.reset_input_buffer()
        ser.write(line.encode("utf-8"))
        ser.flush()
        time.sleep(0.05)
        reply = ser.readline().decode("utf-8", errors="replace").strip()

    if reply:
        print(reply)
        return 0

    print("Keine Antwort erhalten", file=sys.stderr)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
