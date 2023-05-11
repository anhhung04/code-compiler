#include "knight2.h"

int main(int argc, char **argv)
{
    string file_armyknights, file_events;
    // int std_id = 0;
    if (argc == 3)
    {
        // std_id = atoi(argv[3]);
        file_armyknights = argv[1]; // hard-code
        file_events = argv[2];
    }
    else
    {
        cout << "Error number of arguments" << endl;
        exit(1);
    }
    // string path{};
    // if (std_id)
    // {
    //     path = "./" + to_string(std_id) + "/output.txt";
    // }
    // else
    // {
    //     path = "./output.txt";
    // }
    // const char *cpath = path.c_str();
    // freopen(cpath, "w+", stdout);
    // BEBGIN
    KnightAdventure *knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();

    delete knightAdventure;
    knightAdventure = nullptr;
    return 0;
}