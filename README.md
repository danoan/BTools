## Dependencies 

[libboost1.58-dev](https://www.boost.org/users/history/version_1_58_0.html)

[DGtal0.9](https://dgtal.org/download/)

[opencv-3.3.0](https://opencv.org/releases.html)

## How to use

Build instructions can be found in INSTALL.txt

This source contains five applications. For detailed description,
type: [application] -h

### seed-selector

Tool to select foreground, background and probably foreground masks.
The program outputs three pgm images, one for each mask, in the
output folder. These masks are used as input for the grab-cut 
algorithm.
 
### grab-cut

Runs grab-cut algorithm for image segmentation
 

### boundary-correction

Runs the boundary-correction algorithm. Given a grab-cut object file,
the digital curvature flow is evolved in order to enhance segmentation
quality with respect to curvature.

### shape-flow

Evolve the digital curvature flow along digital shapes.


## summary-flow

Overlay flow images in one single image.

