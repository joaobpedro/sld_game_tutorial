#ifndef ENTITY_H_
#define ENTITY_H_

// this will be out fat struct to hold all items
// this will be all types of things, plyers, monters, trees, etc
//

typedef int thing_Idx;

struct Entity{

    // here I can hold all my things propeties
    // like position and heatlh
    //




    // later i need to have properies that are here
    // just to manage my fixed array of things

    thing_Idx ParentIdx;
    thing_Idx FirstChild;
    thing_Idx NextSibling;
    thing_Idx PrevSibling;

};


#endif
