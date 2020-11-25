#include "orc4.h"

//Static Data =============================================================================

const string Orc::RACE_STR = "ORC";

const PlayerClass::AbilityArray Orc::ABILITY_ADJ = {0, 0, -2, -2, 2, -1};
const VocRules::VocType Orc::DEFAULT_VOC = VocRules::BBN;
const int Orc::NUM_INIT_WPN;
const string Orc::INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN] = {
    "",
    "Dagger", 
    "Crossbow", 
    "Sword", 
    "Short Bow", 
    "Light Crossbow"
};

//Constructors and Destructor =============================================================

Orc::Orc(string newName, VocRules::VocType newVoc): Humanoid(newName, newVoc, ABILITY_ADJ){
}

//Public ==================================================================================

string Orc::RaceStr() const{
    return RACE_STR;
}

vector<string> Orc::InitialWeaponList() const{
    vector<string> wpns;

    for(int i = 0; i < NUM_INIT_WPN; i++){
        wpns.push_back(INIT_WPN[Voc()][i]);
    }
    
    return wpns;
}

void Orc::Write(ostream &out) const{
    out << RaceStr() << '#';
    Humanoid::Write(out);
}