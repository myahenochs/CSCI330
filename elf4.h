#include "humanoid4.h"

class Elf: public Humanoid {

    public:

        static const string RACE_STR;

        Elf(string newName, VocRules::VocType newVoc = DEFAULT_VOC);

        //Getters
        virtual string RaceStr() const;

        virtual vector<string> InitialWeaponList() const;
        //returns the player's initial weapons as a vector of names.

        void Write(ostream &out) const;
        //#race#Humanoid::Write()

    private:

        static const AbilityArray ABILITY_ADJ;
        static const VocRules::VocType DEFAULT_VOC;
        static const int NUM_INIT_WPN = 1;
        static const string INIT_WPN[VocRules::END_VOCTYPE][NUM_INIT_WPN];

        Elf();

};