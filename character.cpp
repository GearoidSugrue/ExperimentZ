#include "character.h"

Character::Character(string description, bool isEnemy, int inAttackStrength, int inHealthPoints) {
    this->description = description;
    setEnemyCheck(isEnemy) ;
    setAttackStrength(inAttackStrength) ;
    setHealthPoints(inHealthPoints) ;

}

void Character::setEquipedWeapon(Item *inWeapon) {
        equipedItem = inWeapon ;

}

Item* Character::getEquipedWeapon() {
    return equipedItem ;
}

void Character::addItem(Item *inItem) {
    itemsInCharacter.push_back(*inItem);
}

vector<Item> Character::getItemsInCharacter() {
    return itemsInCharacter ;
}

Item* Character::getItemAtPos(int index) {
    Item  *item =  &itemsInCharacter[index] ;
    return item ;
}

void Character::removeItemFromCharacter(int location) {

    if (itemsInCharacter.size() > 0 && location >= 0) {
        itemsInCharacter.erase(itemsInCharacter.begin()+ location);
    }

}

bool Character::getEnemyCheck() {

    return enemyCheck ;
}

void Character::setEnemyCheck(bool isEnemy) {

    enemyCheck = isEnemy ;
}

int Character::getAttackStrength() {
    return attackStrength ;
}

void Character::setAttackStrength(int inAttackStrength) {
    attackStrength = inAttackStrength ;
}

int Character::getHealthPoints() {
    return healthPoints ;
}
void Character::setHealthPoints(int inHealthPoints) {
    healthPoints = inHealthPoints ;
}

void Character::restoreHealth(int restoreAmount) {
    int currentHealth = getHealthPoints() ;

    if((currentHealth + restoreAmount) > 100)
       setHealthPoints(100) ;
    else
       setHealthPoints(currentHealth + restoreAmount);
}

string Character::shortDescription() {
    return description ;
}

