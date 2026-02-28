# TODOS for the game

  * [x] make a class? for the global constants
  * [x] organize folder, right its a mess
  * [x] make individual classes for the different compenents
  * [x] !! make sure this compiles on omarchy - just delete the build folder and config cmake again
  * [x] [[animate churro]]
  * [x] make a tree tile, something more aligned with the farm enviroment
  * [ ] IMCOMPLETE make monsters come alive
  * [ ] !! IMPORTANT make entity system for the game
  * [ ] add musical effects to make the game feel more like a game
  * [ ] give health properties and lives? maybe
  * [ ] expand the level, this one is very small
  * [ ] make Selma character
  * [ ] include Selma in the game
  * [ ] start to write a story
  * [ ] make churros assests more professional
  * [ ] make the assets required from the story
  * [ ] make different levels for different parts of the story

## animate churro
  * [x] add loading the sprite
  * [x] add destroy teh sprite
  NOTE: the animation happens in the main loop, which make sense since I need motion
  read the docs in the web
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
    * [ ] load media -> set_tiles
    * [ ] render
    * [ ] move
    * [ ] set_camera
    ...

### Entity Manager
* [x] needs a maximum entity value, we wil start with 1024
* [x] needs an entity array, to keep track of all the entityies in the game
* [x] needs a method to add and to remove entities in the array
* [x] I need to use templates to add a components and such
* [ ] entities will not be modular, they will have all the 
data for all components

