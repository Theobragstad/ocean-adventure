#ifndef BOAT_H
#define BOAT_H

#include <iostream>
using namespace std; 

class Boat {
    private:
        string symbol;
        string name;
        int coinCost;
        int woodCost;
        int maxHP;
        int maxWater;
        int moveCost;
        static const int numBoats = 4;
        int split(string str, char sep, string arr[], int sizeArr);

    public:
        Boat();
        Boat(string symbol, string name, int coinCost, int woodCost, int maxHP, int maxWater, int moveCost);

        string getSymbol() const;
        string getName() const;
        int getCoinCost() const;
        int getWoodCost() const;
        int getMaxHP() const;
        int getMaxWater() const;
        int getMoveCost() const;
        int getNumBoats() const;

        void setName(string name);
        void setCoinCost(int coinCost);
        void setWoodCost(int woodCost);
        void displayBoatInfo();
};

#endif