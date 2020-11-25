// wpn.h
// Weapon class

#ifndef _WPNH
#define _WPNH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cctype>
#include <climits>
#include <map>
#include "gamespace.h"
#include "dice.h"

using namespace std;
using namespace GameSpace;

class Weapon
{
  public:
//*******datatypes

    // Types of Weapons and related members    
    enum WpnType {BALLISTIC, BLUDGEONING, ENERGY, PIERCING, SLASHING};
    static const int NUM_DIFF_WPNS = 5;
    static const string WPNTYPE_STR[NUM_DIFF_WPNS]; 
    static WpnType StrToWpnType(string str);    

//*******constructor
    Weapon(string name);
    // Set data for weapon with name
        
//*******getters
    string Name( ) const;
    // Returns the weapon name
    // pre: none
    // post: the weapon name is returned
    
    string NameAndNum( ) const;
    // Returns the weapon name with serial number
    // pre: none
    // post: the weapon name is returned
    
    int Cost( ) const;
    // Returns the weapon cost
    // pre: none
    // post: the weapon cost is returned
    
    int Wt( ) const;
    // Returns the weapon weight
    // pre: none
    // post: the weapon weight is returned

    int Critical( ) const;
    // Returns the weapon critical range
    // pre:  none
    // post: the weapon's critical range is returned

    int RollWeaponDamage(string playerName) const;
    // returns the weapon's rolled damage value 
    //			(needs player's name to roll)
    // pre:  name of player rolling damage
    // post: Weapon's damage is returned
    
    int Size( ) const;
    // returns the weapon size
    // pre:  none.
    // post: the weapon size is returned

    WpnType Style( ) const;
    // returns the weapon style
    // pre:  none.
    // post: the weapon style is returned

    bool IsMelee( ) const;
    // returns true when melee weapon
    // pre:  none.
    // post: returns true if melee, false otherwise

    bool IsRange( ) const;
    // returns true when melee weapon
    // pre:  none.
    // post: returns true if melee, false otherwise

   static bool IsMelee(string name );
    // returns true when melee wpn
    // pre:  none.
    // post: returns true if melee, false otherwise

    static bool IsRange(string name ) ;
    // returns true when range wpn
    // pre:  none.
    // post: returns true if range, false otherwise

    
    
//*******output
    void Write(ostream& stream) const;
    // Writes the weapon data to an output stream
    // order:
    //       name_and_num#cost#weight#critical#ndf#size#style#MELEE or RANGE
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: all member data in the weapon object has been inserted
    //       into output stream.
    

  private:
    struct WeaponRec
    {
       int cost;
       int wt;
       int critical;
       int damRolls;
       int damFaces;
       int size;
       WpnType style;
       bool strength;
    };


    Weapon( );          // no default construction
//    Weapon(const Weapon&w); //no copy construction
//    Weapon& operator=(const Weapon& w); // no assignment
         
    static void Load( );  // loads the data from WPN_FILE
    
    static bool Read(istream& stream,string& name, WeaponRec& data);
    // Reads the weapon object data from an input stream
    // order:
    //       name_and_num#cost#weight#critical#ndf#size#style#
    // pre:  stream must be open.
    // post: data extracted from stream,
    //       if valid - data members have updated value, return true
    //       else data members unchanged, return false

//*******DATA
    string name;                     // name of weapon
    int serialNum;
    static map <string,WeaponRec> wpns; // data about weapons
    static int count;
};

ostream& operator<<(ostream& out, const Weapon& w);
    // Outputs the weapon data to an output stream
    // order:
    //       name#cost#weight#critical#ndf#size#style#MELEE or RANGE
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: all member data in the weapon object has been inserted
    //       into output stream.




#endif


