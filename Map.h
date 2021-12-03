#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdlib.h>
#include <time.h> 
using namespace std; 

class Map 
{
    private:
        static const int rows = 15; 
        static const int cols = 15;
        string mapData[rows][cols];

        int playerPos[2];
        int islands[rows][2];
        bool exploredLocations[rows][cols];

        string boatSymbol;
        
        static const int sharkChance = 7;
        static const int stormChance = 5;
        static const int sharkDamage = 10;
        static const int stormDamage = 20;

    public: 
        Map();

        int getPlayerRow() const;
        int getPlayerCol() const;
        
        void setPlayerRow(int row);
        void setPlayerCol(int col);
        void setBoatSymbol(string boatSymbol);
        
        void generateMap();
        void displayMap();
        int move(string m);
        bool validMove(string s);
        bool isExplored();
        void setExplored();
        void resetExplored();
        bool isIsland();
        int encounterObstacle();  
};
 
#endif