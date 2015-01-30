#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "character.h"

using namespace std;
//using std::vector;


class Room
{
private:

    string description;
    map<string, Room*> exits;
    string exitString();
    vector <Item> itemsInRoom;
    vector <Character> charactersInRoom;
    //vector <Item> interactiveObjectsInRoom;


public:

    bool isEnemysInRoom() ;
    Room(string description);
    void setExits(Room *north, Room *east, Room *south, Room *west, Room *up, Room *down);
    string shortDescription();
    string longDescription();
    Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    void addCharacter(Character *inCharacter) ;
    void removeCharacter(int index) ;
    Item* getItemAtPos(int index) ;
    Character* getCharacterAtPos(int index) ;
    vector<Item> getItemsInRoom() ;
    vector<Character> getCharactersInRoom() ;
};

#endif // ROOM_H
