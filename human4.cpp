#include "human4.h"

//Static Data =============================================================================

const string Human::RACE_STR = "HUMAN";

const PlayerClass::AbilityArray Human::ABILITY_ADJ = {0, 0, 0, 0, 0, 0};
const VocRules::VocType Human::DEFAULT_VOC = VocRules::FTR;
const int Human::NUM_INIT_WPN;
const string Human::INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN] = {
    "",
    "Dagger", 
    "Crossbow", 
    "Sword", 
    "Rapier", 
    "Club"
};

//Constructors and Destructor =============================================================

Human::Human(string newName, VocRules::VocType newVoc): Humanoid(newName, newVoc, ABILITY_ADJ){
}

//Public ==================================================================================

string Human::RaceStr() const{
    return RACE_STR;
}

vector<string> Human::InitialWeaponList() const{
    vector<string> wpns;

    for(int i = 0; i < NUM_INIT_WPN; i++){
        wpns.push_back(INIT_WPN[Voc()][i]);
    }
    
    return wpns;
}

void Human::Write(ostream &out) const{
    out << RaceStr() << '#';
    Humanoid::Write(out);
}
