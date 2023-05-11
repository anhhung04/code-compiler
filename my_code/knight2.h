#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

#define MAX_GIL 999
#define MAX_LEVEL 10
#define MAX_HP 999
#define MAX_INT 1e6

class BaseOpponent;
class Events;
class BaseItem;

bool is_prime(int n);
bool is_pythagoras(int n);

enum ItemType
{
    PHOENIXDOWN_I = 0,
    PHOENIXDOWN_II,
    PHOENIXDOWN_III,
    PHOENIXDOWN_IV,
    ANTIDOTE
};

class BaseBag
{
protected:
    int size = 0;
    int max_size = 1000;
    BaseItem *first_item=nullptr;

public:
    virtual ~BaseBag() = 0;
    virtual bool insertFirst(BaseItem *item) = 0;
    BaseItem *get(ItemType itemType);
    void remove_first_item();
    BaseItem* get_first_item();
    virtual string toString() const;
};

class PaladinBag : public BaseBag
{
public:
    PaladinBag();
    ~PaladinBag();
    bool insertFirst(BaseItem* item) override;
};
class LancelotBag : public BaseBag
{
public:
    LancelotBag();
    ~LancelotBag();
    bool insertFirst(BaseItem* item) override;
};
class DragonBag : public BaseBag
{
public:
    DragonBag();
    ~DragonBag();
    bool insertFirst(BaseItem* item) override;
};
class NormalBag : public BaseBag
{
public:
    NormalBag();
    ~NormalBag();
    bool insertFirst(BaseItem* item) override;
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id=0;
    int hp=0;
    int maxhp=0;
    int level=0;
    int gil=0;
    int antidote=0;
    bool poisoned = false;
    BaseBag *bag=nullptr;
    BaseKnight* next_knight=nullptr;
    KnightType knightType;
public:
    BaseKnight(int _id, int _maxhp, int _level, int _gil);
    ~BaseKnight();
    int get_hp() const;
    int get_maxhp() const;
    int get_level() const;
    void increase_level(int _level);
    void increase_hp(int delta_hp);
    int get_gil() const;
    void set_gil(int _gil);
    void increase_gil(int _gil);
    void set_hp(int _hp);
    int get_antidote() const;
    void set_antidote(int _antidote);
    void set_next_knight(BaseKnight* knight);
    BaseBag *get_bag();
    void heal();
    void grab_item(ItemType item);
    BaseKnight* get_next_knight();
    KnightType get_knightType() const;
    static BaseKnight *create(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdownI);
    string toString() const;
};

class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdown);
};

class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdown);
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdown);
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int _id, int _maxhp, int _level, int _gil, int _antidote, int _phoenixdown);
};
class ArmyKnights
{
private:
    BaseKnight *last_knight=nullptr;
    int size=0;
    bool paladin_shield{false};
    bool lancelot_spear{false};
    bool guinevere_hair{false};
    bool excalibur_sword{false};
public:
    explicit ArmyKnights(const string &file_armyknights);
    ~ArmyKnights();
    int count() const;
    void remove_last_knight();
    void remove_knight(BaseKnight* knight);
    BaseKnight* lastKnight() const;
    BaseKnight* retrieve_fight_knight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
};

class BaseItem
{
protected:
    ItemType itemType;
    BaseItem *next=nullptr;

public:
    virtual ~BaseItem();
    BaseItem *getNext();
    void setNext(BaseItem *next_item);
    ItemType getType();
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
};

class PhoenixDownI : public BaseItem
{
public:
    PhoenixDownI();
    bool canUse(BaseKnight *knight) override;
    void use(BaseKnight *knight) override;
};

class PhoenixDownII : public BaseItem
{
public:
    PhoenixDownII();
    bool canUse(BaseKnight *knight) override;
    void use(BaseKnight *knight) override;
};

class PhoenixDownIII : public BaseItem
{
public:
    PhoenixDownIII();
    bool canUse(BaseKnight *knight) override;
    void use(BaseKnight *knight) override;
};

class PhoenixDownIV : public BaseItem
{
public:
    PhoenixDownIV();
    bool canUse(BaseKnight *knight) override;
    void use(BaseKnight *knight) override;
};

class Antidote : public BaseItem
{
public:
    Antidote();
    bool canUse(BaseKnight *knight) override;
    void use(BaseKnight *knight) override;
};

class Events
{
private:
    int size=0;
    int *event_codes=nullptr;
public:
    explicit Events(const string &file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class BaseOpponent{
protected:
    int level=0;
    int event_code=0;
public:
    virtual ~BaseOpponent();
    virtual void interact(BaseKnight* knight)=0;
    static BaseOpponent* create(int event_code, int event_index);
};

class MadBear:public BaseOpponent{
protected:
    int baseDamage = 10;
    int gil = 100;
public:
    explicit MadBear(int level);
    void interact(BaseKnight* knight) override;
};
class Bandit:public BaseOpponent{
protected:
    int baseDamage = 15;
    int gil = 150;
public:
    explicit Bandit(int level);
    void interact(BaseKnight* knight) override;
};
class LordLupin:public BaseOpponent{
protected:
    int baseDamage = 45;
    int gil = 450;
public:
    explicit LordLupin(int level);
    void interact(BaseKnight* knight) override;
};

class Elf:public BaseOpponent{
protected:
    int baseDamage = 75;
    int gil = 750;
public:
    explicit Elf(int level);
    void interact(BaseKnight* knight) override;
};

class Troll:public BaseOpponent{
protected:
    int baseDamage = 95;
    int gil = 800;
public:
    explicit Troll(int level);
    void interact(BaseKnight* knight) override;
};

class Tornbery:public BaseOpponent{
public:
    explicit Tornbery(int level);
    void interact(BaseKnight* knight) override;
};
class QueenOfCards:public BaseOpponent{
public:
    explicit QueenOfCards(int level);
    void interact(BaseKnight* knight) override;
};
class NinaDeRings:public BaseOpponent{
public:
    NinaDeRings();
    void interact(BaseKnight* knight) override;
};

class DurianGarden:public BaseOpponent{
public:
    DurianGarden();
    void interact(BaseKnight* knight) override;
};
class OmegaWeapon:public BaseOpponent{
public:
    static bool meet;
    OmegaWeapon();
    void interact(BaseKnight* knight) override;
};
class Hades:public BaseOpponent{
public:
    static bool has_paladin_shield;
    Hades();
    void interact(BaseKnight* knight) override;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights=nullptr;
    Events *events=nullptr;
public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string &file_armyknights);
    void loadEvents(const string &file_events);
    void run();
};

#endif // __KNIGHT2_H__