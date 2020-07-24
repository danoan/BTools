[![Build Status](https://travis-ci.com/danoan/BTools.svg?branch=master)](https://travis-ci.com/danoan/BTools)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/50a49f3955c245e9977c282d2036e4a2)](https://app.codacy.com/manual/danoan/BTools?utm_source=github.com&utm_medium=referral&utm_content=danoan/BTools&utm_campaign=Badge_Grade_Dashboard)



## BTools
 BTools is a collection of applications originally developped for the 
 publication [1]. In this work, we describe a flow driven by 
 the minimization of the elastica 
 energy. Its main applications are the **shape-flow** 
 and ***interactive-seg** apps. The 
 latter integrates all the necessary steps to execute
 a segmentation using the proposed digital flow.
 

 
 [1] Antunes, D., Lachaud, J.O., Talbot H.: Digital 
 curvature evolution model for image segmentation. In:
 Couprie, M., Cousty, J., Kenmochi, Y., Mustafa, N. (eds.) 
 Discrete Geometry for Computer Imagery. pp 15-26. Springer
 International Publishing, Cham (2019).
 
## Dependencies 

[libboost1.66.0-dev](https://www.boost.org/users/history/version_1_66_0.html)

[opencv-3.3.0](https://opencv.org/releases.html)

[eigen-3.36](http://eigen.tuxfamily.org/index.php?title=Main_Page)

[DGtal0.9](https://dgtal.org/download/)

[jinja2.11](https://github.com/pallets/jinja)

## Build and Install

In order to build BTools, you are going to need cmake.

```
cd [BTOOLS_ROOT_FOLDER]
mkdir build
cd build
cmake ..
make install
```

There are plenty of configuration parameters, but usually, if 
all dependencies are installed in their standard
locations, that should be enough. Otherwise, if errors occur, 
it is likely that a manual configuration should be
done. In this scenario, ccmake is quite handy.

## How to use

Build instructions can be found in INSTALL.txt

This source contains five applications. For detailed description,
type: [application] -?

### shape-flow

Evolve the digital curvature flow for a given digital shape.

<img alt="Triangle flow" src="https://github.com/danoan/BTools/blob/master/doc/images/triangle.gif" height="200" />
<img alt="Flower flow" src="https://github.com/danoan/BTools/blob/master/doc/images/flower.gif" height="200" />


### interactive-seg

Load a image, select foreground/background seeds and then execute the boundary-correction algorithm.

```
./interactive-seg.sh -I images/coala.jpg output/coala
```
<img alt="Coala seeds" src="https://github.com/danoan/BTools/blob/master/doc/images/coala-seeds.png" height="200" /> <img alt="Coala segmentation" src="https://github.com/danoan/BTools/blob/master/doc/images/coala-seg.png" height="200" />



