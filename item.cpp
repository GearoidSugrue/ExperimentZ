#include "item.h"

Item::Item (string inDescription, int inWeightGrams, bool isInteractive, bool isEdible, bool isWeapon, int inHP_RestoreVal, int inAttackDamVal) {
    description = inDescription;
    setWeight(inWeightGrams);
    //setInteractive(isInteractive);
    setEdibleCheck(isEdible);
    setWeaponCheck(isWeapon);
    setHP_RestoreVal(inHP_RestoreVal);
    setAttackDamVal(inAttackDamVal);
}

Item::Item(string inDescription) {
    description = inDescription;
}

string Item::getShortDescription()
{
    return description;
}

void Item::setWeight(int inWeightGrams)
{
       weightGrams = inWeightGrams;
}

int Item::getWeight() {
    return weightGrams ;
}

void Item::setInteractive(bool Interactive)
{
   isInteractive = Interactive;
}

bool Item::getInteractive()
{
    return isInteractive;
}

void Item::setWeaponCheck(bool isWeapon)
{
    weaponCheck = isWeapon;

}

bool Item::getWeaponCheck() {
    return weaponCheck;
}

void Item::setEdibleCheck(bool isEdible)
{
    edibleCheck = isEdible ;
}

bool Item::getEdibleCheck()
{
    return edibleCheck ;
}

void Item::setHP_RestoreVal(int inHP_RestoreVal) {
    hP_RestoreVal = inHP_RestoreVal ;
}

int Item::getHP_RestoreVal() {
    return hP_RestoreVal ;
}

void Item::setAttackDamVal(int inAttackDamVal) {
    attackDamVal = inAttackDamVal ;
}

int Item::getAttackDamVal() {
    return attackDamVal ;
}
