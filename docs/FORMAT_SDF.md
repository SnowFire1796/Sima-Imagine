# SDF v1

SDF (Sima Definition Format) is a versioned text format. Coordinates and dimensions are normalized relative to the canvas (normally 0..1).

Each shape stores primitive type, component label, x/y/width/height, rotation, flip_x/flip_y, grayscale fill/outline values, outline width, and optional contour points.

Example:
```
SIMA_SDF 1
name "cat"
canvas 256 256
mode monochrome
shapes 1
shape triangle left_ear 0.2 0.1 0.2 0.25 0 0 0 255 0 2 3 0.3 0.1 0.4 0.3 0.2 0.3
```
Grayscale values: 0 = black, 255 = white. The v0.1 trainer writes one silhouette shape per image, but the format supports multiple components for future versions.
