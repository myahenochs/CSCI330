// dice.h

#ifndef _DICEH
#define _DICEH

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <climits>
#include "gamespace.h"

using namespace std;
using namespace GameSpace;

class Dice
{
  public:
    // RollType is defined in GameSpace namespace

    static int Roll(string forWho, RollType forWhat, 
                    int num_dice, int num_dice_faces);
    // Rolls the dice using passed data
    // pre: 
    //      forWho indicates who the roll is for, 
    //      forWhat indicates what the roll is for
    //      num_dice indicates the number of dice to roll
    //      num_dice_faces indicates the faces on the dice that are rolled
    
    // post: Rolls the dice based on forWho and forWhat...
    //       returns the TOTAL rolled value

    static void HideRolls( );
    // Hides the output from Rolls - less verbose
    // pre:
    // post: Sets the flag so no output generated from Roll functions
    
    static void SeeRolls( ); 
    // See the output from the Rolls - more verbose
    // pre:
    // post: Sets the flag so output is sent to cout stream
    //       every times roll takes place.

    static void WriteRollsToFile( );
    // Writes the Rolls to an output file - used to create the RollData
    
    static void ReadRollsFromFile( ); 
    // Reads the Rolls from an input file - RollData is read from file

 
 private:   
    static bool see;  // Controls output for each roll. set to true originally
    static bool write;// writes to dice file      
    static bool read; // reads from dice file

    Dice( );  // default constructor - cannot use!

    static int Roll (int numRolls,int faces) ;
    // Rolls the dice using passed data
    // pre: numRolls and faces must be positive
    // post: Rolls the dice based on numRolls, faces
    //       returns the rolled value
    
    static void Write(ostream& stream, int n, int f, string who, 
                    RollType what, int tot);
    // Writes the passed to stream who[what]:XdY=tot
    // pre: parameters need values
    // post: Write the passed data to the stream

    static void fWrite(ostream& stream, int n, int f, string who, 
                    RollType what, int tot);
    // Writes the passed to stream who[what]:XdY=tot
    // pre: parameters need values
    // post: Write the passed data to the stream
    
    struct RollRec
    {
       string name;
       RollType what;
       int times;
       int numrolls;
       int faces;
       int rollvalue;
       bool used;
    };

    static vector<Dice::RollRec> rollData;  // vector containing the RollData
    
    static bool Read(istream& stream, RollRec& data);
    // Reads the roll object data from an input stream
    // order:
    //       name#what#times#numrolls#faces#rollvalue
    // pre:  stream must be open.
    // post: data extracted from stream,
    //       if valid - data members have updated value, return true
    //       else data members unchanged, return false

    static int Find(int numRolls, int dieFaces, string forWho, RollType forWhat);
    // searches the RollData for the roll value
    // pre: parameter values need to be valid
    // post: finds the first unused occur of the roll in RollData   

};


#endif


