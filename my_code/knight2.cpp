#include "knight2.h"

bool is_pythagoras(int n)
{
    if (n <= 100)
        return false;
    int a = n % 10, b = (n / 10) % 10, c = n / 100;
    if(a*b*c == 0) return false;
    return (a * a + b * b == c * c) || (a * a + c * c == b * b) || (b * b + c * c == a * a);
}

bool is_prime(int n)
{
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i*i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}


/* * * BEGIN implementation of class BaseBag * * */

PaladinBag::PaladinBag()
{
    this->max_size = MAX_INT;
}

PaladinBag::~PaladinBag(){
    BaseItem *item = this->get_first_item();
    while (item)
    {
        BaseItem *next = item->getNext();
        delete item;
        item = next;
    }
}

LancelotBag::LancelotBag()
{
    this->max_size = 16;
}

LancelotBag::~LancelotBag(){
    BaseItem *item = this->get_first_item();
    while (item)
    {
        BaseItem *next = item->getNext();
        delete item;
        item = next;
    }
    item = nullptr;
}

bool LancelotBag::insertFirst(BaseItem *item)
{
    if (this->size >= this->max_size || item == nullptr)
        return false;
    this->size++;
    if (this->first_item)
    {
        item->setNext(this->first_item);
        this->first_item = item;
    }
    else
    {
        this->first_item = item;
    }
    return true;
}

DragonBag::DragonBag()
{
    this->max_size = 14;
}

DragonBag::~DragonBag()
{
    BaseItem *item = this->get_first_item();
    while (item)
    {
        BaseItem *next = item->getNext();
        delete item;
        item = next;
    }
    item = nullptr;
}

NormalBag::NormalBag()
{
    this->max_size = 19;
}

NormalBag::~NormalBag()
{
    BaseItem *item = this->get_first_item();
    while (item)
    {
        BaseItem *next = item->getNext();
        delete item;
        item = next;
    }
    item = nullptr;
}


bool NormalBag::insertFirst(BaseItem *item)
{
    if (this->size >= this->max_size || item == nullptr)
        return false;
    this->size++;
    if (this->first_item)
    {
        item->setNext(this->first_item);
        this->first_item = item;
    }
    else
    {
        this->first_item = item;
    }
    return true;
}


bool DragonBag::insertFirst(BaseItem *item)
{
    if (item->getType() == ItemType::ANTIDOTE || this->size >= this->max_size || item == nullptr)
        return false;
    this->size++;
    if (this->first_item)
    {
        item->setNext(this->first_item);
        this->first_item = item;
    }
    else
    {
        this->first_item = item;
    }
    return true;
}

bool PaladinBag::insertFirst(BaseItem *item)
{
    if (item == nullptr)
        return false;
    this->size++;
    if (this->first_item)
    {
        item->setNext(this->first_item);
        this->first_item = item;
    }
    else
    {
        this->first_item = item;
    }
    return true;
}

bool BaseBag::insertFirst(BaseItem *item)
{
    if (this->size >= this->max_size || item == nullptr)
        return false;
    this->size++;
    if (this->first_item)
    {
        item->setNext(this->first_item);
        this->first_item = item;
    }
    else
    {
        this->first_item = item;
    }
    return true;
}

BaseBag::~BaseBag() noexcept {}

void BaseBag::remove_first_item()
{
    BaseItem *item = this->first_item;
    if (!item)
        return;
    if (item)
    {
        if (item->getNext())
        {
            this->first_item = item->getNext();
            this->size--;
            delete item;
        }
        else
        {
            this->first_item = nullptr;
            this->size--;
            delete item;
        }
    }
    item = nullptr;
}

BaseItem *BaseBag::get_first_item()
{
    if (this->size == 0)
        return nullptr;
    return this->first_item;
}

BaseItem *BaseBag::get(ItemType itemType)
{
    BaseItem *prev = get_first_item();
    if (!prev)
    {
        return prev;
    }
    if (prev->getType() == itemType)
    {
        return prev;
    }
    if (!prev->getNext())
    {
        if (prev->getType() == itemType)
        {
            return prev;
        }
        else
        {
            return nullptr;
        }
    }
    while (prev)
    {
        if (prev->getNext())
        {
            if (prev->getNext()->getType() == itemType)
            {
                BaseItem *item = prev->getNext();
                BaseItem *next = item->getNext();
                prev->setNext(this->first_item);
                item->setNext(this->first_item->getNext());
                this->first_item->setNext(next);
                this->first_item = item;
                return this->first_item;
            }
        }
        prev = prev->getNext();
    }
    prev = nullptr;
    return nullptr;
}

string BaseBag::toString() const
{
    string item_names[] = {"PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV", "Antidote"};
    string s{};
    string str_item_names{};
    int count = 0;
    BaseItem *item = this->first_item;
    while (item)
    {
        ++count;
        str_item_names += item_names[item->getType()];
        if (item->getNext())
            str_item_names += ",";
        item = item->getNext();
    }
    item = nullptr;
    s += "Bag[count=" + to_string(count) + ";" + str_item_names + "]";
    return s;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s{};
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

int BaseKnight::get_hp() const
{
    return this->hp;
}

int BaseKnight::get_maxhp() const
{
    return this->maxhp;
}

void BaseKnight::set_hp(int _hp)
{
    this->hp = _hp;
    if (this->hp > this->maxhp)
        this->hp = this->maxhp;
}

BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
{
    if (maxhp == 888)
    {
        return new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdown);
    }
    else if (is_pythagoras(maxhp))
    {
        return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdown);
    }
    else if (is_prime(maxhp))
    {
        return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdown);
    }
    else
    {
        return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdown);
    }
    return nullptr;
}

BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote)
{
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->next_knight = nullptr;
    this->knightType = KnightType::NORMAL;
}

BaseKnight *BaseKnight::get_next_knight()
{
    return this->next_knight;
}

void BaseKnight::increase_hp(int delta_hp)
{
    this->hp += delta_hp;
    if (this->hp > this->maxhp)
        this->hp = this->maxhp;
    if (delta_hp < 0)
    {
        this->heal();
    }
}

int BaseKnight::get_level() const
{
    return this->level;
}

void BaseKnight::grab_item(ItemType itemType)
{
    BaseItem *grab_item{};
    if (itemType == ItemType::PHOENIXDOWN_II)
    {
        grab_item = new PhoenixDownII();
    }
    else if (itemType == ItemType::PHOENIXDOWN_III)
    {
        grab_item = new PhoenixDownIII();
    }
    else if (itemType == ItemType::PHOENIXDOWN_IV)
    {
        grab_item = new PhoenixDownIV();
    }
    else if (itemType == ItemType::PHOENIXDOWN_I)
    {
        grab_item = new PhoenixDownI();
    }
    else if (itemType == ItemType::ANTIDOTE)
    {
        grab_item = new Antidote();
    }
    else
    {
        grab_item = nullptr;
    }
    bool can_insert = get_bag()->insertFirst(grab_item);
    if (!can_insert)
    {
        delete grab_item;
        grab_item = nullptr;
        if (this->get_next_knight())
        {
            this->get_next_knight()->grab_item(itemType);
        }
    }
}

BaseKnight::~BaseKnight()
{
    this->next_knight = nullptr;
    delete this->bag;
    this->bag = nullptr;
}

void BaseKnight::heal()
{
    BaseItem *item = this->bag->get_first_item();
    while (item)
    {
        if (item->getType() != ItemType::ANTIDOTE)
        {
            if (item->canUse(this))
            {
                item->use(this);
                this->bag->get(item->getType());
                this->bag->remove_first_item();
                break;
            }
        }
        item = item->getNext();
    }
    if (this->gil >= 100 && this->hp <= 0)
    {
        this->gil -= 100;
        this->hp = this->maxhp / 2;
    }
    item = nullptr;
}

void BaseKnight::set_gil(int _gil)
{
    this->gil = _gil;
}

void BaseKnight::increase_level(int _level)
{
    this->level += _level;
    if (this->level > MAX_LEVEL)
        this->level = MAX_LEVEL;
}

KnightType BaseKnight::get_knightType() const
{
    return this->knightType;
}

int BaseKnight::get_antidote() const
{
    return this->antidote;
}

void BaseKnight::set_antidote(int _antidote)
{
    this->antidote = _antidote;
    if (this->antidote < 0)
        this->antidote = 0;
}

void BaseKnight::set_next_knight(BaseKnight *knight)
{
    this->next_knight = knight;
}

int BaseKnight::get_gil() const
{
    return this->gil;
}

BaseBag *BaseKnight::get_bag()
{
    return this->bag;
}

void BaseKnight::increase_gil(int _gil)
{
    this->gil += _gil;
    if (this->gil > MAX_GIL)
    {
        if (this->get_next_knight())
            this->get_next_knight()->increase_gil(this->gil - MAX_GIL);
        this->gil = MAX_GIL;
    }
    if (this->gil < 0)
        this->gil = 0;
}

PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdown) : BaseKnight(id, maxhp, level, gil, antidote)
{
    this->knightType = KnightType::PALADIN;
    this->bag = new PaladinBag();
    bool insert = true;
    for (int i = 0; i < phoenixdown && insert; i++)
    {
        BaseItem *phoenixdown_item = new PhoenixDownI();
        insert = this->bag->insertFirst(phoenixdown_item);
        if(!insert)
        {
            delete phoenixdown_item;
            phoenixdown_item = nullptr;
        }
    }
    for (int i = 0; i < antidote && insert; i++)
    {
        BaseItem *antidote_item = new Antidote();
        insert = this->bag->insertFirst(antidote_item);
        if(!insert)
        {
            delete antidote_item;
            antidote_item = nullptr;
        }
    }
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdown) : BaseKnight(id, maxhp, level, gil, antidote)
{
    this->knightType = KnightType::NORMAL;
    this->bag = new NormalBag();
    bool insert = true;
    for (int i = 0; i < phoenixdown && insert; i++)
    {
        BaseItem *phoenixdown_i = new PhoenixDownI();
        insert = this->bag->insertFirst(phoenixdown_i);
        if(!insert)
        {
            delete phoenixdown_i;
            phoenixdown_i = nullptr;
        }
    }
    for (int i = 0; i < antidote && insert; i++)
    {
        BaseItem *antidote_item = new Antidote();
        insert = this->bag->insertFirst(antidote_item);
        if(!insert)
        {
            delete antidote_item;
            antidote_item = nullptr;
        }
    }
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdown) : BaseKnight(id, maxhp, level, gil, antidote)
{
    this->knightType = KnightType::DRAGON;
    this->bag = new DragonBag();
    bool insert = true;
    for (int i = 0; i < phoenixdown && insert; i++)
    {
        BaseItem *phoenixdown_i = new PhoenixDownI();
        insert = this->bag->insertFirst(phoenixdown_i);
        if(!insert)
        {
            delete phoenixdown_i;
            phoenixdown_i = nullptr;
        }
    }
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdown) : BaseKnight(id, maxhp, level, gil, antidote)
{
    this->knightType = KnightType::LANCELOT;
    this->bag = new LancelotBag();
    bool insert = true;
    for (int i = 0; i < phoenixdown && insert; i++)
    {
        BaseItem *phoenixdown_i = new PhoenixDownI();
        insert = this->bag->insertFirst(phoenixdown_i);
        if(!insert)
        {
            delete phoenixdown_i;
            phoenixdown_i = nullptr;
        }
    }
    for (int i = 0; i < antidote && insert; i++)
    {
        BaseItem *antidote_i = new Antidote();
        insert = this->bag->insertFirst(antidote_i);
        if(!insert)
        {
            delete antidote_i;
            antidote_i = nullptr;
        }
    }
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    ifstream knight_file(file_armyknights);
    int num_of_knights{0};
    knight_file >> num_of_knights;
    this->size = num_of_knights;
    for (int i = 0; i < num_of_knights; i++)
    {
        int maxhp, level, gil, antidote, phoenixdown;
        knight_file >> maxhp >> level >> phoenixdown >> gil >> antidote;
        BaseKnight *new_knight = BaseKnight::create(i + 1, maxhp, level, gil, antidote, phoenixdown);
        if(!new_knight){
            cout << "Error: Invalid knight type" << endl;
            exit(1);
        }
        if (this->last_knight)
        {
            new_knight->set_next_knight(this->last_knight);
            this->last_knight = new_knight;
        }
        else
        {
            this->last_knight = new_knight;
            this->last_knight->set_next_knight(nullptr);
        }
        new_knight = nullptr;
    }
    knight_file.close();
}

ArmyKnights::~ArmyKnights()
{
    BaseKnight *knight = this->last_knight;
    while (knight != nullptr)
    {
        BaseKnight *next_knight = knight->get_next_knight();
        delete knight;
        knight = next_knight;
    }
}

int ArmyKnights::count() const
{
    return this->size;
}

bool ArmyKnights::hasPaladinShield() const
{
    return this->paladin_shield || Hades::has_paladin_shield;
}

bool ArmyKnights::hasLancelotSpear() const
{
    return this->lancelot_spear;
}

bool ArmyKnights::hasGuinevereHair() const
{
    return this->guinevere_hair;
}

bool ArmyKnights::hasExcaliburSword() const
{
    return this->excalibur_sword;
}

bool ArmyKnights::adventure(Events *events)
{
    int num_of_events = events->count();
    bool result = true;
    for (int i = 0; i < num_of_events && result; i++)
    {
        int event_code = events->get(i);
        if (event_code == 112)
        {
            this->lastKnight()->grab_item(ItemType::PHOENIXDOWN_II);
        }
        else if (event_code == 113)
        {
            this->lastKnight()->grab_item(ItemType::PHOENIXDOWN_III);
        }
        else if (event_code == 114)
        {
            this->lastKnight()->grab_item(ItemType::PHOENIXDOWN_IV);
        }
        else if (event_code == 95 && !this->paladin_shield)
        {
            this->paladin_shield = true;
        }
        else if (event_code == 96 && !this->lancelot_spear)
        {
            this->lancelot_spear = true;
        }
        else if (event_code == 97 && !this->guinevere_hair)
        {
            this->guinevere_hair = true;
        }
        else if (event_code == 98 && !this->excalibur_sword)
        {
            this->excalibur_sword = hasLancelotSpear() && hasGuinevereHair() && (hasPaladinShield());
        }
        else if (event_code == 99)
        {
            if (this->excalibur_sword)
            {
                result = true;
            }
            else if (hasLancelotSpear() && hasGuinevereHair() && (hasPaladinShield()))
            {
                int blood = 5000;
                double baseDamageKnight[3] = {0.06, 0.05, 0.075};
                BaseKnight *fight_knight{};
                fight_knight = retrieve_fight_knight();
                while (fight_knight && blood > 0)
                {
                    int damage = fight_knight->get_hp() * fight_knight->get_level() * baseDamageKnight[fight_knight->get_knightType()];
                    blood -= damage;
                    if (blood > 0)
                        this->remove_knight(fight_knight);
                    fight_knight = retrieve_fight_knight();
                }
                result = blood <= 0;
                this->size = result ? this->size : 0;
            }
            else
            {
                this->size = 0;
                result = false;
            }
        }
        else if (event_code <= 11)
        {
            BaseOpponent *opponent = BaseOpponent::create(event_code, i);
            result = this->fight(opponent);
            delete opponent;
            opponent = nullptr;
        }
        cout << "event: " + to_string(event_code) + " i = " + to_string(i) + " --- ";
        this->printInfo();
    }
    return result;
}

void ArmyKnights::remove_knight(BaseKnight *knight)
{
    BaseKnight *prev = lastKnight();
    if (prev == nullptr || count() <= 0)
        return;
    while (prev)
    {
        if (prev->get_next_knight() == knight)
            break;
        prev = prev->get_next_knight();
    }
    if (prev == nullptr)
        return;
    this->size--;
    prev->set_next_knight(knight->get_next_knight());
    delete knight;
    knight = nullptr;
}

BaseKnight *ArmyKnights::retrieve_fight_knight() const
{
    BaseKnight *knight{};
    knight = this->lastKnight();
    int count = this->count();
    while (count > 0 && knight)
    {
        count--;
        if (knight->get_knightType() == KnightType::PALADIN || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::DRAGON)
        {
            return knight;
        }
        knight = knight->get_next_knight();
    }
    knight = nullptr;
    return nullptr;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    int knight_count = this->count();
    if (knight_count <= 0)
        return false;
    BaseKnight *knight = this->lastKnight();
    opponent->interact(knight);
    if (knight->get_hp() <= 0)
    {
        this->remove_last_knight();
        if(this->count()<=0 || !this->lastKnight()) return false;
        //return this->fight(opponent);
    }
    return true;
}

BaseKnight *ArmyKnights::lastKnight() const
{
    if (this->size == 0)
        return nullptr;
    return this->last_knight;
}

void ArmyKnights::remove_last_knight()
{
    BaseKnight *knight = lastKnight();
    this->last_knight = knight->get_next_knight();
    this->size--;
    delete knight;
    knight = nullptr;
}

/* * * END implementation of class ArmyKnights * * */

/* BEGIN implementation of class BaseItem*/

BaseItem::~BaseItem()
{
    this->next = nullptr;
}

BaseItem *BaseItem::getNext()
{
    return this->next;
}

void BaseItem::setNext(BaseItem *next_item)
{
    this->next = next_item;
}

ItemType BaseItem::getType()
{
    return this->itemType;
}

PhoenixDownI::PhoenixDownI()
{
    this->itemType = ItemType::PHOENIXDOWN_I;
    this->next = nullptr;
}

bool PhoenixDownI::canUse(BaseKnight *knight)
{
    return knight->get_hp() <= 0;
}

void PhoenixDownI::use(BaseKnight *knight)
{
    knight->set_hp(MAX_HP);
}

PhoenixDownII::PhoenixDownII()
{
    this->itemType = ItemType::PHOENIXDOWN_II;
    this->next = nullptr;
}

bool PhoenixDownII::canUse(BaseKnight *knight)
{
    return knight->get_hp() < knight->get_maxhp() / 4;
}

void PhoenixDownII::use(BaseKnight *knight)
{
    knight->set_hp(knight->get_maxhp());
}

PhoenixDownIII::PhoenixDownIII()
{
    this->itemType = ItemType::PHOENIXDOWN_III;
    this->next = nullptr;
}

bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    return knight->get_hp() < knight->get_maxhp() / 3;
}

void PhoenixDownIII::use(BaseKnight *knight)
{
    if (knight->get_hp() <= 0)
        knight->set_hp(knight->get_maxhp() / 3);
    else
        knight->increase_hp(knight->get_maxhp() / 4);
}

PhoenixDownIV::PhoenixDownIV()
{
    this->itemType = ItemType::PHOENIXDOWN_IV;
    this->next = nullptr;
}

bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    return knight->get_hp() < knight->get_maxhp() / 2;
}

void PhoenixDownIV::use(BaseKnight *knight)
{
    if (knight->get_hp() <= 0)
        knight->set_hp(knight->get_maxhp() / 2);
    else
        knight->increase_hp(knight->get_maxhp() / 5);
}

Antidote::Antidote()
{
    this->itemType = ItemType::ANTIDOTE;
    this->next = nullptr;
}

bool Antidote::canUse(BaseKnight *knight)
{
    return (knight->get_antidote() >= 1);
}

void Antidote::use(BaseKnight *knight)
{
    if (knight->get_knightType() == KnightType::DRAGON)
    {
        return;
    }
    knight->set_antidote(knight->get_antidote() - 1);
}

/* END implementation of class BaseItem*/

/*BEGIN implementation of class Events*/
int Events::count() const
{
    return this->size;
}

int Events::get(int index) const
{
    return this->event_codes[index];
}

Events::Events(const string &file_events)
{
    ifstream event_file(file_events);
    int num_of_events{0};
    event_file >> num_of_events;
    this->size = num_of_events;
    this->event_codes = new int[size];
    for (int i = 0; i < num_of_events; i++)
    {
        int event;
        event_file >> event;
        event_codes[i] = event;
    }
    event_file.close();
}

Events::~Events()
{
    delete[] event_codes;
    event_codes = nullptr;
}

/*END implementation of class Events*/

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

KnightAdventure::~KnightAdventure()
{
    delete this->armyKnights;
    this->armyKnights = nullptr;
    delete this->events;
    this->events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string &file_armyknights)
{
    this->armyKnights = new ArmyKnights(file_armyknights);
}

void KnightAdventure::loadEvents(const string &file_events)
{
    this->events = new Events(file_events);
}

void KnightAdventure::run()
{
    bool result = this->armyKnights->adventure(this->events);
    this->armyKnights->printResult(result);
}

/* * * END implementation of class KnightAdventure * * */

/*BEGIN implementation of class BaseOpponent*/

BaseOpponent *BaseOpponent::create(int event_code, int event_index)
{
    int level = (event_index + event_code) % 10 + 1;
    BaseOpponent *opponent{};
    switch (event_code)
    {
        case 1:
            opponent = new MadBear(level);
            break;
        case 2:
            opponent = new Bandit(level);
            break;
        case 3:
            opponent = new LordLupin(level);
            break;
        case 4:
            opponent = new Elf(level);
            break;
        case 5:
            opponent = new Troll(level);
            break;
        case 6:
            opponent = new Tornbery(level);
            break;
        case 7:
            opponent = new QueenOfCards(level);
            break;
        case 8:
            opponent = new NinaDeRings();
            break;
        case 9:
            opponent = new DurianGarden();
            break;
        case 10:
            opponent = new OmegaWeapon();
            break;
        case 11:
            opponent = new Hades();
            break;
        default:
            opponent = nullptr;
            break;
    }
    return opponent;
}

BaseOpponent::~BaseOpponent() = default;

MadBear::MadBear(int level)
{
    this->event_code = 1;
    this->level = level;
    this->baseDamage = 10;
    this->gil = 100;
}

void MadBear::interact(BaseKnight *knight)
{
    int damage = this->baseDamage * (this->level - knight->get_level());
    if (knight->get_level() >= this->level || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::PALADIN)
        knight->increase_gil(this->gil);
    else
        knight->increase_hp(-damage);
}

Bandit::Bandit(int level)
{
    this->event_code = 2;
    this->level = level;
    this->baseDamage = 15;
    this->gil = 150;
}

void Bandit::interact(BaseKnight *knight)
{
    int damage = this->baseDamage * (this->level - knight->get_level());
    if (knight->get_level() >= this->level || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::PALADIN)
        knight->increase_gil(this->gil);
    else
        knight->increase_hp(-damage);
}

LordLupin::LordLupin(int level)
{
    this->event_code = 3;
    this->level = level;
    this->baseDamage = 45;
    this->gil = 450;
}

void LordLupin::interact(BaseKnight *knight)
{
    int damage = this->baseDamage * (this->level - knight->get_level());
    if (knight->get_level() >= this->level || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::PALADIN)
        knight->increase_gil(this->gil);
    else
        knight->increase_hp(-damage);
}

Elf::Elf(int level)
{
    this->event_code = 4;
    this->level = level;
    this->baseDamage = 75;
    this->gil = 750;
}

void Elf::interact(BaseKnight *knight)
{
    int damage = this->baseDamage * (this->level - knight->get_level());
    if (knight->get_level() >= this->level || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::PALADIN)
        knight->increase_gil(this->gil);
    else
        knight->increase_hp(-damage);
}

Troll::Troll(int level)
{
    this->event_code = 5;
    this->level = level;
    this->baseDamage = 95;
    this->gil = 800;
}

void Troll::interact(BaseKnight *knight)
{
    int damage = this->baseDamage * (this->level - knight->get_level());
    if (knight->get_level() >= this->level || knight->get_knightType() == KnightType::LANCELOT || knight->get_knightType() == KnightType::PALADIN)
        knight->increase_gil(this->gil);
    else
        knight->increase_hp(-damage);
}

Tornbery::Tornbery(int level)
{
    this->event_code = 6;
    this->level = level;
}

void Tornbery::interact(BaseKnight *knight)
{
    if (knight->get_level() >= this->level)
    {
        knight->increase_level(1);
    }
    else
    {
        if (knight->get_knightType() == KnightType::DRAGON)
        {
            return;
        }
        if (knight->get_antidote() >= 1)
        {
            BaseItem *antidote = knight->get_bag()->get(ItemType::ANTIDOTE);
            if (antidote->canUse(knight))
            {
                antidote->use(knight);
                knight->get_bag()->remove_first_item();
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                knight->get_bag()->remove_first_item();
            }
        }
    }
}

QueenOfCards::QueenOfCards(int level)
{
    this->event_code = 7;
    this->level = level;
}

void QueenOfCards::interact(BaseKnight *knight)
{
    if (knight->get_level() >= this->level)

    {
        knight->increase_gil(knight->get_gil());
    }
    else
    {
        if (knight->get_knightType() == KnightType::PALADIN)
            return;
        knight->set_gil(knight->get_gil() / 2);
    }
}

NinaDeRings::NinaDeRings()
{
    this->event_code = 8;
}

void NinaDeRings::interact(BaseKnight *knight)
{
    if (knight->get_knightType() == PALADIN && knight->get_hp() < knight->get_maxhp() / 3)
    {
        knight->increase_hp(knight->get_maxhp() / 5);
        return;
    }
    if (knight->get_gil() < 50)
        return;
    if (knight->get_hp() < knight->get_maxhp() / 3)
    {
        knight->increase_gil(-50);
        knight->increase_hp(knight->get_maxhp() / 5);
    }
}

DurianGarden::DurianGarden()
{
    this->event_code = 9;
}

void DurianGarden::interact(BaseKnight *knight)
{
    knight->set_hp(knight->get_maxhp());
}

OmegaWeapon::OmegaWeapon()
{
    this->event_code = 10;
}

bool OmegaWeapon::meet = false;

void OmegaWeapon::interact(BaseKnight *knight)
{
    if (meet)
        return;
    if (knight->get_knightType() == DRAGON || knight->get_level() == MAX_LEVEL && knight->get_hp() == knight->get_maxhp())
    {
        meet = true;
        knight->increase_level(MAX_LEVEL);
        knight->set_hp(knight->get_maxhp());
        knight->set_gil(MAX_GIL);
    }
    else
    {
        knight->increase_hp(-knight->get_hp());
    }
}

Hades::Hades()
{
    this->event_code = 11;
}

bool Hades::has_paladin_shield = false;

void Hades::interact(BaseKnight *knight)
{
    if (Hades::has_paladin_shield)
        return;
    if (knight->get_level() == MAX_LEVEL || (knight->get_knightType() == PALADIN && knight->get_level() >= 8))
    {
        has_paladin_shield = true;
        return;
    }
    knight->increase_hp(-knight->get_hp());
}
/*END implementation of class BaseOpponent*/