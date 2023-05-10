#include "knight2.h"

int main(int argc, char ** argv) {
    string file_armyknights, file_events, std_in;
    if(argc == 4){
        std_in = argv[3];
        file_armyknights = "./uploads/mssv"+std_in+"/knights.txt"; // hard-code
        file_events = "./uploads/mssv"+std_in+"/events.txt";
    }
    string path = "./uploads/mssv"+std_in+"/output.txt";
    cout << path << endl;
    const char* cpath = path.c_str();
    freopen(cpath, "a", stdout);
    // BEBGIN
    KnightAdventure * knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();
    
    delete knightAdventure;
    knightAdventure = nullptr;
    return 0;
}