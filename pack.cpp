// pack.cpp

#include "pack.h"

//***********************************************Constr/destr/assignment
PackClass::PackClass():MAX_WT(0){
}

PackClass::PackClass(int wt):MAX_WT(wt) // should validate >0
{

}

PackClass::PackClass(const PackClass & p): MAX_WT(p.MAX_WT){ 
  CopyPack(p);  
}

PackClass::~PackClass( ){
  EmptyPack( );
}


PackClass& PackClass::operator=(const PackClass& p){
  if (this != &p)
  {
    *const_cast<int *>(&MAX_WT) = p.MAX_WT;
    // cout <<packVec.size()<,endl;
    EmptyPack(); 
    CopyPack(p);
  }    
  return *this;
}

//pre : MAX_WT is set
//        packVec is empty
//post:  packVec contains exactly the weapons in p.packVec


void PackClass::CopyPack(const PackClass & p){
  Weapon *w;
  int size = p.Size();
  for (int i = 0; i < size; ++i){

    w = new Weapon(*p.packVec[i]);
    packVec.push_back(w);
  }
}

//***********************************************Transformers

bool PackClass::AddWeapon(Weapon* w){
  int wt = Wt();

  bool canAdd = (w->Wt() <= (MaxWt()-Wt()));
  if(canAdd){
    packVec.push_back(w);
  }

  return canAdd;
}

Weapon * PackClass::RemoveWeapon(string wName){
  bool found;
  Weapon * ret_w = NULL;

  vector<Weapon *>::iterator iter = FindWeapon(wName);
  found = (iter != packVec.end());

  if (found){
    ret_w = *iter;
    packVec.erase(iter);
  }

  return ret_w;
}


void PackClass::EmptyPack( ){
  int len = packVec.size();
  for(int i = 0; i < len; ++i){
    delete packVec[i];
    packVec[i] = NULL;
  }
  packVec.clear();
}  

//***********************************************Observers

bool PackClass::InPack(string wName) const{
  bool found = false;
  vector<Weapon*>::const_iterator iter;

  for(iter = packVec.begin(); iter != packVec.end() && !found; ++iter){
    if(Ucase((*iter)->Name()) == Ucase(wName)){
      found = true;
    }
  }

  return (found); 
}


vector<Weapon *>::iterator PackClass::FindWeapon(string wName){
  bool found = false;
  vector<Weapon *>::iterator iter, ret_iter;

  ret_iter = packVec.end();
  for(iter = packVec.begin(); iter != packVec.end() && !found; ++iter){
    if(Ucase((*iter)->Name()) == Ucase(wName)){
      found = true;
      ret_iter = iter;
    }
  }

  return (ret_iter); 
}

  
int PackClass::Size( ) const{
  return packVec.size();
}


int PackClass::Wt( ) const{
  int wt = 0;

  int len = packVec.size();
  for(int i = 0; i < len; ++i){
    wt += packVec[i]->Wt();
  }

  return wt;
}


int PackClass::MaxWt( ) const{
  return MAX_WT;
}

bool PackClass::IsEmpty( ) const{
  return (packVec.size()==0);
}

bool PackClass::IsFull( ) const{
  return (Wt() == MaxWt());
}

vector<string> PackClass::PackInventory( ) const{
  vector<string> strVec;
  int size = packVec.size();

  for(int i = 0; i < size; i++){
    strVec.push_back(packVec[i]->NameAndNum());
  }
  Sort(strVec);
  return (strVec);
}

void PackClass::Write(ostream & out ) const{
  vector<string> strVec = PackInventory();
  int size = packVec.size();

  for(int i = 0; i < size; i++){
    out << strVec[i];
    if(i < size - 1){
      out << ",";
    }
  }
}

/*
//Methods to add for iteration

Weapon& PackClass::operator[](int i)
{


}

const Weapon& PackClass::operator[](int i) const
{

}
*/

//***************************************

// loads weapons into wNames vector from input weapon files
void LoadFiles( ); 
void LoadFile(istream& fin,vector<string>& vec);
void PrintVector(ostream& fout, vector<string>&vec);

vector<string> wNames;  // stores all the range and melee weapons

void LoadFiles( ){
  ifstream fin;
  fin.open(RANGE_WPNS_FILE.c_str());
  LoadFile(fin, wNames);
  fin.close();
  fin.open(MELEE_WPNS_FILE.c_str());
  LoadFile(fin, wNames);
  fin.close();
  sort(wNames.begin(), wNames.end());
}

void LoadFile(istream& fin,vector<string>& vec){
  bool valid;
  string name;
  valid = ReadStr(fin, name);
  fin.ignore(256,'\n');
  while (fin && valid )
  {
      vec.push_back(Ucase(name));
      valid = ReadStr(fin,name);
      fin.ignore(256,'\n');
  }
}


void PrintVector(ostream& fout, vector<string>&vec){
  int i;
  for (i=0; i<vec.size();i++)
  {
    fout<<vec[i]<<DEL;
  }
  fout<<endl;
}
  

