#include "knight2.h"

int main(int argc, char ** argv) {
    string file_armyknights, file_events;
    if (argc == 1) {
        file_armyknights = "tc1_armyknights"; // hard-code
        file_events = "tc1_events";
    }
    else if (argc == 3)
    {
        file_armyknights = argv[1];
        file_events = argv[2];
    }
    else {
        cout << "Error number of arguments" << endl;
        exit(1);
    }
    // string path{};

    // if(std_id){
    //     path = "./" + to_string(std_id) + "/result.txt";
    // }else{
    //     path = "./result.txt";
    // }
    // const char* cpath = path.c_str();
    // freopen(cpath, "w+", stdout);
    // BEBGIN
    KnightAdventure * knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();
    
    delete knightAdventure;
    knightAdventure = nullptr;
    return 0;
}