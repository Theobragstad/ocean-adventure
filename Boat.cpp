#include "Boat.h"

Boat::Boat() { 
    symbol = "🚣";
    name = "rowboat";
    coinCost = 0;
    woodCost = 0;
    maxHP = 100;
    maxWater = 10;
    moveCost = 1;
}  

Boat::Boat(string symbol, string name, int coinCost, int woodCost, int maxHP, int maxWater, int moveCost) {
    this->symbol = symbol;
    this->name = name;
    this->coinCost = coinCost;
    this->woodCost = woodCost;
    this->maxHP = maxHP;
    this->maxWater = maxWater;
    this->moveCost = moveCost;
}

string Boat::getSymbol() const {
    return symbol;
}

string Boat::getName() const {
    return name;
}

int Boat::getCoinCost() const {
    return coinCost;
}

int Boat::getWoodCost() const {
    return woodCost;
}

int Boat::getMaxHP() const {
    return maxHP;
}

int Boat::getMaxWater() const {
    return maxWater;
}

int Boat::getMoveCost() const {
    return moveCost;
}

int Boat::getNumBoats() const {
    return numBoats;
}

void Boat::setName(string name) {
    this->name = name;
} 

void Boat::setCoinCost(int coinCost) {
    this->coinCost = coinCost;
}

void Boat::setWoodCost(int woodCost) {
    this->woodCost = woodCost;
}

void Boat::displayBoatInfo() {
    cout << endl << symbol << " " << name << endl
    << "Max HP: " << maxHP << endl
    << "Max water storage: " << maxWater << endl
    << "HP to move one unit: " << moveCost << endl 
    << "Cost: 🪙: " << coinCost << "  🪵: " << woodCost << endl;
}