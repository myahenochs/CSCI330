#ifndef _TROLL4_H
#define _TROLL4_H

#include "monster4.h"

class Troll: public Monster {

    public:

        static const string RACE_STR;

        Troll(string newName);

        virtual string RaceStr() const;
        //Narrative: Returns the player's race as a string.

        virtual vector<string> InitialWeaponList() const;
        //Narrative: Returns the player's initial weapon list as a vector of strings.
        //Pre-Condition: None.
        //Post-Condition: A vector of strings is returned.

        virtual int RollAttack() const;
        //Narrative: Rolls the player's attack.
        //Pre-Condition: None.
        //Post-Condition: The attack roll is calculated and returned.

        virtual int RollSavingThrow(SavingThrowType kind) const;
        //Narrative: Rolls the player's saving throw.
        //Pre-Condition: None.
        //Post-Condition: The saving throw is calculated and returned.

        virtual void Write(ostream &out) const;
        //race#name#(row,col)#maxHP#hp#[a1#a2#a3#a4#a5#a6]<line feed>

        bool IsMyFriend(const PlayerClass *p) const;
        //Checks if the pointer points to a member of the same class, or a derivative.


    private:

        static const PlayerClass::AbilityArray ABILITY_ADJ;
        static const int HIT_DICE[3];
        static const int SAVING_THROW[3];
        static const int BASE_ATTACK_BONUS[2];
        static const string INIT_WEAPON;
        static const int NUM_INITSKILLS = 2;
        static const string INIT_SKILLS[NUM_INITSKILLS];
        
        Troll();
};

#endif