#include "knight2.h"
/* * * BEGIN implementation of class BaseBag * * */
// TODO: BaseBag
BaseBag::BaseBag()
{
    BaseItem *lastItem = nullptr;
    int length = 0;
}
BaseBag::~BaseBag()
{
    delete this->lastItem;
}
BaseBag::BaseBag(BaseKnight *knight, int a, int b)
{
    // cout << "BaseBag Constructor Called" << endl;
    for (int i = 1; i <= a; i++)
    {
        BaseItem *tempItemp = new PhoenixDownI();
        knight->bag->insertFirst(tempItemp);
    }

    for (int i = 1; i <= b; i++)
    {
        BaseItem *tempItemp = new Antidote();
        knight->bag->insertFirst(tempItemp);
    }
}
bool BaseBag::insertFirst(BaseItem *item)
{
    {
        if (this->isFull())
        {
            //delete this;
            return false;
        }

        if (lastItem == nullptr)
        {
            lastItem = item;
            lastItem->nextItem = nullptr;
        }
        else
        {
            item->nextItem = lastItem;
            lastItem = item;
        }
        this->length++;
        return true;
    }
}
void BaseBag::createBag(BaseKnight *knight, int a, int b)
{
    for (int i = 1; i <= a; i++)
    {
        BaseItem *tempItemp = new PhoenixDownI();
        if(!knight->bag->insertFirst(tempItemp))
        delete tempItemp;
    }
    if (knight->getType() == KnightType::DRAGON)
    {
        return;
    }
    for (int i = 1; i <= b; i++)
    {
        BaseItem *tempItemp = new Antidote();
         if(!knight->bag->insertFirst(tempItemp))
        delete tempItemp;
    }
}
BaseItem *BaseBag::get(ItemType item)
{
    if (lastItem == nullptr)
    {
        return nullptr;
    }
    BaseItem *temp = lastItem;
    if (lastItem->itemType == item)
    {
        return lastItem;
    }
    if (temp->nextItem == nullptr)
    {
        if (temp->itemType != item)
        {
            return nullptr;
        }
        else
        {
            return temp;
        }
    }
    if (temp->itemType != item)
    {
        int flag = 0;
        while (temp != nullptr)
        {
            if (temp->nextItem->itemType == item)
            {
                flag = 1;
                break;
            }
            temp = temp->nextItem;
        }
        if (flag == 0)
        {
            return nullptr;
        }
    }
    if (temp == lastItem)
    {
        BaseItem* temp2 = temp->nextItem;
        BaseItem* temp3 = temp->nextItem->nextItem;
        lastItem->nextItem = temp3;
        temp2->nextItem=lastItem;
        lastItem = temp2;
        //cout<<"Look at this: "<<this->lastItem->itemType<<endl;
        return this->lastItem;
    }
    BaseItem *temp2 = lastItem->nextItem;
    BaseItem *temp3 = temp->nextItem;
    lastItem->nextItem = temp3->nextItem;
    temp->nextItem = lastItem;
    lastItem = temp3;
    temp3->nextItem = temp2;
    return temp3;
}
BaseItem *BaseBag::pushFirstCanUsePhoenixUp(BaseKnight *knight)
{
    if (this->lastItem == nullptr)
    {
        return nullptr;
    }
    if (this->lastItem->itemType != ItemType::ANTIDOTE && this->lastItem->canUse(knight))
    {
        return this->lastItem;
    }
    BaseItem *temp = this->lastItem;
    int flag = 0;
    while (temp->nextItem != nullptr)
    {

        
        if (temp->nextItem->itemType != ItemType::ANTIDOTE && temp->nextItem->canUse(knight))
        {
            flag = 1;
            break;
        }
        temp = temp->nextItem;
    }

    if (temp->itemType != ItemType::ANTIDOTE && temp->canUse(knight))
    {
        flag = 1;
    }
    if (flag == 1)
    {
       if (temp == lastItem)
    {
        BaseItem* temp2 = temp->nextItem;
        BaseItem* temp3 = temp->nextItem->nextItem;
        lastItem->nextItem = temp3;
        temp2->nextItem=lastItem;
        lastItem = temp2;
        //cout<<"Look at this: "<<this->lastItem->itemType<<endl;
        return this->lastItem;
    }
        BaseItem *temp2 = lastItem->nextItem;
        BaseItem *temp3 = temp->nextItem;
        lastItem->nextItem = temp3->nextItem;
        temp->nextItem = lastItem;
        lastItem = temp3;
        temp3->nextItem = temp2;
        return temp3;
    }
    else
    {
        return nullptr;
    }
}
BaseItem *BaseBag::get(BaseItem *item) // item = temp->nextItem
{
    BaseItem *temp2 = lastItem->nextItem;
    BaseItem *temp3 = item;
    lastItem->nextItem = temp3->nextItem;
    item = lastItem;
    lastItem = temp2;
    temp3->nextItem = nullptr;
    this->length--;
    return temp3;
}
BaseItem *BaseBag::checkItemAt(int index)
{
    BaseItem *temp = this->lastItem;
    if (temp == nullptr)
        return nullptr;
    else
    {
        for (int i = 1; i <= index; i++)
        {
            temp = temp->nextItem;
        }
    }
    return temp;
}
string BaseBag::toString() const
{
    string arr[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    string str1 = "Bag[count=";
    string str2 = to_string(length);
    string tempstr = ";";
    string str3 = "";
    BaseItem *temp = lastItem;
    while (temp != nullptr)
    {
        ItemType tempType = temp->itemType;
        // cout << "Checked " << arr[tempType] <<endl;
        if (temp->nextItem == nullptr)
        {
            str3 = str3 + arr[tempType]; // cai thang cuoi cung khong co dau phay
        }
        else
        {
            str3 = str3 + arr[tempType] + ",";
            // cout << "Checked " << endl;
        }
        temp = temp->nextItem;
    }
    string str4 = "]";
    return str1 + str2 + tempstr + str3 + str4;
}
bool BaseBag::hasItem(ItemType itemType)
{
    if (lastItem == nullptr)
    {
        return false;
    }
    bool flag = false;
    BaseItem *temp = lastItem;
    if (temp->itemType == itemType)
    {
        return true;
    }
    while (temp != nullptr)
    {
        if (temp->nextItem->itemType == itemType)
        {
            flag = true;
            break;
        }
        temp = temp->nextItem;
    }
    return flag;
}
void BaseBag::deleteFirst()
{
    if (this->lastItem == nullptr)
    {
        return;
    }
    else
    {
        BaseItem *temp = this->lastItem;
        this->lastItem = temp->nextItem;
        temp->nextItem = nullptr;
        delete temp;
    }
    this->length--;
}
void BaseBag::removeLast3()
{
    int len = this->length;
    if (len < 3)
    {
        for (int i = 1; i <= len; i++)
        {
            this->deleteFirst();
        }
    }
    else
    {
        this->deleteFirst();
        this->deleteFirst();
        this->deleteFirst();
    }
}
bool LancelotBag::isFull()
{
    return (length >= 16);
}
DragonBag::DragonBag(BaseKnight *knight, int a, int b)
{
    for (int i = 1; i <= a; i++)
    {
        BaseItem *tempItemp = new PhoenixDownI();
        knight->getBag()->insertFirst(tempItemp);
    }
}
LancelotBag::LancelotBag(BaseKnight *knight, int a, int b) : BaseBag(knight, a, b){};
PaladinBag::PaladinBag(BaseKnight *knight, int a, int b) : BaseBag(knight, a, b){};
NormalBag::NormalBag(BaseKnight *knight, int a, int b) : BaseBag(knight, a, b){};
bool DragonBag::isFull()
{
    return (length >= 14);
}
bool NormalBag::isFull()
{
    // cout << "NormalBag Full Checked" << endl;
    return (length >= 19);
}
bool PaladinBag::isFull()
{
    return false;
}
/* * * END implementation of class BaseBag * * */
/*** BEGIN implementation of class BaseItem***/
BaseItem::BaseItem()
{
    this->nextItem = nullptr;
}
BaseItem::~BaseItem()
{
    if (this == nullptr)
        return;
    // cout<<"A Item was Deleted"<<endl;
    if (this->nextItem == nullptr)
        return;
    delete this->nextItem;
}
Antidote::Antidote()
{
    this->itemType = ItemType::ANTIDOTE;
}
PhoenixDownI::PhoenixDownI()
{
    this->itemType = ItemType::PHOENIXI;
}
PhoenixDownII::PhoenixDownII()
{
    this->itemType = ItemType::PHOENIXII;
}
PhoenixDownIII::PhoenixDownIII()
{
    this->itemType = ItemType::PHOENIXIII;
}
PhoenixDownIV::PhoenixDownIV()
{
    this->itemType = ItemType::PHOENIXIV;
}
bool Antidote::canUse(BaseKnight *knight)
{
    if (knight->haveAntidote())
        return true;
    else
        return false;
}
void Antidote::use(BaseKnight *knight)
{
    knight->setPoisoning(false);
    knight->setAntidote(knight->getAntidote() - 1);
}
bool PhoenixDownI::canUse(BaseKnight *knight)
{
    return (knight->getHP() <= 0);
}
void PhoenixDownI::use(BaseKnight *knight)
{
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownII::canUse(BaseKnight *knight)
{
    return ((knight->getHP()) < (knight->getMaxHP() / 4));
}
void PhoenixDownII::use(BaseKnight *knight)
{
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownIII::canUse(BaseKnight *knight)
{
    return ((knight->getHP()) < (knight->getMaxHP() / 3));
}
void PhoenixDownIII::use(BaseKnight *knight)
{
    int hp = knight->getHP();
    if (hp <= 0)
    {
        knight->setHP(knight->getMaxHP() / 3);
    }
    else
    {
        knight->setHP(knight->getHP() + knight->getMaxHP() / 4);
    }
}
bool PhoenixDownIV::canUse(BaseKnight *knight)
{
    return ((knight->getHP()) < (knight->getMaxHP() / 2));
}
void PhoenixDownIV::use(BaseKnight *knight)
{
    int hp = knight->getHP();
    if (hp <= 0)
    {
        knight->setHP(knight->getMaxHP() / 2);
    }
    else
    {
        knight->setHP(knight->getHP() + knight->getMaxHP() / 5);
    }
}

/***END implementatuon of class BaseItem***/
/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->nextKnight = nullptr;
}
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    this->knightBaseDamage = 0.06;
    this->knightType = KnightType::PALADIN;
    this->bag = new PaladinBag();
};
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    this->knightBaseDamage = 0.05;
    this->knightType = KnightType::LANCELOT;
    this->bag = new LancelotBag();
};
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    this->knightBaseDamage = 0;
    this->knightType = KnightType::NORMAL;
    this->bag = new NormalBag();
};
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : BaseKnight(id, maxhp, level, gil, antidote, phoenixdownI)
{
    this->knightBaseDamage = 0.075;
    this->knightType = KnightType::DRAGON;
    this->bag = new DragonBag();
    this->antidote = 0;
};
bool isPrime(int a)
{
    if (a == 1)
    {
        return false;
    }
    if (a == 2)
    {
        return true;
    }
    else
        for (int i = 2; i < sqrt(a) + 1; i++)
        {
            if (a % i == 0)
            {
                return false;
            }
        }
    return true;
}
bool isPythagoras(int hp)
{
    if (hp == 345 || hp == 354 || hp == 435 || hp == 453 || hp == 534 || hp == 543)
        return true;
    else
        return false;
}
bool BaseKnight::isPoisoning()
{
    return poisoning;
}
bool BaseKnight::hpDescrease()
{
    return this->hpDescreaseFlag;
}
void BaseKnight::setPoisoning(bool a)
{
    this->poisoning = a;
}
int BaseKnight::getHP()
{
    return this->hp;
}
int BaseKnight::getMaxHP()
{
    return this->maxhp;
}
int BaseKnight::getLevel()
{
    return this->level;
}
void BaseKnight::setLevel(int newLevel)
{
    if (newLevel > 10)
    {
        this->level = 10;
    }
    else
    {
        this->level = newLevel;
    }
}
int BaseKnight::getAntidote()
{
    return this->antidote;
}
void BaseKnight::setAntidote(int newAntidote)
{
    this->antidote = newAntidote;
}
int BaseKnight::knightDamage()
{
    return (hp * level * knightBaseDamage);
}
int BaseKnight::getGil()
{
    return this->gil;
}
int BaseKnight::exchangeGil(int change)
{
    int over = 0;
    // cout << "Gil changed: " << change << endl;
    if ((this->gil + change) > 999)
    {
        over = this->gil + change - 999;
        this->gil = 999;
        return over;
    }
    else
    {
        this->gil += change;
        return over;
    }
}
bool BaseKnight::isFullGil()
{
    return (this->gil == 999);
}
void BaseKnight::setHP(int newhp)
{
    // cout << "Checked" << endl;
    this->hpDescreaseFlag = (this->hp > newhp);
    this->hp = newhp;
}
KnightType BaseKnight::getType()
{
    return this->knightType;
}
BaseBag *BaseKnight::getBag()
{
    return this->bag;
}
bool BaseKnight::haveAntidote()
{
    return (this->antidote > 0);
}
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight *newKnight = nullptr;
    if (maxhp == 888)
    {
        newKnight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        BaseBag::createBag(newKnight, phoenixdownI, antidote);
    }
    else if (isPrime(maxhp))
    {
        newKnight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        BaseBag::createBag(newKnight, phoenixdownI, antidote);
    }
    else if (isPythagoras(maxhp))
    {
        newKnight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        BaseBag::createBag(newKnight, phoenixdownI, antidote);
    }
    else
    {
        newKnight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        // cout << "Normal Knight Created" << endl;
        BaseBag::createBag(newKnight, phoenixdownI, antidote);
    }
    return newKnight;
}
BaseKnight::~BaseKnight()
{
    if (this == nullptr)
        return;
    // cout<<"A Knight was Deleted"<<endl;
    delete this->bag;
    if (this->nextKnight == nullptr)
        return;
    delete this->nextKnight;
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
void ArmyKnights::insertFirst(BaseKnight *p)
{
    if (LastKnight == nullptr)
    {
        LastKnight = p;
        LastKnight->nextKnight = nullptr;
    }
    else
    {
        p->nextKnight = LastKnight;
        LastKnight = p;
    }
    this->length++;
}
void ArmyKnights::deleteFirst()
{
    if (LastKnight == nullptr)
    {
        return;
    }
    if (LastKnight->nextKnight == nullptr)
    {
        delete LastKnight;
        LastKnight = nullptr;
    }
    else
    {
        BaseKnight *temp = LastKnight;
        LastKnight = temp->nextKnight;
        temp->nextKnight = nullptr;
        delete temp;
    }
    this->length--;
}
bool ArmyKnights::pushKnightToLast()
{
    if (this->LastKnight->knightType != KnightType::NORMAL)
    {
        return true;
    }
    BaseKnight *knight = this->LastKnight;
    int flag = 0;
    while (knight != nullptr)
    {
        if (knight->knightType != KnightType::NORMAL)
        {
            flag = 1;
            break;
        }
        knight = knight->nextKnight;
    }
    if (flag == 1)
    {
        BaseKnight *temp2 = LastKnight->nextKnight;
        BaseKnight *temp3 = knight->nextKnight;
        LastKnight->nextKnight = temp3->nextKnight;
        LastKnight->nextKnight = LastKnight;
        LastKnight = temp3;
        temp3->nextKnight = temp2;
        return true;
    }
    else
    {
        return false;
    }
}
BaseKnight *ArmyKnights::firstFitKnight()
{
    int flag = 0;
    BaseKnight *knight = this->lastKnight();
    while (knight != nullptr)
    {
        if (knight->knightType != KnightType::NORMAL)
        {
            flag = 1;
            break;
        }
        knight = knight->nextKnight;
    }
    if (flag)
    {
        return knight;
    }
    else
    {
        return nullptr;
    }
}
void ArmyKnights::deleteKnight(BaseKnight *knight)
{
    BaseKnight *tempKnight = this->lastKnight();
    if (tempKnight == knight)
    {

        this->LastKnight = tempKnight->nextKnight;
        tempKnight->nextKnight = nullptr;
        delete tempKnight;
        this->length--;
        return;
    }
    int flag = 0;
    while (tempKnight->nextKnight->nextKnight != nullptr)
    {
        if (tempKnight->nextKnight == knight)
        {
            flag = 1;
            break;
        }
        tempKnight = tempKnight->nextKnight;
    }
    if (flag)
    {
        BaseKnight *temp = tempKnight->nextKnight;
        tempKnight->nextKnight = temp->nextKnight;
        temp->nextKnight = nullptr;
        delete temp;
        this->length--;
        return;
    }
    else
    {
        BaseKnight *temp = tempKnight->nextKnight;
        tempKnight->nextKnight = nullptr;
        temp->nextKnight = nullptr;
        delete temp;
        this->length--;
        return;
    }
}
void ArmyKnights::clearAll()
{
    int temp = this->length;
    for (int i = 1; i <= temp; i++)
    {
        this->deleteFirst();
    }
    this->LastKnight = nullptr;
}
ArmyKnights::ArmyKnights(const string &file_armyknights)
{
    ifstream myFile(file_armyknights);
    string line;
    int n = 0, hp = 0, level = 0, phoenixdownI = 0, gil = 0, antidote = 0;
    getline(myFile, line);
    stringstream ss(line);
    ss >> n;
    for (int i = 1; i <= n; i++)
    {
        getline(myFile, line);
        stringstream temp(line);
        temp >> hp >> level >> phoenixdownI >> gil >> antidote;
        BaseKnight *newKnight = BaseKnight::create(i, hp, level, gil, antidote, phoenixdownI); // trong method create da khoi tao cai tui cho moi hiep si
        this->insertFirst(newKnight);
        this->passItemFlag = false;
        this->tempItem = nullptr; // for invalid input...
    }
    myFile.close();
}
ArmyKnights::~ArmyKnights()
{
    delete this->LastKnight;
}
int ArmyKnights::count() const
{
    return length;
}
BaseKnight *ArmyKnights::lastKnight() const
{
    return LastKnight;
}
void ArmyKnights::passItem()
{
    if (this->lastKnight()->nextKnight == nullptr)
    {
        delete this->tempItem;
        this->tempItem = nullptr;
        this->passItemFlag = false;
        return;
    }
    BaseKnight *temp = this->lastKnight();
    bool flag = true;
   // cout << "PassItem Called" << endl;
    while (temp != nullptr)
    {
        if (temp->bag->insertFirst(this->tempItem))
        {
            this->tempItem = nullptr;
            this->passItemFlag = false;
            flag = false;
            break;
        }
        temp = temp->nextKnight;
    }
    if (flag)
    {
        delete this->tempItem;
        this->tempItem = nullptr;
        this->passItemFlag = false;
    }
}
void ArmyKnights::passGil()
{
    if (this->lastKnight()->nextKnight == nullptr)
    {
        this->tempGil = 0;
        this->passGilFlag = false;
        return;
    }
    BaseKnight *temp = this->lastKnight()->nextKnight;
    while (temp != nullptr)
    {
        if (this->tempGil == 0)
        {
            break;
        }
        else
        {
            this->tempGil = temp->exchangeGil(tempGil);
            temp = temp->nextKnight;
        }
    }
    // cout << "PassGil Method Called" << endl;
    this->tempGil = 0;
    this->passGilFlag = false;
}
void ArmyKnights::callPhoenix(BaseKnight *lastKnight)
{

    lastKnight->setHP(lastKnight->getMaxHP() / 2);
    lastKnight->exchangeGil(-100);
}
bool ArmyKnights::fight(BaseEvent *&event)
{
    switch (event->eventType)
    {
    case EventType::SMALL:
        event->small_AffectOn(this);
        break;
    case EventType::BIG:
        event->big_AffectOn(this);
        break;
    case EventType::PHOENIX:
        event->phoenix_AffectOn(this);
        break;
    case EventType::ITEM:
        event->item_AffectOn(this);
        break;
    }
    BaseKnight *lastknight = this->lastKnight();
    if (lastknight->isPoisoning())
    {
        // cout<<"get Poisoned"<<endl;
        if (lastknight->haveAntidote())
        {
            BaseItem *temp = lastknight->bag->get(ANTIDOTE);
            temp->use(lastknight);
            lastknight->bag->deleteFirst();
        }
        else
        {
            // cout<<"remove 3 Item"<<endl;
            lastknight->bag->removeLast3();
            lastknight->setHP(lastknight->getHP() - 10);
            lastknight->setPoisoning(false);
        }
    }
    if (lastknight->hpDescrease())
    {
        // cout<<"Hp Descrease"<<endl;
        BaseItem *item = lastknight->bag->pushFirstCanUsePhoenixUp(lastknight);
        if (item != nullptr)
        {
            // cout<<"Phoenix Used"<<endl;
            item->use(lastknight);
            lastknight->bag->deleteFirst();
        }
    }
    lastknight->hpDescreaseFlag = false;
    if (lastknight->getHP() <= 0 && lastknight->getGil() >= 100)
    {
        // cout<<"Phoenix Called"<<endl;
        this->callPhoenix(lastknight);
    }
    if (this->passGilFlag)
    {
        this->passGil();
    }
    if (this->passItemFlag)
    {
        // cout<<"passItem Flag";
        this->passItem();
    }
    if (this->lastKnight()->getHP() > 0)
    {
        return true;
    }
    else
        return false;
}
bool ArmyKnights::adventure(Events *events)
{
    BaseEvent *event = nullptr;
    bool passAllBeforeBoss = true;
    for (int i = 0; i < events->count() && passAllBeforeBoss; i++)
    {
        if (events->get(i) == 99)
        {
            BaseEvent *boss = new Ultimecia();
            boss->boss_AffectOn(this);
            delete boss;
            this->printInfo();
            break;
        }
        else
        {
            event = BaseEvent::createEvent(events->get(i), i);
            if(event==nullptr)
            {
                this->printInfo();
                continue;

            }
            while (!this->fight(event))
            {
                // cout<<"A Knight was dead"<<endl;
                this->deleteFirst();
                if (this->count() == 0)
                {
                    passAllBeforeBoss = false;
                    // break;
                }
                if (!passAllBeforeBoss)
                    break;
            }
            delete event;
        }
        this->printInfo();

    }
    if (this->count() > 0)
    {
        return true;
    }
    else
        return false;
}
void ArmyKnights::setPaladinShield()
{
    this->hadPaladinShield = true;
}
void ArmyKnights::setLancelotSpear()
{
    this->hadLancelotSpear = true;
}
void ArmyKnights::setGuinevereHair()
{
    this->hadGuinevereHair = true;
}
void ArmyKnights::setExcaliburSword()
{
    this->hadExcaliburSword = true;
}
bool ArmyKnights::hasPaladinShield() const
{
    return this->hadPaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const
{
    return this->hadLancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const
{
    return this->hadGuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const
{
    return this->hadExcaliburSword;
}
/* * * END implementation of class ArmyKnight * * */
/* * * BEGIN implementation of class Events * * */
Events::~Events()
{
    delete[] this->eventCodeList;
}
Events::Events(const string &file_events)
{
    ifstream myFile(file_events);
    string line;
    getline(myFile, line);
    int e = 0;
    stringstream temp(line);
    temp >> e;
    this->numEvents = e;
    this->eventCodeList = new int[e];
    getline(myFile, line);
    stringstream temp1(line);
    for (int i = 0; i < e; i++)
    {
        temp1 >> eventCodeList[i];
    }
    myFile.close();
}
int Events::count() const
{
    return numEvents;
}
int Events::get(int i) const
{
    return eventCodeList[i];
}
BaseEvent::BaseEvent()
{
    this->id = 0;
    this->eventCode = 0;
}
BaseEvent::~BaseEvent()
{
}
BaseEvent *BaseEvent::createEvent(int eventCode, int id)
{
    switch (eventCode)
    {
    case 1:
        return new MadBear(eventCode, id);
        break;
    case 2:
        return new Bandit(eventCode, id);
        break;
    case 3:
        return new LordLupin(eventCode, id);
        break;
    case 4:
        return new Elf(eventCode, id);
        break;
    case 5:
        return new Troll(eventCode, id);
        break;
    case 6:
        return new Tornbery(eventCode, id);
        break;
    case 7:
        return new QueenOfCards(eventCode, id);
        break;
    case 8:
        return new NinaDerings();
        break;
    case 9:
        return new DurianGarden();
    case 10:
        return new OmegaWeapon();
        break;
    case 11:
        return new Hades();
        break;
    case 112:
        return new pickPhoenixII();
        break;
    case 113:
        return new pickPhoenixIII();
        break;
    case 114:
        return new pickPhoenixIV();
        break;
    case 95:
        return new PaladinShield();
        break;
    case 96:
        return new LancelotSpear();
        break;
    case 97:
        return new GuinevereHair();
        break;
    case 98:
        return new Excalibur();
        break;
    case 99:
        return new Ultimecia();
        break;
    }
    //cout << "Error at createEvent";
    return nullptr;
}
MadBear::MadBear(int eventCode, int id)
{
    this->eventType = EventType::SMALL;
    this->id = id;
    this->eventCode = eventCode;
    this->bonusGil = 100;
    this->baseDamage = 10;
}
Bandit::Bandit(int eventCode, int id)
{
    this->eventType = EventType::SMALL;
    this->id = id;
    this->eventCode = eventCode;
    this->bonusGil = 150;
    this->baseDamage = 15;
}
LordLupin::LordLupin(int eventCode, int id)
{
    this->id = id;
    this->eventType = EventType::SMALL;
    this->eventCode = eventCode;
    this->bonusGil = 450;
    this->baseDamage = 45;
}
Elf::Elf(int eventCode, int id)
{
    this->id = id;
    this->eventType = EventType::SMALL;
    this->eventCode = eventCode;
    this->bonusGil = 750;
    this->baseDamage = 75;
}
Troll::Troll(int eventCode, int id)
{
    this->id = id;
    this->eventType = EventType::SMALL;
    this->eventCode = eventCode;
    this->bonusGil = 800;
    this->baseDamage = 95;
}
Tornbery::Tornbery(int eventCode, int id)
{
    this->id = id;
    this->eventType = EventType::BIG;
    this->eventCode = eventCode;
}
QueenOfCards::QueenOfCards(int eventCode, int id)
{
    this->id = id;
    this->eventType = EventType::BIG;
    this->eventCode = eventCode;
}
NinaDerings::NinaDerings()
{
    this->eventType = EventType::BIG;
};
DurianGarden::DurianGarden()
{
    this->eventType = EventType::BIG;
};
OmegaWeapon::OmegaWeapon()
{

    this->eventType = EventType::BIG;
};
Hades::Hades()
{
    this->eventType = EventType::BIG;
};
pickPhoenixII::pickPhoenixII()
{
    this->eventType = EventType::PHOENIX;
    this->phoenixType = 2;
};
pickPhoenixIII::pickPhoenixIII()
{
    this->eventType = EventType::PHOENIX;
    this->phoenixType = 3;
};
pickPhoenixIV::pickPhoenixIV()
{
    this->eventType = EventType::PHOENIX;
    this->phoenixType = 4;
};
PaladinShield::PaladinShield()
{
    this->eventType = EventType::ITEM;
};
LancelotSpear::LancelotSpear()
{
    this->eventType = EventType::ITEM;
};
GuinevereHair::GuinevereHair()
{
    this->eventType = EventType::ITEM;
};
Excalibur::Excalibur()
{
    this->eventType = EventType::ITEM;
};
Ultimecia::Ultimecia() { this->eventType = EventType::BOSS; };
int BaseEvent::getLevelO()
{
    return (this->id + this->eventCode) % 10 + 1;
}
void BaseEvent::small_AffectOn(ArmyKnights *armyKnights)
{
    BaseKnight *knight = armyKnights->lastKnight();
    if (armyKnights->lastKnight()->getType() == KnightType::NORMAL || armyKnights->lastKnight()->getType() == KnightType::DRAGON)
    {
        int levelO = this->getLevelO();

        if (knight->getLevel() < levelO)
        {
            knight->setHP(knight->getHP() - (this->baseDamage) * (levelO - knight->getLevel()));
            return;
        }
    }
    int over = knight->exchangeGil(this->bonusGil); // bien nay la so tien du ra sau khi bo vao tui cua lastKnight
    if (over > 0)
    {
        armyKnights->passGilFlag = true;
        armyKnights->tempGil = over;
    }
    else
        return;
}
void BaseEvent::phoenix_AffectOn(ArmyKnights *armyKnights)
{
    BaseItem *temp = nullptr;
    switch (this->phoenixType)
    {
    case (2):
        temp = new PhoenixDownII();
        break;
    case (3):
        temp = new PhoenixDownIII();
        break;
    case (4):
        temp = new PhoenixDownIV();
        break;
    }
    if (armyKnights->lastKnight()->bag->isFull())
    {
        armyKnights->passItemFlag = true;
        armyKnights->tempItem = temp;
    }
    else
    {
        armyKnights->lastKnight()->bag->insertFirst(temp);
    }
}
void BaseEvent::boss_AffectOn(ArmyKnights *armyKnights)
{

    if (armyKnights->hasExcaliburSword())
    {
        return;
    }
    if (armyKnights->hasGuinevereHair() && armyKnights->hasLancelotSpear() && armyKnights->hasPaladinShield())
    {
        int UltimeciaHP = 5000;
        BaseKnight *knight = armyKnights->firstFitKnight();
        //  cout<<knight->toString()<<endl;
        while (knight != nullptr)
        {
            // cout<<armyKnights->lastKnight()->toString()<<endl;
            // cout<<UltimeciaHP<<endl;
            UltimeciaHP -= (knight->knightDamage());
            // cout<<knight->toString()<<endl;

            if (UltimeciaHP <= 0)
            {
                break;
            }
            else
            {
                armyKnights->deleteKnight(knight);
            }
            // cout<<"Numbers of Knights: "<<armyKnights->count()<<endl;
            knight = armyKnights->firstFitKnight();
        }
        if (UltimeciaHP > 0)
        {
            armyKnights->clearAll();
        }
    }
    else
    {
        armyKnights->clearAll();
    }
}
void BaseEvent::big_AffectOn(ArmyKnights *armyKnights) {}
void BaseEvent::item_AffectOn(ArmyKnights *armyKnights) {}
void Tornbery::big_AffectOn(ArmyKnights *armyKnights)
{
    BaseKnight *knight = armyKnights->lastKnight();
    int levelO = this->getLevelO();
    if (knight->getLevel() >= levelO)
    {
        knight->setLevel(knight->getLevel() + 1);
        return;
    }
    if (knight->getType() == KnightType::DRAGON)
    {
        return;
    }
    else
    {
        knight->setPoisoning(true);
    }
}
void QueenOfCards::big_AffectOn(ArmyKnights *armyKnights)
{
    BaseKnight *knight = armyKnights->lastKnight();
    int levelO = this->getLevelO();
    if (knight->getLevel() >= levelO)
    {
        int over = knight->exchangeGil(knight->getGil()); // bien nay la so tien du ra sau khi bo vao tui cua lastKnight
        if (over > 0)
        {
            armyKnights->passGilFlag = true;
            armyKnights->tempGil = over;
        }
        return;
    }
    if (knight->getType() == KnightType::PALADIN)
    {
        return;
    }
    int fix = knight->getGil()%2 == 0? 0:1;
    knight->exchangeGil(-((knight->getGil()) / 2) - fix);
}
void NinaDerings::big_AffectOn(ArmyKnights *armyKnights)
{
    BaseKnight *knight = armyKnights->lastKnight();
    if (knight->getType() != KnightType::PALADIN && knight->getGil() < 50)
    {
        return;
    }
    if (knight->getHP() < (knight->getMaxHP() / 3))
    {
        if (knight->getType() != KnightType::PALADIN)
        {
            knight->exchangeGil(-50);
        }
        knight->setHP(knight->getHP() + (knight->getMaxHP()) / 5);
    }
}
void DurianGarden::big_AffectOn(ArmyKnights *armyKnights)
{
    armyKnights->lastKnight()->setHP(armyKnights->lastKnight()->getMaxHP());
}
void OmegaWeapon::big_AffectOn(ArmyKnights *armyKnights)
{
    if (armyKnights->wonOmegaWeapon)
    {
        return;
    }
    BaseKnight *knight = armyKnights->lastKnight();
    if ((knight->getLevel() == 10 && knight->getHP() == knight->getMaxHP()) || knight->getType() == KnightType::DRAGON)
    {
        knight->setLevel(10);
        knight->exchangeGil(999 - knight->getGil());
        armyKnights->wonOmegaWeapon = true;
    }
    else
    {
        knight->setHP(0);
    }
}
void Hades::big_AffectOn(ArmyKnights *armyKnights)
{
    if (armyKnights->wonHades)
    {
        // cout<<"Bo may da win Hades"<<endl;
        return;
    }
    BaseKnight *knight = armyKnights->lastKnight();
    if ((knight->getType() == KnightType::PALADIN && knight->getLevel() >= 8) || knight->getLevel() == 10)
    {
        if (!armyKnights->hasPaladinShield())
        {
            armyKnights->setPaladinShield();
            armyKnights->winHades = true;
        }
        armyKnights->wonHades = true;
        return;
    }
    knight->setHP(0);
}
void PaladinShield::item_AffectOn(ArmyKnights *armyKnights)
{
    if (armyKnights->winHades)
    {
        return;
    } // da co khien roi thi bo qua khong lay nua
    armyKnights->setPaladinShield();
}
void LancelotSpear::item_AffectOn(ArmyKnights *armyKnights)
{
    armyKnights->setLancelotSpear();
}
void GuinevereHair::item_AffectOn(ArmyKnights *armyKnights)
{
    armyKnights->setGuinevereHair();
}
void Excalibur::item_AffectOn(ArmyKnights *armyKnights)
{
    if (armyKnights->hasGuinevereHair() && armyKnights->hasLancelotSpear() && armyKnights->hasPaladinShield())
    {
        armyKnights->setExcaliburSword();
    }
}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure()
{
    delete armyKnights;
    delete events;
}
void KnightAdventure::loadArmyKnights(const string &fileName)
{
    armyKnights = new ArmyKnights(fileName);
}
void KnightAdventure::loadEvents(const string &fileName)
{
    events = new Events(fileName);
}
void KnightAdventure::run()
{
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */