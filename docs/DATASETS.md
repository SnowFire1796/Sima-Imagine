# Dataset sources

Recommended starter: Oxford-IIIT Pet Dataset: https://www.robots.ox.ac.uk/~vgg/data/pets/

It contains 37 pet breeds (12 cat, 25 dog), roughly 200 images per breed, and provides head bounding boxes and pixel-level trimap segmentations. Published license: CC BY-SA 4.0. Keep attribution and follow ShareAlike terms if redistributing adapted material.

Suggested layout:
```
dataset/raw/cat/cat_001.jpg
dataset/masks/cat/cat_001.png
```
Image and mask basenames must match. In the original trimap, label 2 is background; labels 1 and 3 are treated as foreground by the trainer. Start with cat breeds and a few dozen examples.

The primitive-shape examples are not required in v0.1: geometric classification is computed from contours. Later, curate labelled examples of triangles, circles, ellipses, rectangles, trapezoids, arcs and curves. Do not commit large datasets to this source repository. Retain source dataset licences.
