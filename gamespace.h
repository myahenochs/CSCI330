// gamespace.h
// game specific types and functions
// game: Saving Syra

#ifndef _GAMESPACE
#define _GAMESPACE

#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

namespace GameSpace
{

//*****************************************************************************  
// Named constants  

//Input Files
  const string ARSENAL_FILE = "weapons.in";
  const string BOARD_FILE = "grid.in";
  const string DICE_FILE = "dice.in";
  const string ENCOUNTER_FILE = "encounters.in";    
  const string MELEE_WPNS_FILE = "melee.in";
  const string PROMOTION_FILE = "promotion.in";
  const string RANGE_WPNS_FILE = "range.in";
  const string SEARCH_PARTY_FILE = "searchparty.in";
  const string SKILLS_FILE = "skills.in";
  const string VOCRULES_FILE = "vocrules.in";

//Output Files
  const string COMBAT_OUTFILE = "combat.out";
  const string MOVE_OUTFILE = "move.out";
  const string TEST_OUTFILE = "tests.out";

//Board constants
  const int NUMROWS = 10;
  const int NUMCOLS = 10;
  const bool KEYBD = true;

//Output constants
  const string LINE1 = "*************************************************\n";
  const char DEL = '#';

//*****************************************************************************  
// enum for dice  
  
  enum RollType {DEX, CON, INT, CHA, STR, WIS, 
                   GP, HP, INIT, ATT, SVTH, SKCK, DMG, END_ROLLTYPE};
    // DEX - Dexterity
    // CON - Constitution
    // INT - Intelligence
    // CHA - Charisma
    // STR - Strength
    // WIS - wisdom
    // GP - Gold pieces
    // HP - Hit points
    // INIT - Initiative Roll 
    // ATT - Attack Roll
    // SVTH - Saving Throw
    // SKCK - Skill Check
    // DMG - Damages

 const string ROLL_STR[END_ROLLTYPE] = {"DEX", "CON", "INT", "CHA", "STR", "WIS",
                             "GP", "HP","INIT","ATT", "SVTH", "SKCK", "DMG"};
  
  
//*****************************************************************************  
// Enum for SavingThrow

  enum SavingThrowType {FORT=1, REFLEX, WILL, END_SAVINGTHROWTYPE};
  // Datatype for describing the saving throws
  // Fortitude:FORT, Reflex: REFLEX, Will:WILL
  
  const string SAVINGTHROW_STR[END_SAVINGTHROWTYPE] = {"INVALID SAVINGTHROW",
                                        "FORT","REFLEX", "WILL"};
    

//*****************************************************************************  
// Enum for exception handling

  enum ExceptionType {INVALID_MISC, INVALID_NAME, INVALID_RACE, INVALID_VOC, INVALID_WPN, 
                      INVALID_ABILITY, INVALID_SAVINGTHROW, INVALID_SKILL, END_EXCEPTIONTYPE};

  const string EXCEPTION_STR[END_EXCEPTIONTYPE] = {"INVALID MISC",   "INVALID NAME", 
                                                   "INVALID RACE",   "INVALID VOCATION",
                                                   "INVALID WEAPON", "INVALID ABILITY TYPE", 
                                                   "INVALID SAVINGTHROW", "INVALID SKILL"};  

//*****************************************************************************  
// Function creating uppercase string  
  
  string Ucase(string str);
  // Converts str to uppercase
  // pre: str is a string
  // post: returns the uppercase version of str

  string TrimStr(string str);
  // Trims leading and trailing whitespace and removes extra
  //    whitespace in the middle
  // pre: str is a string
  // post: returns the trimmed string

  bool Cmp(string s1, string s2);
  // Compares 2 strings(non-case sensitive) to determine sorted order
  // pre:
  // post: returns true if s1<=s2

  void Sort(vector<string>& vec);
  // Sorts a vector of strings (not case-sensitive sort)
  // pre:
  // post: vector is in sorted order


  
//*****************************************************************************  
// File I/O for dice

  void WriteDel(ostream& stream);
  // Writes the delimiter to the output stream
  // pre: stream is open and in good condition
  // post: delimiter has been written
  
  bool ReadNum(istream& stream, int& num,int min,int max);
  // Reads a number, validates range, if valid reads del and returns true
  // pre: stream is open and in good cond, min and max indicate boundaries for num
  // post: valid: returns num, reads passed delimiter (includes \n), returns true
  //       invalid: stops reading and returns false
   
  bool ReadStr(istream& stream, string& str);    
  // Reads string through del, returns true if string length>0 && stream
  // pre: stream is open and in good cond.
  // post: reads str and delimiter (includes \n).  if string length >0 return true
  //		otherwise returns false
  
  bool ReadDel(istream& stream);
  // Reads Del (includes '\n')
  // pre: stream is open and in good cond.
  // post: delimiter is read and stream status is returned


//*****************************************************************************  
// Functions for Game Play  

  void PrintTest(ostream & out, string test="");
  // Prints the test label
  // pre:  out is open and test is prefix for test
  //       if test is new then testnumber is reset
  // post: test label is printed

  string ConvertInt(int num);
  // converts an int to a string
  // pre : num is integer value
  // post: returns as string of num: num = 5, "5"

  
};


#endif

