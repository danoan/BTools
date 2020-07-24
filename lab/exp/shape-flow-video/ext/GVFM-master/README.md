GVFM: gnuplot scripts for making videos out of data.

HOW TO USE GVFM
====================================================

If you know how to use gnuplot, you should have no
problem using this script.

You only need to edit two files:

- gvfm_plot.gp
- gvfm_frame.gp

For making the video, you have two options:

1. In a command line write:

	gnuplot gvfm.gp

2. In the interactive gnuplot environment, write:

	load "gvfm.gp"

DEPENDENCIES
====================================================
- Any recent version of Linux or Mac
- gnuplot, Version 4.4 or above
- mencoder