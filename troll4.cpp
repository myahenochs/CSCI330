#include "troll4.h"

const string Troll::RACE_STR = "TROLL";
const PlayerClass::AbilityArray Troll::ABILITY_ADJ = {14, 23, 6, 6, 23, 9};
const int Troll::HIT_DICE[3] = {6, 8, 36};
const int Troll::SAVING_THROW[3] = {11, 4, 3};
const int Troll::BASE_ATTACK_BONUS[2] = {9, 1};
const string Troll::INIT_WEAPON = "CLUB";
const string Troll::INIT_SKILLS[NUM_INITSKILLS] = {"LISTEN", "SPOT"};

Troll::Troll(string newName): Monster(newName, ABILITY_ADJ, Troll::HIT_DICE){
    for(int i = 0; i < NUM_INITSKILLS; i++){
        AddSkill(INIT_SKILLS[i]);
    }
}

string Troll::RaceStr() const{
    return RACE_STR;
}

vector<string> Troll::InitialWeaponList() const{
    vector<string> wpns;
    wpns.push_back(INIT_WEAPON);

    return wpns;
}

int Troll::RollAttack() const{
    return Monster::RollAttack(BASE_ATTACK_BONUS);
}

int Troll::RollSavingThrow(SavingThrowType kind) const{
    return Monster::RollSavingThrow(kind, SAVING_THROW);
}

void Troll::Write(ostream &out) const{
    out << RaceStr() << '#';
    PlayerClass::Write(out);
}

bool Troll::IsMyFriend(const PlayerClass *p) const{
    if(p){
        return typeid(Troll) == typeid(*p);
    }
    else{
        return false;
    }
}