#include "Map.h"
using namespace std; 
 
bool inDoubleArr(int arr[][2], int numRows, int x, int y);
int findInDoubleArr(bool arr[][2], int numRows, int x, int y); /////

Map::Map() {
    // generate random coordinates for the player's starting position
    srand(time(0)); 
    playerPos[0] = rand() % rows; 
    playerPos[1] = rand() % cols;
    
    // initialize the exploredLocations array to false
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            exploredLocations[r][c] = false;
        }
    }
 
    boatSymbol = "🚣 ";
}
 
int Map::getPlayerRow()  const {
    return playerPos[0];
}

int Map::getPlayerCol()  const {
    return playerPos[1];
}

void Map::setPlayerRow(int row) {
    playerPos[0] = row;
}

void Map::setPlayerCol(int col) {
    playerPos[1] = col;
}

void Map::setBoatSymbol(string boatSymbol) {
    this->boatSymbol = boatSymbol;
}

// initialize the map
void Map::generateMap() {
    // set every element to water
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            mapData[r][c] = "🌊 ";            
        }
    }
    
    // generate random coordinates to populate the map with islands
    int rX;
    int rY;
    for(int i = 0; i < rows; i++) {
        rX = rand() % rows;
        rY = rand() % rows;
        islands[i][0] = rX;
        islands[i][1] = rY;
        mapData[rX][rY] = "🏝  ";
    }
    mapData[playerPos[0]][playerPos[1]] = boatSymbol;
}

// display the map (contents of mapData array)
void Map::displayMap() {
    cout << endl << " ____________________________________________" << endl;
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols+1; c++) {
            if(c == 0|| c == cols) {
                cout << "⎸";
            }
            if(c < cols) {
                cout << mapData[r][c];
            }
        }
        cout << endl;
    }
    cout << " --------------------------------------------" << endl;
}

// move the player's boat
int Map::move(string m) {
    char direction = m[0];
    int count = m[1]-48;

    // check if the player is currently on an island, and set the player's current location to an island before the player's boat is moved
    if(count > 0 && isIsland()) {
        mapData[playerPos[0]][playerPos[1]] = "🏝  ";
    }
    // otherwise, set the player's current location to water
    else {
        mapData[playerPos[0]][playerPos[1]] = "🌊 ";
    }
    
    if(isExplored()) {
        mapData[playerPos[0]][playerPos[1]] = "❌ ";
    }

    // check direction
    if(direction == 'n') {
        // check for out of bounds move
        if(playerPos[0] - count < 0) {
            mapData[playerPos[0]][playerPos[1]] = boatSymbol;
            return 0;
        }
        // update the corresponding element
        else {
            playerPos[0] -= count;
           
        }
    }
    else if(direction == 's') {
        if(playerPos[0] + count >= rows) {
            mapData[playerPos[0]][playerPos[1]] = boatSymbol;
            return 0;
        }
        else {
            playerPos[0] += count;
           
        }         
    }
    else if(direction == 'e') {
        if(playerPos[1] + count >= cols) {
            mapData[playerPos[0]][playerPos[1]] = boatSymbol;
            return 0;
        }
        else {
            playerPos[1] += count;
           
        }       
    }
    else if(direction == 'w') {
        if(playerPos[1] - count < 0) {
            mapData[playerPos[0]][playerPos[1]] = boatSymbol;
            return 0;
        }
        else {
            playerPos[1] -= count;
           
        }          
    }
    mapData[playerPos[0]][playerPos[1]] = boatSymbol;
    return count;
}

// check for valid move input
bool Map::validMove(string s) {
    string directions = "nsew";
    // only allow nsew and 1-9
    if(s.length() == 2 && s[1]-48 <= 9 && s[1]-48 > 0) {
        for(char c: directions) {
            if(s[0] == c) {
                return true;
            }
        }
    }
    return false;
}

bool Map::isExplored() {
    return exploredLocations[playerPos[0]][playerPos[1]];
}

void Map::setExplored() {
    exploredLocations[playerPos[0]][playerPos[1]] = true;
}

void Map::resetExplored() {
    // if the whole ocean has been explored, reset it to allow continued fishing
    bool flag = false;
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            if(mapData[r][c] != "🏝  " && !exploredLocations[r][c]) {
                flag = true;
                break;
            }
        }
    }
    if(!flag) {
        for(int r = 0; r < rows; r++) {
            for(int c = 0; c < cols; c++) {
                exploredLocations[r][c] = false;
                mapData[r][c] = "🌊 ";
            }
        } 
    }

    // if all islands have been explored, reset them to allow them to be explored again
    flag = false;
    for(int r = 0; r < rows; r++) {
        if(!exploredLocations[islands[r][0]][islands[r][1]]) {
            flag = true;
            break;
        }
    }
    if(!flag) {
        for(int r = 0; r < rows; r++) {
            exploredLocations[islands[r][0]][islands[r][1]] = false;
            mapData[islands[r][0]][islands[r][1]] = "🏝  ";
        }
    }
}

// check if the player's location is in the island location array
bool Map::isIsland() {
    return inDoubleArr(islands, rows, playerPos[0], playerPos[1]);
}

// use sharkChance and stormChance to randomly determine if the player encounters one of them
int Map::encounterObstacle() {
    int r = rand()%100;
    if(r < sharkChance) {
        cout << "🦈 Your boat was attacked by a shark and you lost " << sharkDamage << " health!" << endl;
        return sharkDamage;
    }
    else if(r >= sharkChance && r < (sharkChance+stormChance)) {
        cout << "⛈️ You got caught in a storm and lost " << stormDamage << " health!" << endl;
        return stormDamage;
    }
    return 0;
}

// check if a 2D element is in a 2D array
bool inDoubleArr(int arr[][2], int numRows, int x, int y) {
    for(int r = 0; r < numRows; r++) {
        if(arr[r][0] == x && arr[r][1] == y) {
            return true;
        }
    }
    return false; 
}