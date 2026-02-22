#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

struct Manager {

    // maximum number of entities in the game
    static const int MAX_ENTITIES = 1024;

    // registry of the entities in the game, if nil, the entity is dead
    // also this is a fixed size array
    int Entities[MAX_ENTITIES];

    // method to update the array
    void update_array(int Entities[], int size);

};

#endif
