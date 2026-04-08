#!/usr/bin/env python3
"""Sehr einfacher Mehrkanal-Daemon für den Pi 4.

Liest ein YAML-ähnliches Mapping aus einer JSON-Datei und bietet eine minimale stdin-Konsole.
"""

from __future__ import annotations

import json
import pathlib
import sys
import time
from dataclasses import dataclass

import serial


@dataclass
class Channel:
    name: str
    port: str
    baud: int = 115200


class Router:
    def __init__(self, channels: list[Channel]):
        self.channels = channels
        self.handles: dict[str, serial.Serial] = {}

    def open(self) -> None:
        for channel in self.channels:
            self.handles[channel.name] = serial.Serial(channel.port, channel.baud, timeout=0.5)
            time.sleep(0.05)

    def close(self) -> None:
        for handle in self.handles.values():
            try:
                handle.close()
            except Exception:
                pass

    def send(self, name: str, command: str) -> str:
        handle = self.handles[name]
        handle.reset_input_buffer()
        handle.write((command.strip() + "\n").encode("utf-8"))
        handle.flush()
        return handle.readline().decode("utf-8", errors="replace").strip()


def load_config(path: pathlib.Path) -> list[Channel]:
    data = json.loads(path.read_text(encoding="utf-8"))
    return [Channel(**item) for item in data["channels"]]


def repl(router: Router) -> int:
    print("Router gestartet. Beispiel: server1 TYPE hello")
    while True:
        try:
            line = input("> ").strip()
        except EOFError:
            print()
            return 0
        if not line:
            continue
        if line in {"quit", "exit"}:
            return 0
        parts = line.split()
        if len(parts) < 2:
            print("Format: <channel> <command>")
            continue
        channel_name = parts[0]
        command = " ".join(parts[1:])
        if channel_name not in router.handles:
            print(f"Unbekannter Kanal: {channel_name}")
            continue
        try:
            print(router.send(channel_name, command))
        except Exception as exc:
            print(f"Fehler: {exc}")


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print(f"Usage: {argv[0]} <config.json>", file=sys.stderr)
        return 2
    config = load_config(pathlib.Path(argv[1]))
    router = Router(config)
    router.open()
    try:
        return repl(router)
    finally:
        router.close()


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
