//Myah Enochs
//CSCI 330
//Spring 2020
//Program 2
//This file contains declarations for a class containing a player.

#ifndef _PLAYER4_H
#define _PLAYER4_H

#include <string>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <typeinfo>

#include "dice.h"
#include "gamespace.h"
#include "wpn.h"

using namespace std;
using namespace GameSpace;

class PlayerClass{

    public:

        //Public Data --------------------------------------------------------------------------

        enum AbilityType{DEX, CON, INT, CHA, STR, WIS, END_ABILITYTYPE};
        enum DiceIndex {NUM, FACES, MOD, END_DICEINDEX};
        enum WeaponType {MELEE, RANGE, END_WEAPONTYPE};
        typedef const int AbilityArray[END_ABILITYTYPE];


        //Destructor ---------------------------------------------------------------------------

        virtual ~PlayerClass();


        //Public Observers ---------------------------------------------------------------------

        friend ostream &operator<<(ostream &out, const PlayerClass *p);
        //race#voc#level#name#(row,col)#maxHP#hp#[a1#a2#a3#a4#a5#a6]#xp<line feed>
	
	//Getters
        string Name() const;
        virtual string RaceStr() const = 0;
        int Ability(AbilityType aType) const;
        int Row() const;
        int Col() const;
        int HP() const;
        int MaxHP() const;
        bool IsDead() const;
        bool IsDying() const;
        bool IsDisabled() const;
        bool IsActive() const;

        //Weapon getters
        string WeaponName() const;
        string WeaponNameAndNum() const;
        bool HasWeapon() const;
        bool IsMeleeWeapon() const;
        bool IsRangeWeapon() const;

        virtual vector<string> InitialWeaponList() const = 0;
        //Narrative: returns a vector containing the player's initial weapon(s).

        int SkillCheck(string skillToCheck) const;
        //Narrative: Returns the skill check value for the passed skill.
        //Pre-Condition: None
        //Post-Condition: Returns the 

        vector<string> Skills() const;
        //Narrative: returns a vector containing the player's known skills.

        vector<int> Abilities() const;
        //Narrative: returns a vector containing the player's ability score values.

        virtual bool IsMyFriend(const PlayerClass *p) const = 0;
        //Checks if the pointer points to a member of the same class, or a derivative.

        //Rolls
        int RollInitiative() const;
        int RollDefense() const;
        int RollDamage() const;
        virtual int RollSavingThrow(SavingThrowType type) const = 0;
        virtual int RollAttack() const = 0;

        virtual void Write(ostream &out) const;
	//name#(row,col)#maxHP#hp#[a1#a2#a3#a4#a5#a6]<line feed>

	//Operators: Based on Name()
        bool operator==(const PlayerClass &p) const;
        bool operator!=(const PlayerClass &p) const;
        bool operator>=(const PlayerClass &p) const;
        bool operator<=(const PlayerClass &p) const;
        bool operator>(const PlayerClass &p) const;
        bool operator<(const PlayerClass &p) const;


        //Public Transformers ------------------------------------------------------------------

        bool SetCell(int newRow, int newCol);
	//Narrative: Sets the player's position on the board to the specified coordinates.
	//Pre-Condition: Two integers must be passed.
	//Post-Condition: If the coordinates are a valid position on the board, or the default position, returns true.
	//	Returns false otherwise.

        int UpdateHP(int mod);
	//Narrative: Updates the player's HP by the amount specified. 
	//Pre-Condition: An integer is passed, which may be negative.
	//Post-Condition: Adds the modifier if positive, subtracts if negative. The player's HP may go to 0 or lower, 
	//	and may not go above the player's maximum HP. Will make no change if the player is dead.
	//	Returns the player's HP after the change.

        Weapon * LoseWeapon();
        //Narrative: The player loses their current weapon.
        //Pre-Condition: None
        //Post-Condition: A pointer to the lost weapon is returned.

        virtual Weapon * FindWeapon (Weapon *wpn);
        //Narrative: The player finds a new weapon to replace their old weapon, if they had one.
        //Pre-Condition: A pointer to a valid Weapon is passed.
        //Post-Condition: The player's weapon is now equal to the new weapon pointer.
        //      If the player did not have a weapon, NULL is returned.
        //      If the player had a weapon, the old weapon pointer is returned.
        //      If wpn is NULL, no changes are made and INVALID_WPN is thrown.

        bool AddSkill(string skill);
        //Narrative: The player learns a new skill.
        //Pre-Condition: A valid string must be passed.
        //Post-Condition: If the skill is valid, the skill is added to the player's skill list.
        //      Otherwise, INVALID_SKILL is thrown.

        void Amnesia();
        //Narrative: Clears the player's skill list.
        //Pre-Condition: None.
        //Post-Condition: The list of player skills is emptied.

        PlayerClass & operator=(const PlayerClass &p);
        //Narrative: Sets an existing player equal to an existing player.
        //Pre-Condition: An existing player is passed in.
        //Post-Condition: Everything inside of the player is set to the values in p, if p is not equal to the player.

        

    protected:

        //Protected Constructors ---------------------------------------------------------------

        PlayerClass(string newName, const AbilityArray adj, const bool rollAbil = false);
        PlayerClass(const PlayerClass &p);

        //Protected Methods --------------------------------------------------------------------

        int AbilityMod(AbilityType aType) const;
        //Narrative: Calculates the player's ability modifier.
        //Pre-Condition: A valid AbilityType must be passed.
        //Post-Condition: Calculates and returns the player's ability modifier based on their stat of aType.

        int Roll(int num, int faces, GameSpace::RollType type) const;
        //Narrative: Rolls the dice for the player.
        //Pre-Condition: Two integers and a valid RollType must be passed.
        //Post-Condition: The roll is done using the player's name, type, num, and faces and returned.

        int Roll(GameSpace::RollType type) const;
        //Narrative: Rolls the dice with a default value for faces and sides.
        //Pre-Condition: A valid RollType must be passed.
        //Post-Condition: The roll is done using the player's name, the type, 1 die, and 20 faces and returned.

        int UpdateMaxHP(int mod);
        //Narrative: Used for updating the HP to be the mod.
        //Pre-Condition: An integer must be sent in.
        //Post-Condition: The player's hp and hpMax are incremented by mod.

        void OverwriteMaxHP(int mod);
        //Narrative: Used for updating the HP to be the mod.
        //Pre-Condition: An integer must be sent in.
        //Post-Condition: The player's hp and hpMax are set to mod.


    private:

        //Static Constants

        static const int DEFAULT_ROW, DEFAULT_COL;
        static const int DISABLED, DEAD;
        static const int MAX_NAME_LEN, MIN_NAME_LEN;
        static const char DEL;

        //Static Variables

        static map<string, AbilityType> SKILL_MAP;
        static int runningID;

        struct CellRec{
            int row, col;
        };

        const int PID;
        const string NAME;
        int hp, hpMax;
        CellRec cell;
        vector<int> abilityScores;
        vector<string> skills;

        Weapon *weapon;

        //Private Constructors

        PlayerClass();


        //Private Observers -------------------------------------------------------------------

        static string ValidateName(string newName);
	//Narrative: Validates that the name is within parameters.
	//Pre-Condition: A valid string is passed.
	//Post-Condition: Returns the parameter unchanged if the length is between the minimum and maximum.
	//	Otherwise, returns the default name.
	
        static AbilityType ValidateAbility(AbilityType aType);
	//Narrative: Validates that the ability is within parameters.
	//Pre-Condition: An AbilityType, or a coersion, is passed.
	//Post-Condition: Returns the parameter unchanged if the parameter is between the start and end of the
	//      enumerated values. Otherwise, returns the default AbilityType.

        static bool ValidSkill(string skill);
        //Narrative: Checks if the passed skill is valid according to SKILL_MAP.
        //Pre-Condition:  A valid string is passed.
        //Post-Condition: Returns true if the skill is valid, false otherwise.

        void OuputSkills(ostream &out) const;
        //Narrative: Outputs the player's skills in a comma-separated list.
        //Pre-Condition: A valid ostream is passed.
        //Post-Condition: Outputs the player's skills and exits.

        //Private Transformers ----------------------------------------------------------------

        static void LoadSkills();
        //Narrative: Loads the skills map from the skills file.
        //Pre-Condition: None.
        //Post-Condition: Skills and their AbilityType from inside of a file defined in GameSpace are loaded into the map.
	
        void SetHP();
	//Narrative: Sets the player's HP and max HP.
	//Post-Condition: The player's max HP is set according to the player's race and vocation. HP is set to max HP.

        void CopyIntoMe(const PlayerClass &p);
        //Narrative: Copies all fields from p to the player.
        //Pre-Condition: An existing PlayerClass must be passed in. If this is called in the assignment operator, 
                //expects dynamic data to be deallocated.
        //Post-Condition: Player's fields will be the same as p's fields.

        void Deallocate();
        //Narrative: Deallocates all dynamic data.
        //Pre-Condition: None.
        //Post-Condition: All pointers will be deleted and set to NULL.
	

        //Utility and Conversion Methods ------------------------------------------------------

        static AbilityType StringToAbilityType(string str);
        ////Returns an AbilityType according to the passed string.

        static string AbilityTypeToString(AbilityType type);
        //Returns a string according to the passed AbilityType.

};

#endif