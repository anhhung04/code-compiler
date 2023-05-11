#include "knight2.h"

bool ArmyKnights :: WinHades = false;
bool ArmyKnights :: WinOmega = false;
bool ArmyKnights :: PaladinShield = false;
bool ArmyKnights :: LancelotSpear = false;
bool ArmyKnights :: GuinevereHair = false;
bool ArmyKnights :: ExcaliburSword = false; 


/* * * BEGIN implementation of class BaseBag * * */
string BaseBag::toString() const{
    if(current_item == 0) return "Bag[count=0;]";
    string StringType[]={"Antidote","PhoenixI","PhoenixII","PhoenixIII","PhoenixIV"};
    string knight_bag = "Bag[count=" + to_string(current_item) + ";";
    Node* temp = head;
    while(temp->next != nullptr){
        knight_bag += StringType[temp->Item ->Type()]+ ",";
        temp = temp->next;
    }
    knight_bag +=StringType[temp-> Item->Type()];
    knight_bag += ']';
    return knight_bag;    
}

bool BaseBag::insertFirst(BaseItem * item){
    if(current_item == max) return false;
    else if(knight ->getType() == DRAGON &&  item ->Type() == Antidote) return false;
    else return true;
}

BaseItem * BaseBag::get(ItemType itemType){
    if(current_item == 0) return nullptr;
   
    if(itemType == Antidote){
        Node* temp = head;
        while(temp != nullptr && temp->Item -> Type() != itemType) temp = temp->next;
        if(temp == nullptr) return nullptr;
        else{
            swap(head->Item, temp->Item);
            return head -> Item;
        }
    }

    else{
        Node* temp = head;
        while(temp && temp->Item->canUse(knight) == false) temp = temp->next;
        if(temp == nullptr) return nullptr;
        else{
            swap(head->Item, temp->Item);
            return head ->Item;
        }
    }

}

bool  BaseBag::useItem(ItemType itemType){ 
    if(get(itemType) == nullptr) return false;
    else{
    if(itemType == Antidote) {
        removeItem(); 
        return true;
    }
    else{
    this->head->Item->use(knight);
    removeItem();
    return true;
    }
}
}

void BaseBag:: addItem(BaseItem *item){
    Node* temp = new Node();
    temp->Item = item;
    temp->next = head;
    head = temp;
    current_item ++;
}

void BaseBag::removeItem(){
    if(current_item == 0) return;
    current_item --;
    Node* temp = head;
    head = head->next;
    delete temp->Item;
    delete temp;
}

BaseBag::~BaseBag(){
    for(int i=0;i< current_item;i++){
        Node* temp = head;
        head = head->next;
        delete temp->Item;
        delete temp;
}
}

BaseBag::BaseBag(BaseKnight *knight, int phoenixdown, int antidote){
    this -> knight = knight;
    this -> current_item =0;
    if(knight -> getType() == DRAGON) this -> max =14;
    else if(knight -> getType() == LANCELOT) this -> max = 16;
    else if(knight -> getType() == PALADIN) this -> max =1000000000;
    else this -> max=19;
    this -> head=nullptr;
    
    for(int i=0;i<phoenixdown;i++){
        BaseItem *item= new PhoenixI_Item(); 
        if(insertFirst(item)){addItem(item);}  
    }

    if(knight -> getType() != DRAGON ){
        for(int i=0;i<antidote;i++){
        BaseItem *item= new Antidote_Item(); 
         if(insertFirst(item)){addItem(item);}  
        }
    }
}
/* * * END implementation of class BaseBag * * */


/* * * BEGIN implementation of class BaseItem * * */
bool Antidote_Item:: canUse(BaseKnight *knight){
    if (knight -> getPoisonStatus()) return true;
    else return false;
}
void Antidote_Item:: use(BaseKnight *knight){
    knight -> setPoisonStatus(false);
}
ItemType Antidote_Item:: Type(){
    return Antidote;
}

bool PhoenixI_Item::canUse(BaseKnight * knight){
if(knight->getHp() <=0) return true;
else return false;
}
void PhoenixI_Item::use(BaseKnight *knight){
    knight -> setHp(knight -> getMaxHp());
}
ItemType PhoenixI_Item:: Type(){
return PhoenixDownI;
}

bool PhoenixII_Item::canUse(BaseKnight *knight){
    if (knight -> getHp() < knight -> getMaxHp()/4) return true;
    else return false;
}
void PhoenixII_Item::use(BaseKnight *knight){
    knight -> setHp(knight -> getMaxHp());
}
ItemType PhoenixII_Item::Type(){
return PhoenixDownII;
}

bool PhoenixIII_Item::canUse(BaseKnight *knight){
    if (knight -> getHp() < knight -> getMaxHp()/3) return true;
    else return false;
}
void PhoenixIII_Item::use(BaseKnight *knight){
    if (knight -> getHp() <= 0) knight -> setHp(knight -> getMaxHp()/3);
    else knight -> setHp(knight->getHp()+knight->getMaxHp()/4);
}
ItemType PhoenixIII_Item::Type(){
return PhoenixDownIII;
}

bool PhoenixIV_Item::canUse(BaseKnight *knight){
    if (knight -> getHp() < knight -> getMaxHp()/2) return true;
    else return false;
}
void PhoenixIV_Item::use(BaseKnight *knight){
    if (knight -> getHp() <= 0) knight -> setHp(knight -> getMaxHp()/2);
    else knight -> setHp(knight->getHp()+knight->getMaxHp()/5);
}
ItemType PhoenixIV_Item::Type(){
return PhoenixDownIV;
}
/* * * END implementation of class BaseItem * * */




/* * * BEGIN implementation of class BaseKnight * * */
bool Prime(int n){
 if (n <= 1)
        return false;
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
    return true;
}

KnightType calcKnight(int maxhp){
    if (maxhp == 888) return LANCELOT;
    else if (Prime(maxhp)) return PALADIN;
    else if (maxhp == 345 || maxhp == 354 || maxhp == 453|| maxhp == 435 || maxhp == 543 || maxhp == 534) return DRAGON;
    else return NORMAL;
 }

void BaseKnight::setGil(int gil){
    if(gil > 999){
        this->overgil = gil - 999;
        this->gil = 999;
    }
    else this->gil = gil;
}

int BaseKnight::getOvergil(){
    int over = this-> overgil;
    this->overgil = 0;
    return over;
}

void BaseKnight::setHp(int temp){
    if(temp > maxhp) this->hp = maxhp;
    else this->hp = temp;
}

void BaseKnight :: HealthHp(){
    this -> bag -> useItem(PhoenixDownI);

    if (gil >=100 && this -> hp <=0) {
        this -> gil -=100;
        this -> hp = this ->maxhp/2;
    }
}

void BaseKnight::setLevel(int level){
    if(level > 10) this->level = 10;
    else this->level = level;
}

bool BaseKnight :: Insert(BaseItem *item){
    if(bag -> insertFirst(item) == false) return false;
    else {
        this -> bag -> addItem(item);
        return true;
}
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

BaseKnight::~BaseKnight(){
    delete bag;
}

BaseKnight :: BaseKnight (int maxhp){
    if(calcKnight(maxhp) == PALADIN)  this -> knightType = PALADIN; 
    else if(calcKnight(maxhp) == DRAGON)  this -> knightType = DRAGON; 
      else if(calcKnight(maxhp) == LANCELOT)  this -> knightType = LANCELOT; 
      else  this -> knightType = NORMAL;
}

BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int phoenixdownI, int antidote){
    BaseKnight *newknight = new BaseKnight(maxhp);
    newknight -> id = id;
    newknight -> hp = maxhp;
    newknight -> maxhp = maxhp;
    newknight -> level = level;
    newknight -> gil = gil;
    newknight ->bag = new BaseBag(newknight,phoenixdownI,antidote);
    return newknight;
}

double BaseKnight :: baseDamage(){
    double k;
    if( this -> getType() == DRAGON) k = 0.075;
    else if( this -> getType()== LANCELOT) k = 0.05;
    else if( this -> getType() == PALADIN) k = 0.06;
    else k=0;
    return k * this -> getHp() * this -> getLevel();
}
/* * * END implementation of class BaseKnight * * */




/* * * BEGIN implementation of class BaseOpponent * * */
MadBear::MadBear(int i) : BaseOpponent() {
    baseDamage = 10;
    baseGil = 100;
    event_id = 1;
    levelIO = (i + 1) % 10 + 1;
}
Bandit::Bandit(int i) : BaseOpponent() {
        baseDamage = 15;
        baseGil = 150;
        event_id =2;
        levelIO = (i + 2) % 10 + 1;
    }
LordLupin::LordLupin(int i) : BaseOpponent() {
        baseDamage = 45;
        baseGil = 450;
        event_id =3;
        levelIO = (i + 3) % 10 + 1;

    }
Elf::Elf(int i) : BaseOpponent() {
        baseDamage = 75;
        baseGil = 750;
        event_id =4;
        levelIO = (i + 4) % 10 + 1;
    }
Troll::    Troll(int i) : BaseOpponent() {
        baseDamage = 95;
        baseGil = 800;
        event_id =5;
        levelIO = (i + 5) % 10 + 1;
    }
Tornbery::    Tornbery(int i): BaseOpponent(){
        event_id =6;
        levelIO = (i + 6) % 10 + 1;
    }
QueenofCards ::   QueenofCards(int i): BaseOpponent(){
        event_id =7;
        levelIO = (i + 7) % 10 + 1;
    }
NinadeRings ::    NinadeRings(): BaseOpponent(){
        event_id =8;
    }
Garden ::    Garden(): BaseOpponent(){
        event_id =9;
    }
OmegaWeapon::    OmegaWeapon(): BaseOpponent(){
        event_id =10;
    }
Hades::  Hades(): BaseOpponent(){
        event_id =11;
    }
/* * * END implementation of class BaseOpponent * * */




/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

ArmyKnights::ArmyKnights (const string & file_armyknights){

    ifstream input(file_armyknights);
    input >> numKnight;
    knight = new BaseKnight*[numKnight];
    int maxhp, level, phoenixdownI, gil, antidote;
    for(int i = 0; i < numKnight; i++){
        input >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        knight[i] = BaseKnight::create(i+1, maxhp, level, gil,phoenixdownI, antidote);
    }    
}

int ArmyKnights::count() const{ return this->numKnight;}

BaseKnight * ArmyKnights::lastKnight() const{ return this->knight[numKnight-1];}

ArmyKnights::~ArmyKnights(){
    for(int i = 0; i < numKnight; i++) delete knight[i];
    delete[] knight;
}

void ArmyKnights::fight(BaseOpponent * opponent){
    while(numKnight){
    BaseKnight * last = lastKnight();

    if ( opponent -> event_id ==1 || opponent -> event_id == 2 || opponent -> event_id == 3 || opponent -> event_id == 4 || opponent -> event_id == 5){
    if ( last -> getLevel() >= opponent -> levelIO || last -> getType() ==  LANCELOT || last -> getType() ==  PALADIN ){
        last -> setGil(last -> getGil() + opponent -> baseGil); 
    }
    else {
            last->setHp(last->getHp() - (opponent ->baseDamage) * (opponent -> levelIO - last->getLevel())); 
            last ->HealthHp();  
        }
    }


    if(opponent -> event_id == 6){
    if(opponent -> levelIO <= last->getLevel()){
        last -> setLevel(last ->getLevel()+1);
    }
    else {
        if(last -> getType() == DRAGON) break;
        if(last->bag ->useItem(Antidote) == false){
            last->bag->removeItem();
            last->bag->removeItem();
            last->bag->removeItem();
            last->setHp(last->getHp() -  10);
            last ->HealthHp();
        }
    }    
    }


    if(opponent -> event_id == 7){
    if(opponent -> levelIO <= last->getLevel()) last->setGil(last->getGil() * 2);
    else if (last -> getType() == PALADIN) last -> setGil(last->getGil());
    else last->setGil(last->getGil() / 2);
    }


    if(opponent -> event_id == 8){
    if(last->getGil() >= 50 && last->getHp() < last->getMaxHp()/3){
        last->setGil(last->getGil() - 50);
        last->setHp(last->getHp() + last->getMaxHp()/5);
    }
    else break;
    }
    
    if(opponent -> event_id == 9){
    last -> setHp(last->getMaxHp());
    }


    if(opponent -> event_id==10){
        if(ArmyKnights::WinOmega == false){
            if((last->getLevel() == 10 && last->getHp() == last->getMaxHp()) || last -> getType() == DRAGON){
            ArmyKnights::WinOmega = true;
            last -> setLevel(10);
            last->setGil(999);
            }
            else {
                last -> setHp(0);
                last -> HealthHp();
}
        }
        else break;
    }


    if(opponent -> event_id == 11){
    if(ArmyKnights :: WinHades == false){
        if(last -> getLevel()==10 || (last -> getLevel() >= 8 && last -> getType() == PALADIN)){
            ArmyKnights :: WinHades = true;
        }
        else {
            last -> setHp(0);
            last -> HealthHp();}
    }
    else break;
    }


    if(last -> getHp() <=0) {
        numKnight--;
        delete last;}
    break;
}
}

void ArmyKnights:: InsertItem(BaseItem *item){
    for(int j = numKnight - 1 ; j >= 0; j--){
                if(knight[j]->Insert(item)) break;
                else if(j == 0) delete item;  
            }
}

void ArmyKnights:: setGil(){
    for(int i = numKnight - 1; i >= 0; i--){
                int overgil = knight[i]->getOvergil();
                if( overgil == 0 || i == 0)  break;
                knight[i-1]->setGil(overgil + knight[i-1]->getGil());
            }
}

bool ArmyKnights::adventure (Events * events){
   for(int i = 0; i < events->count(); i++){
        int event_id = events->get(i);
        cout << "event: " << event_id << " i = " << i << " --- ";

        if (event_id == 1) {
            BaseOpponent *event = new MadBear(i);
            this->fight(event);
            delete event;
        } 

        else if(event_id ==2){
            BaseOpponent *event = new Bandit(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==3){
            BaseOpponent *event = new LordLupin(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==4){
            BaseOpponent *event = new Elf(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==5){
            BaseOpponent *event = new Troll(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==6){
            BaseOpponent *event = new Tornbery(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==7){
            BaseOpponent *event = new  QueenofCards(i);
            this -> fight(event);
            delete event;
        }

        else if(event_id ==8){
            BaseOpponent *event = new NinadeRings();
            this -> fight(event);
            delete event;
        }

        else if(event_id ==9){
            BaseOpponent *event = new  Garden();
            this -> fight(event);
            delete event;
        }

        else if(event_id ==10){
            BaseOpponent *event = new OmegaWeapon();
            this -> fight(event);
            delete event;
        }

        else if(event_id ==11){
            BaseOpponent *event = new Hades();
            this -> fight(event);
            delete event;
            if(ArmyKnights::WinHades) this->PaladinShield = true;
        }


        else if(event_id == 95)   this->PaladinShield = true;

        else if(event_id== 96)    this->LancelotSpear = true;

        else if(event_id == 97)   this->GuinevereHair = true;

        
        else if(event_id == 98 && PaladinShield && LancelotSpear && GuinevereHair){this->ExcaliburSword = true;}
        
        else if(event_id == 112){
            BaseItem* item = new PhoenixII_Item();
             this -> InsertItem(item);
        }

        else if(event_id == 113){
            BaseItem* item = new PhoenixIII_Item();
             this -> InsertItem(item);
        }

        else if(event_id == 114){
            BaseItem* item = new PhoenixIV_Item();
            this -> InsertItem(item);
        }


        else if(event_id == 99){
            
            if(ExcaliburSword){
                this->printInfo();
                return true;
            }

            else if (!GuinevereHair || !LancelotSpear || !PaladinShield ){
                for(int i = 0; i < numKnight ; i++) delete knight[i];
                numKnight = 0;
            }
            
            else {
                int HPBoss = 5000;
                BaseKnight * checkNor = nullptr;
                int NorKnight = 0;

                for(int i=numKnight-1; i>=0 ; i--){
                BaseKnight *last = lastKnight();
                    if (last-> getType() == NORMAL) {
                        NorKnight++;
                        if (checkNor == nullptr) {
                        checkNor = last;
                        numKnight--;
                        continue;
                }
                }
                    else{
                        HPBoss -= last -> baseDamage();
                }

                if(HPBoss <= 0){
                    numKnight += NorKnight;
                    if(checkNor != nullptr ) knight[numKnight - 1] = checkNor;
                    this->printInfo();
                    if(checkNor != nullptr) delete checkNor;
                return true;
                }

                numKnight--;
                delete last;
                }

                if(checkNor != nullptr) delete checkNor;
            }
            this->printInfo();
            return false;            
        }

        this -> setGil();
        this->printInfo();
        if(numKnight == 0) return false;
    }
    return true;    
}

/* * * END implementation of class ArmyKnights * * */



/* * * BEGIN implementation of class Event * * */
Events::Events(string file_input){
    ifstream input(file_input);
    input >> numevent;
    road = new int[numevent];
    for(int i = 0; i < numevent; i++) 
    input >> road[i];
}

int Events::get(int i) const{return road[i];}

int Events::count() const{return numevent;}

Events::~Events(){delete[] road;}

/* * * END implementation of class Event * * */




/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string & file){armyKnights = new ArmyKnights(file);}

void KnightAdventure::loadEvents(const string & file){events = new Events(file);}

void KnightAdventure::run(){
    armyKnights->printResult(armyKnights->adventure(events));
}

KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}
/* * * END implementation of class KnightAdventure * * */