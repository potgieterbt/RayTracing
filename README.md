# RayTracing
Following the RayTracing weekend series

Requires CMake and an image viewer that can display a ppm file.

Building:
`cmake -B build && cmake --build ./build`

Running:
`./RayGun > ./image.ppm`

I use `feh` to display the image:
`feh image.ppm`

TODO:
    Add multi-threading
    Change how the render is saves so I can have it render in a window and watch it improve
    Bidirectional and path spaced ray tracing, Metropolis.
    Convert RGB to spectral
    Glossy BRDF model
    Triangle and disk primatives
