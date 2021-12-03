#ifndef INVENTORY_H
#define INVENTORY_H

#include "Animal.h"
#include "Boat.h"
#include <vector> 
#include <fstream>

class Inventory {
    private: 
        int numCoins;
        int numWood;

        vector<Animal> food;
        vector<int> foodCounts;

        static const int chanceWater = 40;
        static const int chanceWood = 25;
        static const int chanceCoin = 25;

        static const int numBoats = 4;
        static const int numAnimals = 14;

        Animal animals[numAnimals];
        int ranges[numAnimals][2];
         
        Boat boats[numBoats];
        vector<Boat> purchasedBoats;
        vector<Boat> availableBoats;

        int split(string str, char sep, string arr[], int sizeArr);
        void rangeGenerator(Animal arr[], int ranges[][2], int size);
        int findInRange(int num, int ranges[][2], int size);

    public:
        Inventory(); 
        Inventory(int nC, int nW, vector<Animal> f, vector<int> fC);

        int getNumCoins() const;
        int getNumWood() const;
        Animal getFood(int i) const; 
        int getFoodCounts(int i) const;
        Animal getAnimal(int i) const;
        int getNumFoods() const;
        int getNumBoats() const;
        Boat getBoat(int i) const;
        int getNumAnimals() const;
        int getRandomAnimalIndex();

        void setNumCoins(int numCoins);
        void setNumWood(int numWood); 
        void addFood(Animal animal);
        void setFoodCount(int i, int val);
        void removeFood(int i);
        void displayInventory();
        void readAnimals(string filename, Animal animals[]);
        void readBoats(string filename, Boat boats[]);
        int lookForMaterials();
        void buyBoat();
        Boat changeBoat(Boat boat);

        void handleFailedInput();
};

#endif