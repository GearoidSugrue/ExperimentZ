#ifndef SETUP_H
#define SETUP_H

#include "room.h"
#include "character.h"


class setUp
{

private:

    Room *currentRoom;

public:
    setUp();
    void createRooms() ;
   // Room *currentRoom;

    string go(string direction) ;


    Room* getCurrentRoom() ;

};

#endif // SETUP_H
