#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;
#include <vector>
using std::vector;

#include "item.h"


class Character {
private:
    string description;
    vector < Item > itemsInCharacter;
    bool enemyCheck ;
    int attackStrength;
    int healthPoints;
    Item* equipedItem = NULL;

public:

    Character(string description, bool isEnemy, int inAttackStrength, int inHealthPoints);
    void setEquipedWeapon(Item *inWeapon) ;
    Item* getEquipedWeapon() ;
    void addItem(Item *inItem);
    vector< Item > getItemsInCharacter() ;
    Item* getItemAtPos(int index) ;
    string shortDescription();
    string longDescription();
    bool getEnemyCheck();
    void setEnemyCheck(bool isEnemy) ;
    int getAttackStrength() ;
    void setAttackStrength(int inAttackStrength) ;
    int getHealthPoints() ;
    void setHealthPoints(int inHealthPoints) ;
    void removeItemFromCharacter(int location) ;
    void restoreHealth(int restoreAmount) ;

};

#endif // CHARACTER_H
