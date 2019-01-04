## Dependencies 

[libboost1.58-dev](https://www.boost.org/users/history/version_1_58_0.html)

[DGtal0.9](https://dgtal.org/download/)

[opencv-3.3.0](https://opencv.org/releases.html)

## How to use

Build instructions can be found in INSTALL.txt

This source contains five applications. For detailed description,
type: [application] -h

###flow

Evolves the digital curvature flow for a set of predefined digital shapes (ball, flower, 
ellipse, triangle, square, pentagon, heptagon) as shown in DGCI19 paper.

The output files are written in output/flow.
 
Usage: flow [-r Ball Radius] [-i Max Iterations] [-a Application Center 0 Pixel 1 Pointel]
[-c Counting Mode 0 Pixel 1 Pointel] [-s Space Mode 0 Pixel 1 Interpixel] 
[-p FlowProfile single double] "FLOW_NAME"

###interactive

Read image file and let user to manually set seeds.
Execute graph cut segmentation accordingly to seed input and digital 
curvature flow post-processing accordingly with the list of parameters.

Instructions on the seed selection procedure can be found at the end
of this document.

The output files are written in output/interactive
 
Usage: IMAGE_FILE_PATH [-c Curvature Weight] [-d Data Weight] 
[-l Length Weight] [-b Ball Radius] [-i Max Iterations]

###multipleSelector

Read all images in IMAGE_DATASET_PATH and let user 
to manually set seeds for each of them. For each image, one dataSeed file 
is generated.

The output files are written in output/multipleSelector.

Usage: IMAGE_DATASET_PATH 

###fromSeed

Read single data seed file and execute graph cut segmentation 
accordingly. Next, execute digital curvature flow post-processing with 
the list of parameters below.

The output files are written in output/fromSeed.
 
Usage: DATA_SEED_FILE_PATH [-c Curvature Weight] [-d Data Weight] 
[-l Length Weight] [-b Ball Radius] [-i Max Iterations]


###dataset

Read all data seed files in DATA_SEED_FOLDER_PATH and execute 
graph cut segmentation for each of them accordingly. Next, for each data seed,
execute digital curvature flow post-processing several times, varying just one 
of the energy weights data or curvature.

While varying data weight, the passed curvature weight parameter is used. 
The same happen when varying curvature.

The output files are written in output/dataset.
 
Usage: DATA_SEED_FOLDER_PATH [-c Curvature Weight] [-d Data Weight] 
[-l Length Weight] [-b Ball Radius] [-i Max Iterations]





## Seed selection
To select a seed, use the mouse to draw a rectangle. The object to be 
segmented should lie in the interior of such rectangle. If happy with
the selection, press Enter. 

Next, use the mouse to select the seed pixels, namely, those that for
sure are part of the object to be segmented. Clearly, such pixels must 
lie inside the rectangle previously drawn. If happy with the selection, 
press Enter. 


In the **multipleSelector** application, you can create multiple 
seeds for every image. After selecting a seed by the above procedure:

press ENTER to make an additional seed selection;

press ESCAPE to redo the current seed selection;

press ESPACE to pass to the next image.