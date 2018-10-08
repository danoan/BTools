## Dependencies 

libboost1.58-dev

DGtal0.9

opencv-3.3.0

## How to use

This source contains five applications:


**dataset**: Read data seed files and execute the segmentation accordingly with parameters. 
USAGE: DATA_SEED_FOLDER_PATH [-c Curvature Weight] [-d Data Weight] [-l Length Weight] [-b Ball Radius] [-i Max Iterations]


**fromSeed**: Read single data seed file and execute the segmentation accordingly with parameters. 
USAGE: DATA_SEED_FILE_PATH [-c Curvature Weight] [-d Data Weight] [-l Length Weight] [-b Ball Radius] [-i Max Iterations]


**interactive**: Read image file and let user to set seeds mannualy execute the segmentation accordingly with parameters. 
USAGE: IMAGE_FILE_PATH [-c Curvature Weight] [-d Data Weight] [-l Length Weight] [-b Ball Radius] [-i Max Iterations]


**multipleSelector**: Read all images and let user to mannually select seeds. It outputs one dataSeed file for each image.
USAGE: IMAGE_DATASET_PATH [-c Curvature Weight] [-d Data Weight] [-l Length Weight] [-b Ball Radius] [-i Max Iterations]


**illustration**: Create some of the figures present in the paper.


## Seed selection
Draw a rect to select probable foreground pixels and press enter.

Select sure foreground pixels among those inside the rect and press enter.

**interactive**: If happy with selection, press escape. If wish to make a new selection, press enter.

**multipleSelector**: To start a new selection for the same image, press enter. To pass to next image, press escape.

