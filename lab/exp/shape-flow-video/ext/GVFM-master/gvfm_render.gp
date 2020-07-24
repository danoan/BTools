# Ideally, you don't need to change this file.

system "mencoder -msglevel 'all=-1' mf://".video_file."-frame-*.png -ovc x264 -mf fps=30 -vf scale=".video_width.":".video_height." -o ".video_file.video_file_suffix
pr ""
pr "Removing temporary files..."
#system "rm ".video_file."-frame-*.png"
pr ""
