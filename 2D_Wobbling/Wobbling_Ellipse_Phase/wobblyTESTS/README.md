### Here I test what difference it makes if I change things around in the following lines of code of wobbly.c (ORIGINAL VERSION):

event circle_flow (i++) {
  fraction (circle, (0.01*sq(x) + sq(y) - sq(0.3)));
  foreach()
    foreach_dimension()
      u.x[] = (1. - circle[])*u.x[];
  boundary ((scalar *){u});
}

### I test the effect of changing u.x to u.y, or including both, or neither (that bit commented out)

### At some point I will do this test for flow around the cylinder as well.