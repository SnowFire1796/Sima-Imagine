#!/usr/bin/env bash
set -euo pipefail
./build/sima train --input dataset/raw/cat --masks dataset/masks/cat --class cat --output learned --size 256
./build/sima generate --class cat --learned learned --output output/cat.png --size 256 --seed 7
