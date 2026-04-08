#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
FW_DIR="$ROOT_DIR/firmware/rp2350"
BUILD_DIR="$FW_DIR/build"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake ..
cmake --build .
