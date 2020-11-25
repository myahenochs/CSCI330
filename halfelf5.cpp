#include "halfelf5.h"

const string HalfElf::RACE_STR = "HALFELF";

const PlayerClass::AbilityArray HalfElf::ABILITY_ADJ = {0, 0, 1, 2, 0, 1};
const VocRules::VocType HalfElf::DEFAULT_VOC = VocRules::ROG;
const int HalfElf::NUM_INIT_WPN;
const string HalfElf::INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN] = {
    {"",           ""},
    {"Dagger",     "Short Bow"},
    {"Long Sword", ""},
    {"Sword",      ""},
    {"Rapier",     "Short Bow"},
    {"Club",       "Light Crossbow"}
};

const int HalfElf::NUM_VOC_WPN[VocRules::END_VOCTYPE] = {0, 2, 1, 1, 2, 2};

HalfElf::HalfElf(string newName, VocRules::VocType newVoc): Humanoid(newName, newVoc, ABILITY_ADJ){
    AddSkill("Move Silently");
}

//Public ==================================================================================

string HalfElf::RaceStr() const{
    return RACE_STR;
}

vector<string> HalfElf::InitialWeaponList() const{
    vector<string> wpns;
    VocRules::VocType voc = Voc();

    for(int i = 0; i < NUM_VOC_WPN[voc]; i++){
        wpns.push_back(INIT_WPN[voc][i]);
    }
    
    return wpns;
}

int HalfElf::RollSavingThrow(SavingThrowType type) const{
    return floor(Humanoid::RollSavingThrow(type)*1.5);
}

Weapon * HalfElf::FindWeapon(Weapon *wpn){
    Weapon *rtnWpn = wpn;
    if(wpn){
        if(wpn->Wt() <= 10){
            rtnWpn = Humanoid::FindWeapon(wpn);
        }
    }

    return rtnWpn;
}

void HalfElf::Write(ostream &out) const{
    out << RaceStr() << '#';
    Humanoid::Write(out);
}