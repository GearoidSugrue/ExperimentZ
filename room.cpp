#include "room.h"


Room::Room(string description) {
    this->description = description;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west, Room *up, Room *down) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
    if (up != NULL)
        exits["up"] = up;
    if (down != NULL)
        exits["down"] = down;
}

string Room::shortDescription() {
    return description;
}

string Room::longDescription() {
    return "\nRoom: " + description + ".\n";
}

string Room::exitString() {
    string returnString = "\nexits =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(*inItem);
}

vector<Item> Room::getItemsInRoom() {

    return itemsInRoom ;

}

Item* Room::getItemAtPos(int index) {
    Item  *item =  &itemsInRoom[index] ;
    return item ;
}

void Room::addCharacter(Character *inCharacter) {
    charactersInRoom.push_back(*inCharacter);
}

void Room::removeCharacter(int index) {

    if (charactersInRoom.size() > 0 && index >= 0) {
        charactersInRoom.erase(charactersInRoom.begin()+ index);
    }
}

vector<Character> Room::getCharactersInRoom() {

    return charactersInRoom ;

}

bool Room::isEnemysInRoom() {
    bool isEnemyPresent = false ;

    for(int i = 0; i < charactersInRoom.size(); i++) {
        Character *tempChara = &charactersInRoom[i] ;
        if(tempChara->getEnemyCheck() == 0 ) {
            isEnemyPresent = true ;
        }
    }
    return isEnemyPresent ;
}

void Room::removeItemFromRoom(int location)
{
    if (itemsInRoom.size() > 0 && location >= 0) {

        itemsInRoom.erase(itemsInRoom.begin()+ location);

    }
}

Character* Room::getCharacterAtPos(int index) {
    Character *character = &charactersInRoom[index] ;
    return character ;
}
