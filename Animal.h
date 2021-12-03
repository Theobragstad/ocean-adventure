#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>  
#include <stdlib.h>
#include <time.h> 
using namespace std;

class Animal {
    private:
        string symbol; 
        string name;
        int chanceOccurence;
        int chanceCatch;
        int hp;

    public:
        Animal();
        Animal(string symbol, string name, int chanceOccurence, int chanceCatch, int hp);

        string getSymbol() const;
        string getName() const; 
        double getChanceOccurence() const;
        double getChanceCatch() const; 
        int getHP() const;
        Animal getRandomAnimal(Animal animals[]); 

        void displayAnimal(); 
        bool catchAnimal(Animal animal);  
};

#endif 