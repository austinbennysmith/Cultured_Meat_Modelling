### Line of code to change speed of simulation video: mencoder -speed 0.1 -o output.mp4 -ovc lavc RT.mp4

### Line of code to crop video: ffmpeg -i shearMovie9.mp4 -vf "crop=in_w-115:in_h-525" -c:a copy shearMovie9CROP.mp4

### Line of code to stack videos: ffmpeg -i shearMovie8.mp4 -i shearMovie9.mp4 -filter_complex vstack=inputs=2 combined.mp4

### To play with color saturation: ffmpeg -i Vorticity.mp4 -filter_complex "vibrance=intensity=2:rlum=0.2:blum=0.4" -pix_fmt yuv420p output.mp4