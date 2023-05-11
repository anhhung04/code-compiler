
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

class BaseKnight;
class BaseItem;
class Events;

enum ItemType {Antidote = 0, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV};

class BaseBag {
protected:
    class Node{
    public:
        BaseItem* Item = nullptr;
        Node* next = nullptr;
    };

protected:
    BaseKnight* knight;
    Node* head = nullptr;
    int current_item = 0, max = 0;
public:
    BaseBag(BaseKnight *knight, int phoenixdown, int antidote);
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    void addItem(BaseItem *item);
    bool useItem(ItemType itemType);
    void removeItem();
    string toString() const;
    ~BaseBag();
};



class BaseOpponent{
    public:
    int baseDamage;
    int event_id;
    int baseGil;
    int levelIO;

};

class MadBear : public BaseOpponent {
public:
    MadBear(int i);
};

class Bandit : public BaseOpponent{
public:
Bandit(int i);
};

class LordLupin : public BaseOpponent{
public:
LordLupin(int i);
};

class Elf : public BaseOpponent{
public:
Elf(int i);
};

class Troll : public BaseOpponent{
public:
Troll(int i);
};

class Tornbery : public BaseOpponent{
public:
Tornbery(int i);
};

class QueenofCards : public BaseOpponent{
public:
QueenofCards(int i);
};

class NinadeRings : public BaseOpponent{
public:
NinadeRings();
};

class Garden : public BaseOpponent{
public:
Garden();
};

class OmegaWeapon : public BaseOpponent{
public:
OmegaWeapon();
};

class Hades : public BaseOpponent{
public:
Hades();
};






enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    KnightType knightType;
    bool PoisonStatus=false;
    int overgil=0;

public:
    BaseBag * bag;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    BaseKnight(int a);
    ~BaseKnight();
    KnightType getType(){return knightType;}
    int getHp(){return hp;}
    void setHp(int hp);
    int getLevel(){return level;}
    void setLevel(int level);
    int getMaxHp(){return maxhp;}
    bool getPoisonStatus(){return PoisonStatus;}
    void setPoisonStatus(bool PoisonStatus){this->PoisonStatus = PoisonStatus;}
    int getGil(){return gil;}
    void setGil(int gil);
    bool Insert(BaseItem* item);
    int getOvergil();
    void HealthHp();
    double baseDamage();
};

 

class ArmyKnights {
private:
    BaseKnight** knight;
    int numKnight;
    
public:
    static bool PaladinShield;
    static bool LancelotSpear;
    static bool GuinevereHair;
    static bool ExcaliburSword; 
    static bool WinHades;
    static bool WinOmega;   
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    void fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    void InsertItem(BaseItem *item);
    void setGil();
    bool hasPaladinShield() const{ return PaladinShield;}
    bool hasLancelotSpear() const{ return LancelotSpear;}
    bool hasGuinevereHair() const{ return GuinevereHair;}
    bool hasExcaliburSword() const{ return ExcaliburSword;}
    void printInfo() const;
    void printResult(bool win) const;
};





class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType Type () = 0;
};

class Antidote_Item: public BaseItem{
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType Type ();
};
class PhoenixI_Item: public BaseItem{
public:
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType Type ();

};
class PhoenixII_Item: public BaseItem{
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType Type ();    
};
class PhoenixIII_Item: public BaseItem{
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType Type ();   

};
class PhoenixIV_Item: public BaseItem{
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
    ItemType Type ();
};




class Events {
private:
    int* road;
    int numevent;
public:
    Events(string );
    int count() const;
    int get(int) const;
    ~Events();
};


class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure();
    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__