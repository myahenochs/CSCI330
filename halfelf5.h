#ifndef _HALF_ELF_5_H
#define _HALF_ELF_5_H

#include "humanoid4.h"

class HalfElf: public Humanoid{

    public:

        static const string RACE_STR;

        HalfElf(string newName, VocRules::VocType newVoc = DEFAULT_VOC);

        //Getters
        virtual string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;
        //returns the player's initial weapons as a vector of names.

        int RollSavingThrow(SavingThrowType type) const;

        virtual Weapon * FindWeapon(Weapon *wpn);

        void Write(ostream &out) const;
        //#race#Humanoid::Write()

    private:

        static const AbilityArray ABILITY_ADJ;
        static const VocRules::VocType DEFAULT_VOC;
        static const int NUM_INIT_WPN = 2;
        static const string INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN];
        static const int NUM_VOC_WPN[VocRules::END_VOCTYPE];

        HalfElf();

};


#endif