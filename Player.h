#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player {
    private:
        string name; 
        int hp;
        int day;
        int score;
        int water;
        int maxHP;
        int maxWater;
        int numAnimalsCaught;

    public:
        Player();
        Player(string name, int hp, int day, int score, int water, int maxHP, int maxWater, int numAnimalsCaught);

        string getName() const;
        int getHP() const;
        int getDay() const;
        int getScore() const;
        int getWater() const;
        int getMaxHP() const;
        int getMaxWater() const;
        int getNumAnimalsCaught() const;
        
        void setName(string name);
        void setHP(int hp);
        void incrementDay();
        void setScore();
        void setWater(int water);
        void setMaxHP(int maxHP);
        void setMaxWater(int maxWater);
        void incrementNumAnimalsCaught();
       
        void displayPlayerInfo();
};

#endif 