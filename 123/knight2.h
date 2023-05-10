#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
bool isPrime(int);
bool isPythagoras(int);
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType { ANTIDOTE, PHOENIXI, PHOENIXII, PHOENIXIII, PHOENIXIV };
enum EventType { SMALL, BIG, PHOENIX, ITEM, BOSS };
class BaseBag;
class BaseEvent;
class Events;
class BaseItem;
class BaseKnight;
class ArmyKnights;
class BaseItem {
public:
    ItemType itemType;
    BaseItem* nextItem = nullptr;
    BaseItem();
    ~BaseItem();
    virtual bool canUse(BaseKnight* ) = 0;
    virtual void use(BaseKnight* ) = 0;
};
class BaseBag {
public:
    BaseBag();
    ~BaseBag();
    BaseBag(BaseKnight*, int, int);
    BaseItem* lastItem = nullptr;
    int length = 0;
    bool hasItem(ItemType );
    void deleteFirst();
    bool insertFirst(BaseItem* );
    virtual bool isFull() { cout << "hehe"; return true; };
    static void createBag(BaseKnight*,int,int);
    BaseItem* get(ItemType );
    BaseItem* get(BaseItem* );
    BaseItem* checkItemAt(int);
    BaseItem* pushFirstCanUsePhoenixUp(BaseKnight*);
    virtual string toString() const;
    void removeLast3();
    friend class BaseKnight;
};
class LancelotBag :public BaseBag {
public:
    LancelotBag() = default;
    LancelotBag(BaseKnight* , int , int );
    bool isFull();
};
class PaladinBag : public BaseBag {
public:
    PaladinBag() = default;
    PaladinBag(BaseKnight* , int , int );
    bool isFull();
};
class DragonBag :public BaseBag {
public:
    bool isFull();
    DragonBag() = default;
    DragonBag(BaseKnight*, int, int);
};
class NormalBag : public BaseBag {
public:
    NormalBag(BaseKnight* , int , int );
    NormalBag() = default;
    bool isFull();
};
class BaseKnight {
protected:
    bool poisoning = false;
    bool hpDescreaseFlag = false;
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    double knightBaseDamage;
    BaseBag* bag;
    KnightType knightType;
public:
    BaseKnight* nextKnight;   
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
     ~BaseKnight();
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    bool haveAntidote();
    string toString() const;
    bool hpDescrease();
    bool isPoisoning();
    void setPoisoning(bool a);
    int getAntidote();
    void setAntidote(int newAntidote);
    int getHP();
    int getMaxHP();
    int getLevel();
    void setLevel(int newLevel);
    bool isFullGil();
    int exchangeGil(int newgil);
    int knightDamage();
    int getGil();
    void setHP(int newhp);
    KnightType getType();
    BaseBag* getBag();
    friend class ArmyKnights;
    friend class BaseEvent;
    friend class BaseBag;
};
class PaladinKnight :public BaseKnight
{
public:  
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class LancelotKnight :public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class DragonKnight :public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class NormalKnight :public BaseKnight
{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class ArmyKnights {
private:
    BaseKnight* LastKnight = nullptr;
    int length = 0;
    bool hadPaladinShield = false;
    bool hadLancelotSpear = false;
    bool hadGuinevereHair = false;
    bool hadExcaliburSword = false;
public:       
    BaseItem* tempItem = nullptr;
    bool passItemFlag = false;
    bool wonOmegaWeapon = false;
    bool wonHades = false;
    bool winHades = false;
    int tempGil = 0;
    bool passGilFlag = false;
    ArmyKnights (const string & file_armyknights);
    void clearAll();
    void insertFirst(BaseKnight*);
    void deleteFirst();
    bool pushKnightToLast();
    BaseKnight* firstFitKnight();
    void deleteKnight(BaseKnight*);
    ~ArmyKnights();
    bool fight(BaseEvent *& );
    bool adventure (Events * );
    int count() const;
    BaseKnight * lastKnight() const;
    void setPaladinShield();
    void setLancelotSpear();
    void setGuinevereHair();
    void setExcaliburSword();
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void passItem();
    void passGil();
    void callPhoenix(BaseKnight* );
    void printInfo() const;
    void printResult(bool win) const;
};
class Antidote :public BaseItem
{
public:
    Antidote();
    bool canUse(BaseKnight* );
    void use(BaseKnight* );
};
class  PhoenixDownI :public BaseItem {
public:
    PhoenixDownI();
    bool canUse(BaseKnight* );
    void use(BaseKnight* );
};
class  PhoenixDownII :public BaseItem {
public:
    PhoenixDownII();
    bool canUse(BaseKnight* );
    void use(BaseKnight* );
};
class  PhoenixDownIII :public BaseItem {
public:
    PhoenixDownIII();
    bool canUse(BaseKnight* );
    void use(BaseKnight* );
};
class  PhoenixDownIV :public BaseItem {
public:
    PhoenixDownIV();
    bool canUse(BaseKnight* );
    void use(BaseKnight* );
};
class BaseEvent
{
public:
    int id;
    int eventCode;
    EventType eventType;
    int bonusGil;
    int baseDamage;
    int phoenixType;
   ~BaseEvent();
    BaseEvent();
    static BaseEvent* createEvent(int eventCode, int id);
    void small_AffectOn(ArmyKnights* armyKnights);
    void phoenix_AffectOn(ArmyKnights* armyKnights);
    virtual void item_AffectOn(ArmyKnights* armyKnights);
    virtual void big_AffectOn(ArmyKnights* armyKnights);
    void boss_AffectOn(ArmyKnights* armyKnights);
    int getLevelO();
};
class Events {
private:
    int numEvents;
    int* eventCodeList;
public:
    Events(const string& file_events);
    ~Events();
    int count() const;
    int get(int i) const;

};
class MadBear : public BaseEvent
{
public:
    MadBear(int eventCode, int id); 
};
class Bandit : public BaseEvent
{
public:
    Bandit(int eventCode, int id);    
};
class LordLupin : public BaseEvent
{
public:
    LordLupin(int eventCode, int id);
};
class Elf : public BaseEvent
{
public:
    Elf(int eventCode, int id);    
};
class Troll : public BaseEvent
{
public:
    Troll(int eventCode, int id);  
};
class Tornbery : public BaseEvent
{
public:
    Tornbery(int eventCode, int id);
    void big_AffectOn(ArmyKnights* armyKnights);
};
class QueenOfCards : public BaseEvent
{
public:
    QueenOfCards(int eventCode, int id);
    void big_AffectOn(ArmyKnights* armyKnights);
};
class NinaDerings : public BaseEvent
{
public:
    NinaDerings();
    void big_AffectOn(ArmyKnights* armyKnights);
};
class DurianGarden : public BaseEvent
{
public:
    DurianGarden();
    void big_AffectOn(ArmyKnights* armyKnights);
};
class OmegaWeapon : public BaseEvent
{
public:
    OmegaWeapon();
    void big_AffectOn(ArmyKnights* armyKnights);
};
class Hades : public BaseEvent
{
public:
    Hades();
    void big_AffectOn(ArmyKnights* armyKnights);
};
class pickPhoenixII : public BaseEvent
{
public:
    ~pickPhoenixII();
    pickPhoenixII();
};
class pickPhoenixIII : public BaseEvent
{
public:
    ~pickPhoenixIII();
    pickPhoenixIII();
};
class pickPhoenixIV : public BaseEvent
{
public:
    pickPhoenixIV();
};
class PaladinShield : public BaseEvent
{
public:
    PaladinShield();
    void item_AffectOn(ArmyKnights* armyKnights);
};
class LancelotSpear : public BaseEvent
{
public:
    LancelotSpear();
    void item_AffectOn(ArmyKnights* armyKnights);
};
class GuinevereHair : public BaseEvent
{
public:
    GuinevereHair();
    void item_AffectOn(ArmyKnights* armyKnights);
};
class Excalibur : public BaseEvent
{
public:
    Excalibur();
    void item_AffectOn(ArmyKnights* armyKnights);
};
class Ultimecia : public BaseEvent
{
public:
    Ultimecia();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__