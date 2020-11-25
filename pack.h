// pack.h

#ifndef _PACKH
#define _PACKH

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "wpn.h"
#include "gamespace.h"

using namespace std;

class PackClass
{
  public:
//***********************************************Const/dest/assignment

    PackClass(int weight);
    PackClass(const PackClass& w);
    
    ~ PackClass( );
    PackClass& operator=(const PackClass& p);
//***********************************************Transformers
    
    bool AddWeapon (Weapon* w);
    Weapon * RemoveWeapon(string wName);
    void EmptyPack( );


//***********************************************Observers

    bool InPack(string wName) const;
    int Size( ) const;
    int Wt( ) const;
    int MaxWt( ) const;
    bool IsEmpty( ) const;
    bool IsFull( ) const;
    vector<string> PackInventory( ) const;
    void Write(ostream &) const;

//***********************************************Operators

// Methods to add for iteration      
//    Weapon& operator[](int i);
//    const Weapon& operator[](int i) const;
  
  private:
    PackClass( );
    void CopyPack(const PackClass &p );
    vector<Weapon *>::iterator FindWeapon(string wName);
    // Given a weapon name - find the weapon in the pack vector
    //   and return the iterator to that weapon
    // pre: wName is the name (only) of weapon to search for
    // post: if found, the iterator points to the weapon in the pack vector
    //         if not found the iterator == pack.end()

//***********************************************Data Members
    
    vector<Weapon *> packVec;
    const int MAX_WT;
};  


#endif


