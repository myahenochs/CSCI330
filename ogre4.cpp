#include "ogre4.h"

const string Ogre::RACE_STR = "OGRE";
const PlayerClass::AbilityArray Ogre::ABILITY_ADJ = {8, 15, 6, 7, 21, 10};
const int Ogre::HIT_DICE[3] = {4, 8, 8};
const int Ogre::SAVING_THROW[3] = {6, 0, 1};
const int Ogre::BASE_ATTACK_BONUS[2] = {8, 1};
const string Ogre::INIT_WEAPON = "SPEAR";
const string Ogre::INIT_SKILLS[NUM_INITSKILLS] = {"INTIMIDATE", "LISTEN", "SPOT"};

Ogre::Ogre(string newName): Monster(newName, ABILITY_ADJ, Ogre::HIT_DICE){
    for(int i = 0; i < NUM_INITSKILLS; i++){
        AddSkill(INIT_SKILLS[i]);
    }
}

string Ogre::RaceStr() const{
    return RACE_STR;
}

vector<string> Ogre::InitialWeaponList() const{
    vector<string> wpns;
    wpns.push_back(INIT_WEAPON);

    return wpns;
}

int Ogre::RollAttack() const{
    return Monster::RollAttack(BASE_ATTACK_BONUS);
}

int Ogre::RollSavingThrow(SavingThrowType kind) const{
    return Monster::RollSavingThrow(kind, SAVING_THROW);
}

void Ogre::Write(ostream &out) const{
    out << RaceStr() << '#';
    PlayerClass::Write(out);
}

bool Ogre::IsMyFriend(const PlayerClass *p) const{
    if(p){
        return typeid(Ogre) == typeid(*p);
    }
    else{
        return false;
    }
}