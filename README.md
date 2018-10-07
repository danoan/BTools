**Dependencies** 

libboost1.58-dev

DGtal0.9

opencv-3.3.0

**How to use**

./main -c 1.0 -d 0.25 -l 0.5 -b 3.0 -i 1 -f images/ds1/cow2.jpg

Draw a rect containing the object.

Press Enter.

Paint some pixels inside the rect. Those pixels identify sure foreground pixels.

Press Enter.

Wait for GrabCut output.

Press Enter if output is sufficiently good. Press any other key to redo the selections.

When operation is concluded, a window displaying images before and after correction will appear. The results are also save in output/Interactive/[Image_Name]