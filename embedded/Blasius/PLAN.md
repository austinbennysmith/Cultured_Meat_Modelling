### PLAN:

Instead of converting u to f, just take the u.x and u.y profiles into a python (MATLAB?) script and generate a plot of eta vs u/U, which can then be compared (& normed) to the expected plot. Potentially enhance the Basilisk script to catch every point at some spacing within the Boundary layer, rather than just the profiles.

Also: I will need to do the eta vs u/U plot for ONLY the points in the profiles within the boundary layer. This will probably mean masking arrays in Python so that only u.x values less than 0.99 are included.