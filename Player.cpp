#include "Player.h"

Player::Player() {
    name = "";
    maxHP = 100;
    hp = maxHP;
    maxWater = 10;
    water = maxWater;
    day = 0;
    score = 0;
    numAnimalsCaught = 0;
}

Player::Player(string name, int hp, int day, int score, int water, int maxHP, int maxWater, int numAnimalsCaught) {
    this->name = name;
    this->hp = hp;
    this->day = day; 
    this->score = score;
    this->water = water;
    this->maxHP = maxHP;
    this->maxWater = maxWater;
    this->numAnimalsCaught = numAnimalsCaught;
}

string Player::getName() const {
    return name;
}

int Player::getHP() const {
    return hp;
}

int Player::getDay() const {
    return day;
}

int Player::getScore() const {
    return score;
}

int Player::getWater() const {
    return water; 
}

int Player::getMaxHP() const {
    return maxHP;
}

int Player::getMaxWater() const {
    return maxWater;
}

int Player::getNumAnimalsCaught() const {
    return numAnimalsCaught;
}

void Player::setName(string name) {
    this->name = name;
}

// setHP() function to prevent negative HP or HP greater than the maxHP
void Player::setHP(int hp) {
    if(this->hp+hp < 0) {
        this->hp = 0;
    }
    else if(this->hp+hp > maxHP) {
        this->hp = maxHP;
    }
    else {
        this->hp += hp;
    }
}

void Player::incrementDay() {
    day++;
}

// calculate score
void Player::setScore() {
    score = (day+numAnimalsCaught)*10;
}

void Player::setWater(int water) {
    if(this->water+water < 0) {
        this->water = 0;
    }
    else if(this->water+water > maxWater) {
        this->water = maxWater;
    }
    else {
        this->water += water;
    }
}

void Player::setMaxHP(int maxHP) {
    this->maxHP = maxHP;
}

void Player::setMaxWater(int maxWater) {
    this->maxWater = maxWater;
}

void Player::incrementNumAnimalsCaught() {
    numAnimalsCaught++;
}

void Player::displayPlayerInfo() {
    cout << "💛: " << hp << "   💧: " << water << "   📅: " << day << "   Score: " << score << endl << endl;
}