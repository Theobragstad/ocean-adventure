#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Player.h"
#include "Animal.h"
#include "Inventory.h"
#include "Boat.h" 

class Game {
    private:
        Map map;
        Player player;
        Boat boat;
        Animal animal;
        Inventory inventory;
        
        string saveFile;

        bool inAZ(string str);
        int countLines(string filename);
        int split(string str, char sep, string arr[], int sizeArr);

    public:
        Game();
        
        void start();
        void menu();
        void showStats(string filename);
        void saveInfo(string filename);
        void options();
        void actions();
        bool rescue();
        int handleMove(int i);
        void viewInventory();
        void viewAnimals();
        void viewBoats();
        void modifyBoat();
        void handleFailedInput();
};




#endif