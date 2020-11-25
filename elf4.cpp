#include "elf4.h"

//Static Data =============================================================================

const string Elf::RACE_STR = "ELF";

const PlayerClass::AbilityArray Elf::ABILITY_ADJ = {2, -2, 0, 0, 0, 0};
const VocRules::VocType Elf::DEFAULT_VOC = VocRules::WIZ;
const int Elf::NUM_INIT_WPN;
const string Elf::INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN] = {
    "",
    "Dagger", 
    "Long Sword", 
    "Sword", 
    "Rapier", 
    "Short Bow"
};

//Constructors and Destructor =============================================================

Elf::Elf(string newName, VocRules::VocType newVoc): Humanoid(newName, newVoc, ABILITY_ADJ){
}

//Public ==================================================================================

string Elf::RaceStr() const{
    return RACE_STR;
}

vector<string> Elf::InitialWeaponList() const{
    vector<string> wpns;

    for(int i = 0; i < NUM_INIT_WPN; i++){
        wpns.push_back(INIT_WPN[Voc()][i]);
    }
    
    return wpns;
}

void Elf::Write(ostream &out) const{
    out << RaceStr() << '#';
    Humanoid::Write(out);
}