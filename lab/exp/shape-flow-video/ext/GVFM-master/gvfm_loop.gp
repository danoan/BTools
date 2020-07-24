# Ideally, you don't need to change this file.

if(frame<10) set output OUTPUT_PATH."/".video_file."-frame-000".frame.".png";else if(frame<100) set output OUTPUT_PATH."/".video_file."-frame-00".frame.".png";else if(frame<1000) set output OUTPUT_PATH."/".video_file."-frame-0".frame.".png";else if (frame<10000) set output OUTPUT_PATH."/".video_file."-frame-".frame.".png";else pr "number of frames too large!"

load "gvfm_frame.gp"

set output
frame=frame+skip_frame
if (frame<end_frame) reread