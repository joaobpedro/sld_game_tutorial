# TODOS for the game

  * [x] make a class? for the global constants
  * [x] organize folder, right its a mess
  * [x] make individual classes for the different compenents
  * [x] !! make sure this compiles on omarchy - just delete the build folder and config cmake again
  * [x] [animate churro](#animate-churro)
  * [x] make a tree tile, something more aligned with the farm enviroment
  * [x] IMCOMPLETE make monsters come alive
  * [x] !! IMPORTANT make entity system for the game
  * [x] give health properties and lives? maybe
  * [ ] [General Fixes](#general-fixes)
  * [ ] Vector Mechanics - I need to make vector calculation helpers
  * [ ] add musical effects to make the game feel more like a game
  * [ ] expand the level, this one is very small
  * [ ] make Selma character
  * [ ] include Selma in the game
  * [ ] start to write a story
  * [ ] make churros assests more professional
  * [ ] make the assets required from the story
  * [ ] make different levels for different parts of the story

  - NOTE: to animate I need the same type of sprite for everyone, and maybe
  have a custom animate function for the player

## animate churro
  * [x] add loading the sprite
  * [x] add destroy teh sprite
  * [x] the load media loads the sprite sheet in chunks
  * [x] animation is just the rendering of the images at a given rate
  * [x] make the animation respond to the user inputs
    * [x] I need more images to do this
        * [x] one running to the left
        * [x] one running up
        * [x] one running down
        * [x] one stopped
  * [x] need to load the files all at the same time
    * [x] so I will have an array of textures
    * [x] see the documentation on this

## make monters come alive
  * [x] make the monster sprites
  * [x] make the monster character, i.e., rending
  * [x] make the collision assessment
        * [x] the collisions are following the camera, need to make them camera independent
  * [x] give health property so Churro can kill the monsters !!!!!!!!!!!!!!!!!!!!!!!!

## Entity System
* [ ] build an entity manager
* [x] see how to make entities modular

            ENTITY MANAGER
                |
            ENTITY ARRAY - if in array - RENDER
                /\
            ADD   REMOVE

* [ ] re-write all game functions
    * [x] load media -> set_tiles
    * [x] render
    * [x] move
    * [x] set_camera
    * [x] animate
        * [x] all things must have the same sprite structure
        * [ ] we can make the sprite pick based on speed, this will work
            even if the things does not have event handles
        
    * [x] kill monster
        * [ ] now need a proper animation for the kill monster
    ...
* [ ] FIXME: there is a bug in the event handling and the access to the player data is not as I imagined
need to check the pointer/ref/adresses stuff.
    * [x] NOTE FIXED seems fixed for now

### Entity Manager
* [x] needs a maximum entity value, we wil start with 1024
* [x] needs an entity array, to keep track of all the entityies in the game
* [x] needs a method to add and to remove entities in the array
* [x] I need to use templates to add a components and such
* [x] entities will not be modular, they will have all the 
data for all components
* [ ] right now i am not managing entities at all, just populating the 
array with some things and thats it

## General Fixes
* [ ] the monsters are not interacting with the walls properly
* [ ] the velocity of the monsters is not proper, they need to be more
random
* [ ] the monster generation needs to be more random and only in
playable places of the game

