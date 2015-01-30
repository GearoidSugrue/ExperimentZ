#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//using std::vector;

class Item {
private:
    string description;
    string longDescription;
    int weightGrams;
    float value;
    bool weaponCheck;
    bool edibleCheck ;
    int hP_RestoreVal ;
    int attackDamVal ;
    bool isInteractive;


public:
    Item (string description, int inWeight, bool isInteractive, bool inEdible, bool isWeapon, int inHP_RestoreVal, int inAttackDamVal);
    Item (string description);

    string getShortDescription();
    string getLongDescription();
    int getWeight();
    void setWeight(int inWeightGrams);
    bool getInteractive();
    void setInteractive(bool Interactive);
    bool getWeaponCheck();
    void setWeaponCheck(bool isWeapon);
    bool getEdibleCheck();
    void setEdibleCheck(bool isEdible) ;
    int getHP_RestoreVal();
    void setHP_RestoreVal(int inHP_RestoreVal);
    int getAttackDamVal();
    void setAttackDamVal(int inAttackDamVal);


};

#endif /*ITEM_H_*/
