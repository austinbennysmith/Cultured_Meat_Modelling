L2 norm between computed and theoretical steady state horixontal (x-component) velocity profile decreases as mesh refinement increases:
(the theoretical expectation is a linear increase in horizontal velocity with height)

<img width="620" alt="Screen Shot 2021-04-04 at 11 13 22 PM" src="https://user-images.githubusercontent.com/69660053/113533441-e9ce1a00-959b-11eb-984b-e5de12f70fdd.png">

L2 norm for y component (strangely it increases with mesh refinement....):

<img width="615" alt="Screen Shot 2021-04-05 at 1 27 36 PM" src="https://user-images.githubusercontent.com/69660053/113604268-05283c00-9613-11eb-8579-5c3554bdc994.png">

Per Radu's suggestion, I added best fit lines and included the following three lines before the run() command in couette_Final.c:

NITERMIN = 1; // default 1</br>
NITERMAX = 200; // default 100</br>
TOLERANCE = 1e-6; // default 1e-3

Here's the plot I get without those lines included:

<img width="610" alt="Screen Shot 2021-04-08 at 12 37 00 PM" src="https://user-images.githubusercontent.com/69660053/114064569-c7702100-9867-11eb-8a69-6bbc4cfa5f30.png">

And here's the plot I get with them included:

