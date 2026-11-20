# Sima-Imagine

**A CPU-first C++26 experiment for geometric monochrome cartoon reconstruction.**

Sima turns example images into normalized geometric silhouette descriptions (SDF), keeps a local learned-template library, and renders black-and-white PNGs. It needs no GPU, Python, Qt, or neural-network runtime.

## What v0.1 actually does
- Loads PNG, JPEG, BMP, TGA and PPM through the stb single-header libraries.
- Converts images to grayscale and estimates a foreground mask (or uses supplied masks).
- Crops and normalizes the foreground.
- Samples contour points, computes a convex hull, simplifies the contour, and classifies a coarse primitive family.
- Saves a monochrome preview and human-readable SDF file per image.
- Renders a selected learned silhouette as a supersampled grayscale PNG.
- Includes a CLI and a small CTest test suite.

**Important limitation:** v0.1 learns whole-object silhouettes. It does not yet understand semantic parts such as eyes, ears, nose, paws, or tail. That requires labelled part masks/landmarks or a dedicated detector. This is a geometric-learning prototype, not a diffusion model or a general prompt-to-image model.

## Build
Read [docs/INSTALL.md](docs/INSTALL.md). Short version:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j2
ctest --test-dir build --output-on-failure
```

## Train and generate
```bash
mkdir -p dataset/raw/cat
# add cat photos to dataset/raw/cat/
./build/sima train --input dataset/raw/cat --class cat --output learned --size 256
./build/sima generate --class cat --learned learned --output output/cat.png --size 256 --seed 7
```

With foreground masks:
```bash
./build/sima train --input dataset/raw/cat --masks dataset/masks/cat --class cat --output learned
```

Generate the built-in monochrome primitive references (triangle, circle, ellipse, rectangle, trapezoid):
```bash
./build/sima primitives --output dataset/primitives
```

## Learned library
```
learned/cat/
  images/       normalized monochrome previews
  definitions/  one .sdf file per source image
  training_manifest.csv
  knowledge.txt
```
SDF coordinates are normalized to the canvas. See [docs/FORMAT_SDF.md](docs/FORMAT_SDF.md).

## Dataset
Recommended starter: [Oxford-IIIT Pet](https://www.robots.ox.ac.uk/~vgg/data/pets/). It includes cat/dog images and trimap masks. Read [docs/DATASETS.md](docs/DATASETS.md) for licensing and preparation notes.

## Dependencies
CMake fetches [stb](https://github.com/nothings/stb) on first configure. No external image library needs to be installed manually.

## Roadmap
- v0.2 semantic part labels and landmark import.
- v0.3 multi-primitive fitting per object.
- v0.4 spatial relationship learning and reusable component library.
- v0.5 prompt-to-component selection and composition search.
- v1.0 polished end-to-end workflow, evaluation suite and GUI.

Source code license: MIT. Dataset images keep their original licences.
