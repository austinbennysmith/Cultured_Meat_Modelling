### Path to cd into sometimes: /home/benny/Documents/Cultured_Meat_Modelling/2D_Wobbling/Wobbling_Ellipse_Phase/wobbly_REFLENGTHCORRECT/ROTATING_FRAME

### To view something with gfsview: gfsview2D file.gfs

### To run a basilisk c script using jview: CFLAGS=-DDISPLAY=-1 make file.tst

### isosurface ("l2", -0.01, color = "vyz", min = -1, max = 1, linear = true, map = cool_warm); or http://basilisk.fr/src/output.h#output_ppm 

### Command to find all files in subdirectory above 100MB (so that those files can be removed before pushing to Github): find . -type f -size +100M

### Command to copy a file into all subdirectories: 
for d in */; do cp water.txt "$d"; done

find -type f -name *log -size +500M -delete