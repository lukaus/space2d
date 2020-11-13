# Space2d 
2d space simulator

i want a 2d gravity sim

uses [SFML](https://www.sfml-dev.org/)

to add:
    - separate display from ticks
    - HUD stuff (targeted planet, current date and time, pause/verbose status, TPS)
        - click planet to see orbital properties 
    - ability to display approx. date/time and change tick from 1t=1/60th of a second up to 1t=1yr
        - This may be difficult to do without breaking the simulation. An idea:
            - have a "significant body" threshold that will update a list for each object of bodies that are exerting a "significant" force on it (as in, more than the threshold). Any object exerting less than the threshold amount of force will be excluded from the simulation between timescale ticks. This value will be updated each timescale tick (and not done when timescale = 1)
    - Multithread tick processing
    - simple collisions (right now, simulation breaks down when objects come close to colliding)
    - complex collisions (objects break into many little objects upon colliding) (this would be hard lol)
    - create objects on the fly, burn fuel produce accelleration etc
    - look for code improvements that will speed up execution

