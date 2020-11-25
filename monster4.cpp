#include "monster4.h"

//PUBLIC =======================================================

void Monster::Write(ostream &out) const{
    PlayerClass::Write(out);
}

Monster::Monster& Monster::operator=(const Monster &m){
    if(&m != this){
        PlayerClass::operator=(m);
    }
    return *this;
}


//PROTECTED ====================================================

Monster::Monster(string name, PlayerClass::AbilityArray abilAdj, const int newDice[3]): PlayerClass(name, abilAdj), HIT_DICE(newDice){
    int newHP = PlayerClass::Roll(HIT_DICE[NUM], HIT_DICE[FACES], GameSpace::HP) + HIT_DICE[MOD];
    OverwriteMaxHP(newHP);
}

int Monster::RollAttack(const int attBonus[]) const{
    if(IsActive()){
        return PlayerClass::Roll(ATT) + AttackBonus(attBonus);
    }
    return 0;
}

int Monster::RollSavingThrow(SavingThrowType type, const int savingThrows[]) const{
    int mod = 0;
    int sThrow = 0;
    int roll = 0; 

    if(IsActive()){
        if(type < FORT || type >= END_SAVINGTHROWTYPE){
            throw INVALID_SAVINGTHROW;
        }

        roll = Roll(SVTH);
        sThrow = savingThrows[type-1];

        switch(type){
            case FORT:   mod = AbilityMod(CON);
                break;
            case REFLEX: mod = AbilityMod(DEX);
                break;
            case WILL:   mod = AbilityMod(WIS);
        }
    }

    sThrow += mod += roll;
    if(sThrow < 0){
        sThrow = 0;
    }

    return sThrow;
}

int Monster::AttackBonus(const int bonus[3]) const{
    int base = 0, mod = 0;

    if(HasWeapon() && IsRangeWeapon()){
        mod = AbilityMod(DEX);
        base = bonus[RANGE];
    }
    else{
        mod = AbilityMod(STR);
        base = bonus[MELEE];
    }

    return base + mod;
}
