#include "Animal.h"

Animal::Animal() {
    srand(time(0)); 
} 

Animal::Animal(string symbol, string name, int chanceOccurence, int chanceCatch, int hp) {
    this->symbol = symbol;
    this->name = name;
    this->chanceOccurence = chanceOccurence;
    this->chanceCatch = chanceCatch;    
    this->hp = hp;
}

string Animal::getSymbol() const {
    return symbol;
}

string Animal::getName() const {
    return name; 
}

double Animal::getChanceOccurence() const {
    return chanceOccurence;
}

double Animal::getChanceCatch() const {
    return chanceCatch;
}       

int Animal::getHP() const {
    return hp;
}

Animal Animal::getRandomAnimal(Animal animals[]) {
    Animal a;
    return a;
}

void Animal::displayAnimal() {
    cout << endl << symbol << " " 
    << name << endl 
    << "HP: " << hp << endl
    << "Probability of an encounter: " << chanceOccurence << "%" << endl 
    << "Probability of catching: " << chanceCatch << "%" << endl << endl;
}

// use the animal's chanceCatch variable to randomly determine if it is "caught" or if it "escapes"
bool Animal::catchAnimal(Animal animal) {  
    if ((rand() % 100) < (animal.getChanceCatch())) {
        cout << "You caught the " << animal.getSymbol() << " " << animal.getName() << "!" << endl;
        return true;
    }
    else {
        cout << "The " << animal.getSymbol() << " " << animal.getName() << " escaped!" << endl;
        return false;
    }
}