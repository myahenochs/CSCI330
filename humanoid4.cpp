#include "humanoid4.h"

//Static Data =============================================================================

const int Humanoid::NUM_SK;

const string Humanoid::INIT_SK[VocRules::END_VOCTYPE][Humanoid::NUM_SK] = {
    /*NNE*/ {"",              "",                  ""},
    /*BBN*/ {"CLIMB",         "LISTEN",           "SWIM"},
    /*CLR*/ {"HEAL",          "USE MAGIC DEVICES", ""},
    /*FTR*/ {"INTIMIDATE",    "SWIM",              ""},
    /*ROG*/ {"BLUFF",         "CLIMB",             "HIDE"},
    /*WIZ*/ {"CONCENTRATION", "HIDE",              "USE MAGIC DEVICES"}
};


const int Humanoid::INIT_SK_NUM[VocRules::END_VOCTYPE] = {0, 3, 2, 2, 3, 3};


//Constructors and Destructor =============================================================

Humanoid::Humanoid(std::string newName, VocRules::VocType newVoc, const AbilityArray adj): PlayerClass(newName, adj, true), voc(InitVoc(newVoc)), level(0), exp(0), PACK(new PackClass(25+(AbilityMod(STR)*5))){
    InitSkills();
    Promote();
}

Humanoid::Humanoid(const Humanoid &h): PlayerClass(h), PACK(new PackClass(h.PACK->MaxWt())){
    CopyHumanoid(h);
}

Humanoid::~Humanoid(){
    Deallocate();
}


//Public ==================================================================================

void Humanoid::Write(ostream &out) const{
    out << VocStr() << '#';
    out << Level() << '#';
    out << XP() << '#';
    PlayerClass::Write(out);
    
    out << "\t(";
    PACK->Write(out);
    out << ')' << '#';
    out << endl;
}


void Humanoid::CopyHumanoid(const Humanoid &h){
    *PACK = *h.PACK;

    voc = h.voc;
    level = h.level;
    exp = h.exp;
}

bool Humanoid::IsMyFriend(const PlayerClass *p) const{
    const Humanoid *h = dynamic_cast<const Humanoid *>(p);

    return h != NULL;
}

VocRules::VocType Humanoid::Voc() const{
    return voc;
}

string Humanoid::VocStr() const{
    return VocRules::VocToStr(voc);
}

int Humanoid::Level() const{
    return level;
}

long Humanoid::XP() const{
    return exp;
}

vector<string> Humanoid::Pack() const{
    return PACK->PackInventory();
}

Weapon* Humanoid::FindWeapon(Weapon *wpn){
    Weapon *rtnWpn = wpn;
    if(wpn){
        if(IsActive()){
            rtnWpn = PlayerClass::FindWeapon(wpn);
            if (rtnWpn && PACK->AddWeapon(rtnWpn)){
                rtnWpn = NULL;
            }
        }
    }
    else{
        throw INVALID_WPN;
    }

    return rtnWpn;
}

Weapon* Humanoid::ChangeWeapon(string wpn){
    Weapon *rtnWpn = NULL;

    if(IsActive()){
        if(PACK->InPack(wpn)){
            rtnWpn = PACK->RemoveWeapon(wpn);
            rtnWpn = FindWeapon(rtnWpn);
        }
    }

    return rtnWpn;
}

long Humanoid::UpdateXP(long mod){
    if (mod > 0 && level != VocRules::LEVEL_MAX && !IsDead() && !IsDisabled()){
        exp += mod;
        VocRules *vocptr = VocRules::GetVocRules();
        while (exp >= vocptr->XPforPromotion(level+1) && level < VocRules::LEVEL_MAX){
            Promote();
        }
    }
    return exp;
}

int Humanoid::RollAttack() const{
    VocRules *vocRules = VocRules::GetVocRules();
    int base = 0, mod = 0, roll = 0;

    if(IsActive()){
        roll = Roll(ATT);
        base = vocRules->BaseAttackBonus(voc, level);
        if(HasWeapon() && IsRangeWeapon()){
            mod = AbilityMod(DEX);
        }
        else{
            mod = AbilityMod(STR);
        }
    }

    return base + mod + roll;
}

int Humanoid::RollSavingThrow(SavingThrowType type) const{
    VocRules *vocRules = VocRules::GetVocRules();
    int roll = 0, sThrow = 0, mod = 0;

    if(IsActive()){
        if(type < FORT || type >= END_SAVINGTHROWTYPE){
            throw INVALID_SAVINGTHROW;
        }

        roll = Dice::Roll(Name(), SVTH, 1, 20);
        sThrow = vocRules->BaseSaveBonus(voc, level, type);

        switch(type){
            case FORT:   mod = AbilityMod(CON);
                break;
            case REFLEX: mod = AbilityMod(DEX);
                break;
            case WILL:   mod = AbilityMod(WIS);
        }
    }

    return sThrow + mod + roll;
}

Humanoid& Humanoid::operator=(const Humanoid &h){
    if(this != &h){
        PlayerClass::operator=(h);
        PACK->EmptyPack();
        CopyHumanoid(h);
    }
}


//Protected ===============================================================================

int Humanoid::RollHitDice() const{
    VocRules *vocRules = VocRules::GetVocRules();
    return vocRules->HitDie(voc);
}


//Private =================================================================================

int Humanoid::AttackBonus() const{

}

VocRules::VocType Humanoid::InitVoc(VocRules::VocType newVoc) const{
    if(newVoc > 0 && newVoc < VocRules::END_VOCTYPE){
        return newVoc;
    }
    else{
        throw INVALID_VOC;
    }
}

void Humanoid::InitSkills(){
    for(int i = 0; i < INIT_SK_NUM[voc]; ++i){
        AddSkill(INIT_SK[voc][i]);
    }
}

void Humanoid::Promote(){
    VocRules *vocptr = VocRules::GetVocRules();
    int hitDie = vocptr->HitDie(voc);
    int hp = Roll(1, hitDie, GameSpace::HP) + AbilityMod(CON);

    if(hp <= 0){
        hp = 1;
    }

    if(level == 0){
        OverwriteMaxHP(hp);
    }
    else{
        UpdateMaxHP(hp);
    }
    
    level++;
}

void Humanoid::Deallocate(){
    if(PACK){
        delete PACK;
    }
}