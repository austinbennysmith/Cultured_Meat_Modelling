### Change speed of video: mencoder -speed 0.1 -o output.mp4 -ovc lavc RT.mp4

### Crop video: ffmpeg -i shearMovie9.mp4 -vf "crop=in_w-115:in_h-525" -c:a copy shearMovie9CROP.mp4

### Stack videos: ffmpeg -i shearMovie8.mp4 -i shearMovie9.mp4 -filter_complex vstack=inputs=2 combined.mp4

### To play with color saturation: ffmpeg -i Vorticity.mp4 -filter_complex "vibrance=intensity=2:rlum=0.2:blum=0.4" -pix_fmt yuv420p output.mp4

### Rescaling a movie: mencoder input.mpg -ovc lavc -lavcopts vcodec=mpeg4:mbd=2:trell -vf scale=640:480 -o output.avi

### To get info about a video: ffprobe -v quiet -print_format json -show_format -show_streams ~/Movies/big_buck_bunny_720p_5mb.mp4

### Handline matplotlib image/video sizes in pixels: https://stackoverflow.com/questions/13714454/specifying-and-saving-a-figure-with-exact-size-in-pixels