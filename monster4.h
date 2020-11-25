#ifndef _MONSTER4_H
#define _MONSTER4_H

#include "player4.h"


class Monster: public PlayerClass {

    public:

        virtual void Write(ostream &out) const;
        //name#(row,col)#maxHP#hp#[a1#a2#a3#a4#a5#a6]<line feed>

        Monster& operator=(const Monster &m);

        virtual string RaceStr() const = 0;
        virtual vector<string> InitialWeaponList() const = 0;

        virtual int RollAttack() const = 0;
        //Narrative: Rolls the player's attack based on their skill values, weapon, and bonuses.
        //Pre-Condition: An array of two integers is passed.
        //Post-Condition: The attack roll is calculated and returned.

        virtual int RollSavingThrow(SavingThrowType type) const = 0;
        //Narrative: Rolls the player's saving throw.
        //Pre-Condition: The saving throw type and an array of three integers is passed.
        //Post-Condition: The saving throw is calculated and returned.

    protected:

        Monster(string name, PlayerClass::AbilityArray abilAdj, const int newDice[3]);

    private:

        const int *const HIT_DICE;

        Monster();

        int AttackBonus(const int bonus[3]) const;
        //Narrative: Calculates the player's attack bonus.
        //Pre-Condition: The player's attack bonus is passed through an array of three integers.
        //Post-Condition: The attack bonus is calculated and returned.
};

#endif