//Myah Enochs
//CSCI 330
//Spring 2020
//Program 4

#include "player4.h"

//Static Value Assignment ======================================================================

const int PlayerClass::DEFAULT_ROW = -1;
const int PlayerClass::DEFAULT_COL = -1;
const int PlayerClass::DISABLED = 0, PlayerClass::DEAD = -10;
const int PlayerClass::MAX_NAME_LEN = 10;
const int PlayerClass::MIN_NAME_LEN = 1;
const char PlayerClass::DEL = '#';

map<string, PlayerClass::AbilityType> PlayerClass::SKILL_MAP;
int PlayerClass::runningID = 0;

//==============================================================================================


//Constructors =================================================================================

PlayerClass::PlayerClass(string newName, const int abilAdj[], bool rollAbil): PID(++runningID), NAME(ValidateName(newName)), weapon(NULL){
    LoadSkills();
    if(rollAbil){
        for(int i = 0; i < END_ABILITYTYPE; i++){
            abilityScores.push_back(Roll(3, 6, static_cast<RollType>(i)));
            abilityScores[i] += abilAdj[i];
            if(abilityScores[i] < 0){
                abilityScores[i] = 0;
            }
        }
    }
    else{
        for(int i = 0; i < END_ABILITYTYPE; i++){
            abilityScores.push_back(abilAdj[i]);
        }
    }
    SetHP();
    SetCell(DEFAULT_ROW, DEFAULT_COL);
}

PlayerClass::PlayerClass(const PlayerClass &p): PID(PID), NAME(p.NAME),weapon(NULL){
    CopyIntoMe(p);
}

PlayerClass::~PlayerClass(){
    Deallocate();
}


//Public Observers =============================================================================

string PlayerClass::Name() const{
    return (NAME + '-' + GameSpace::ConvertInt(PID));
}

int PlayerClass::Ability(AbilityType aType) const{
    aType = ValidateAbility(aType);
    return abilityScores[aType];
}

int PlayerClass::Row() const{
    return cell.row;
}

int PlayerClass::Col() const{
    return cell.col;
}

int PlayerClass::HP() const{
    return hp;
}

int PlayerClass::MaxHP() const{
    return hpMax;
}

bool PlayerClass::IsDead() const{
    return (hp <= DEAD || abilityScores[CON] == 0);
}

bool PlayerClass::IsDying() const{
    return (hp < DISABLED && hp >= DEAD);
}

bool PlayerClass::IsDisabled() const{
    return (hp == DISABLED);
}

bool PlayerClass::IsActive() const{
    return (!IsDead() && !IsDying() && !IsDisabled());
}

int PlayerClass::AbilityMod(AbilityType aType) const{
    aType = ValidateAbility(aType);
    return (floor(abilityScores[aType]/2-5));
}

void PlayerClass::Write(ostream &out) const{
    out << Name() << DEL;
    out << '(' << Row() << ',' << Col() << ')' << DEL;
    out << HP() << DEL;
    out << MaxHP() << DEL;

    out << '[';
    for(int i = 0; i < END_ABILITYTYPE; i++){
        out << abilityScores[i];
        if (i < END_ABILITYTYPE - 1){
            out << DEL;
        }
    }
    out << ']' << DEL;

    out << WeaponNameAndNum() << DEL;

    out << '(';
    OuputSkills(out);
    out << ')';
    out << DEL;

    out << endl;
}


string PlayerClass::WeaponName() const{
    if (HasWeapon()){
        return weapon->NameAndNum();
    }
    else{
        return "";
    }
}

string PlayerClass::WeaponNameAndNum() const{
    if(weapon){
        return weapon->NameAndNum();
    }
    return "";
}

bool PlayerClass::HasWeapon() const{
    return weapon != NULL;
}

bool PlayerClass::IsMeleeWeapon() const{
    return (HasWeapon() && weapon->IsMelee());
}

bool PlayerClass::IsRangeWeapon() const{
    return (HasWeapon() && weapon->IsRange());
}

int PlayerClass::SkillCheck(string skillToCheck) const{
    skillToCheck = Ucase(skillToCheck);
    skillToCheck = TrimStr(skillToCheck);
    int sk = 0, roll = 0;

    if(!ValidSkill(skillToCheck)){
        throw INVALID_SKILL;
    }

    bool present = std::find(skills.begin(), skills.end(), skillToCheck) != skills.end();

    if(present && !IsDead()){
        roll = Dice::Roll(Name(), SKCK, 1, 20);
        sk = AbilityMod(SKILL_MAP[skillToCheck]);
    }

    return sk + roll;
}

vector<string> PlayerClass::Skills() const{
    return skills;
}

vector<int> PlayerClass::Abilities() const{
    vector<int> ab;
    for(int i = 0; i < END_ABILITYTYPE; ++i){
        ab.push_back(abilityScores[i]);
    }
    return ab;
}

int PlayerClass::RollInitiative() const{
    if(IsActive()){
        return Dice::Roll(Name(), INIT, 1, 20) + AbilityMod(DEX);
    }
    else{
        return 0;
    }
}

int PlayerClass::RollDefense() const{
    if(IsActive()){
        return AbilityMod(DEX) + 10;
    }
    else{
        return 0;
    }
}

int PlayerClass::RollDamage() const{
    int roll = 0, mod = 0, dam = 0;
    if(IsActive()){
        if(HasWeapon()){
            roll = weapon->RollWeaponDamage(Name());
            if(IsMeleeWeapon()){
                mod = AbilityMod(STR);
            }
        }
        else{
            mod = AbilityMod(STR);
        }
    }

    dam = roll + mod;
    if(dam < 0){
        dam = 0;
    }

    return dam;
}


bool PlayerClass::operator==(const PlayerClass &p) const{
    return (Ucase(Name()) == Ucase(p.Name()));
}

bool PlayerClass::operator!=(const PlayerClass &p) const{
    return (Ucase(Name()) != Ucase(p.Name()));
}

bool PlayerClass::operator>=(const PlayerClass &p) const{
    return (Ucase(Name()) >= Ucase(p.Name()));
}

bool PlayerClass::operator<=(const PlayerClass &p) const{
    return (Ucase(Name()) <= Ucase(p.Name()));
}

bool PlayerClass::operator>(const PlayerClass &p) const{
    return (Ucase(Name()) > Ucase(p.Name()));
}

bool PlayerClass::operator<(const PlayerClass &p) const{
    return (Ucase(Name()) < Ucase(p.Name()));
}


//Public Transformers ==========================================================================

bool PlayerClass::SetCell(int nRow, int nCol){
    bool boardPos = (nRow > 0 && nRow <= GameSpace::NUMROWS) && (nCol > 0 && nCol <= GameSpace::NUMCOLS);
    bool defPos   = nRow == DEFAULT_ROW && nCol == DEFAULT_COL;
    bool validPos = false;

    if (boardPos || defPos){
        cell.row = nRow;
        cell.col = nCol;
        validPos = true;
    }
    return validPos;
}

int PlayerClass::UpdateHP(int mod){
    if(!IsDead()){
    	hp += mod;
    	if (hp > hpMax){
		    hp = hpMax;
    	}
    }
    return hp;
}

Weapon * PlayerClass::LoseWeapon(){
    Weapon *returnWpn = NULL;
    if(HasWeapon()){
        returnWpn = weapon;
        weapon = NULL;
    }
    return returnWpn;
}

Weapon * PlayerClass::FindWeapon(Weapon *wpn){
    Weapon *returnWpn = NULL;

    if(wpn == NULL){
        throw INVALID_WPN;
    }

    if(IsActive()){
        returnWpn = weapon;
        weapon = wpn;
    }
    else{
        returnWpn = wpn;
    }

    return returnWpn;
}

bool PlayerClass::AddSkill(string skill){
    skill = Ucase(skill);
    bool valid = ValidSkill(skill);
    bool present = find(skills.begin(), skills.end(), skill) != skills.end();
    bool added = false;

    if(valid){
        if(!present && IsActive()){
            skills.push_back(skill);
            Sort(skills);
            added = true;
        }
        else if(present){
            added = true;
        }
    }
    else{
        throw INVALID_SKILL;
    }

    return added;
}

void PlayerClass::Amnesia(){
    skills.clear();
}

PlayerClass & PlayerClass::operator=(const PlayerClass &p){
    if(&p != this){
        Deallocate();
        CopyIntoMe(p);
    }
    return *this;
}


//Private Observers ============================================================================

string PlayerClass::ValidateName(string newName){
    newName = GameSpace::TrimStr(newName);
    if (newName.length() < MIN_NAME_LEN){
        throw INVALID_NAME;
    }
    else if (newName.length() >= MAX_NAME_LEN){
        // newName = GameSpace::TrimStr(newName);
        newName.resize(MAX_NAME_LEN - 1);
    }

    return GameSpace::TrimStr(newName);
}

PlayerClass::AbilityType PlayerClass::ValidateAbility(AbilityType aType){
    if (aType < 0 || aType >= END_ABILITYTYPE)
        INVALID_ABILITY;
    return aType;
}

bool PlayerClass::ValidSkill(string skill){
    return (SKILL_MAP.count(skill) != 0);
}

void PlayerClass::OuputSkills(ostream &out) const{
    int size = skills.size();
    for(int i = 0; i < size; ++i){
        out << skills.at(i);
        if(i < size - 1){
            out << ',';
        }
    }
}


//Protected ====================================================================================

int PlayerClass::Roll(int num, int faces, GameSpace::RollType type) const{
    return Dice::Roll(Name(), type, num, faces);
}

int PlayerClass::Roll(GameSpace::RollType type) const{
    return Dice::Roll(Name(), type, 1, 20);
}

int PlayerClass::UpdateMaxHP(int mod){
    hpMax += mod;
    hp = hpMax;
    return hpMax;
}

void PlayerClass::OverwriteMaxHP(int mod){
    hp = hpMax = mod;
}

//Private Transformers =========================================================================

void PlayerClass::LoadSkills(){
    static bool executed = false;
    if(!executed){
        ifstream skillsFile;
        string sk, ab;
        AbilityType ability;

        skillsFile.open(SKILLS_FILE.c_str());

        getline(skillsFile, sk, '#');
        while(!skillsFile.eof()){
            getline(skillsFile, ab);
            ability = StringToAbilityType(ab);
            SKILL_MAP.insert(make_pair(Ucase(sk), ability));
            getline(skillsFile, sk, '#');
        }

        skillsFile.close();
        executed = true;
    }
}

void PlayerClass::SetHP(){
    hp = hpMax = 1;
}

void PlayerClass::CopyIntoMe(const PlayerClass &p){
    *(const_cast<string*>(&NAME)) = p.NAME;
    *(const_cast<int*>(&PID)) = p.PID;

    if(p.HasWeapon()){
        weapon = new Weapon(*p.weapon);
    }
    
    hp = p.hp;
    hpMax = p.hpMax;
    cell = p.cell;
    skills = p.skills;

    abilityScores = p.abilityScores;
}

void PlayerClass::Deallocate(){
    if(weapon != NULL){
        delete weapon;
        weapon = NULL;
    }
}


//Utility and Conversion Methods ===============================================================

PlayerClass::AbilityType PlayerClass::StringToAbilityType(string str){
    str = Ucase(str);

    if(str == "DEX"){
        return DEX;
    }
    else if(str == "CON"){
        return CON;
    }
    else if(str == "INT"){
        return INT;
    }
    else if(str == "CHA"){
        return CHA;
    }
    else if(str == "STR"){
        return STR;
    }
    else if(str == "WIS"){
        return WIS;
    }
    else{
        throw INVALID_ABILITY;
    }
}

string PlayerClass::AbilityTypeToString(AbilityType type){
    switch(type){
        case DEX: return "DEX";
        case CON: return "CON";
        case INT: return "INT";
        case CHA: return "CHA";
        case WIS: return "WIS";
        default: throw INVALID_ABILITY;
    }
}

//Top-Level Functions ==========================================================================

ostream &operator<<(ostream &out, const PlayerClass *p){
    if(p != NULL && &out != NULL){
        p->Write(out);
    }
    return out;
}