#ifndef _HUMANOID4_H
#define _HUMANOID4_H

#include "player4.h"
#include "voc.h"
#include "pack.h"

class Humanoid: public PlayerClass {
    
    public:

        virtual ~Humanoid();

        virtual void Write(ostream &out) const;
        //voc#level#xp#PlayerClass::Write()
        //  (pack)#

        //Getters
        virtual string RaceStr() const = 0;
        VocRules::VocType Voc() const;
        string VocStr() const;
        int Level() const;
        long XP() const;

        vector<string> Pack() const;
        //Returns the contents of the pack as a vector of names.

        virtual vector<string> InitialWeaponList() const = 0;
        //returns the player's initial weapons as a vector of names.

        virtual Weapon* FindWeapon(Weapon *wpn);
        //Narrative: The player picks up a weapon and puts it in their pack, if possible.
        //Pre-Condition: wpn must not be null and pointing to a valid weapon.
        //Post-Condition: 

        Weapon* ChangeWeapon(string wpn);
        //Narrative: Swaps the player's weapon with one that is in the pack.
        //Pre-Condition: A valid string is passed in.
        //Post-Condition: If wpn is in the pack, the player will make it their current weapon
        //  and put the old weapon back, if possible. If the weapon cannot be put back, it is returned.
        //  Otherwise, returns null.

        long UpdateXP(long mod);
        //Narrative: Updates the player's experience points by mod, then promotes the player, if possible.
        //Pre-Condition: A positive long must be passed in.
        //Post-Condition: If mod is positive, mod is added to the player's experience points.
        //  If the player can be promoted, they will be.
        //  Returns the player's experience points.

        int RollAttack() const;
        //1d20 + attack bonus

        virtual int RollSavingThrow(SavingThrowType type) const;
        //Base bonus + ability modifier

        bool IsMyFriend(const PlayerClass *p) const;
        //Checks if the pointer points to a member of the same class, or a derivative.

        Humanoid& operator=(const Humanoid &h);


    protected:

        Humanoid(string newName, VocRules::VocType newVoc, const AbilityArray adj);
        Humanoid(const Humanoid &h);
        void CopyHumanoid(const Humanoid &h);

        int RollHitDice() const;


    private:

        static const int NUM_SK = 3;
        static const string INIT_SK[VocRules::END_VOCTYPE][NUM_SK];
        static const int INIT_SK_NUM[VocRules::END_VOCTYPE];

        VocRules::VocType voc;
        int level;
        long exp;
        PackClass* const PACK;

        Humanoid();

        int AttackBonus() const;
        //If range weapon: base attack bonus + dexterity modifier
        //Else: base attack bonus + strength modifier

        VocRules::VocType InitVoc(VocRules::VocType newVoc) const;
        //Narrative: Validates the passed VocType.
        //Pre-Condition: A VocType, or a cast to a VocType, must be passed.
        //Post-Condition: If the VocType is valid, it is returned. otherwise, throws INVALID_VOC

        void InitSkills();
        //Narrative: Initializes the player's skills
        //Pre-Condition: None
        //Post-Condition: Adds the player's initial skills to their active kills.
    
        void Promote();
        //Narrative: Promotes the player a level and updates their HP.
        //Pre-Condition: None
        //Post-Condition: Increments the player's level, then calculates the hp modifier.
        //  If the player's level is 0, their max HP is overriden.
        //  Else, the modifier is added onto the current max HP.

        void Deallocate();
        //Deallocates all dynamic data.


};

#endif