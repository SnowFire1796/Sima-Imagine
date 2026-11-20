# Algorithm and scope

v0.1 pipeline: image scan -> grayscale -> foreground mask -> crop/normalize -> boundary sampling -> convex hull -> Ramer-Douglas-Peucker simplification -> coarse geometric classification -> SDF template + monochrome preview -> seeded template selection -> supersampled PNG rendering.

An external foreground mask is strongly preferred. Without one, a border-colour heuristic estimates foreground and works best when the image has a uniform background.

**Scope honesty:** v0.1 learns a whole-object silhouette, not semantic anatomy. It cannot reliably infer that a contour region is an eye, ear, nose, paw, or tail. That requires labelled part masks/landmarks or a separately trained detector. Convex hulls also discard concavities and fine details. The output is a vector-like redraw of a learned silhouette, not a diffusion model or general text-to-image model.

Next milestones: semantic part annotations; multi-primitive fitting; component library and spatial graph; prompt-to-component selection; evaluation suite.
