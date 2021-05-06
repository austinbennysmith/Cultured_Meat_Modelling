### Results from running the 2-fluid Couette simulation at different refinement LEVELs (with the #define FILTERED line): as the LEVEL is increased, the steady state solution approaches a corner at the interface, as expected. See images below:
<img width="632" alt="Screen Shot 2021-05-06 at 10 21 40 AM" src="https://user-images.githubusercontent.com/69660053/117315417-ae9e5f80-ae55-11eb-8916-6430dab971c6.png"> </br>
### Zooming in on the interface:
<img width="640" alt="Screen Shot 2021-05-06 at 10 24 18 AM" src="https://user-images.githubusercontent.com/69660053/117315593-d42b6900-ae55-11eb-9015-058d0a25af70.png"> </br>
### And if I remove the #define FILTERED line, I get the following (not much different):
<img width="624" alt="xend_multiLEVEL_noFILTER" src="https://user-images.githubusercontent.com/69660053/117318293-48670c00-ae58-11eb-90ae-dc6335333bd7.png">
<img width="613" alt="xend_multiLEVEL_noFILTER_zoomed" src="https://user-images.githubusercontent.com/69660053/117318299-4ac96600-ae58-11eb-98fb-cd82dd9931d7.png">
