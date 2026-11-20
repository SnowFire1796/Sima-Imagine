# Build and run

Requirements: CMake 3.31+, Git, and a C++ compiler with C++26 support (GCC 15+ recommended; support depends on compiler build).

On Xubuntu/Ubuntu:
```bash
sudo apt update
sudo apt install build-essential cmake git
g++ --version
cmake --version
```

Build:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j2
ctest --test-dir build --output-on-failure
```
The first CMake configure downloads the two stb single-header image libraries. Internet is required for this first step. No Python, CUDA, Qt, or GPU is needed.

Run from the repository root:
```bash
mkdir -p dataset/raw/cat
# copy cat images into dataset/raw/cat
./build/sima train --input dataset/raw/cat --class cat --output learned --size 256
./build/sima generate --class cat --learned learned --output output/cat.png --size 256 --seed 7
./build/sima inspect --file learned/cat/definitions/cat-0001.sdf
```

For masks with matching filenames:
```bash
./build/sima train --input dataset/raw/cat --masks dataset/masks/cat --class cat --output learned
```
On older CPUs start with 32-100 images and 128-256 px. Do not start with thousands of large photos.
