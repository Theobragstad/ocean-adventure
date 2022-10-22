#include "Game.h"

Game::Game() {
    // generate the map and set the save filename
    map.generateMap();
    saveFile = "gameInfo.txt"; 
}

void Game::start() {
    cout << endl << "O c e a n  E x p l o r a t i o n!" << endl << endl
    << "Enter your name: ";
    string input1;
    cin >> input1;

    // allow only string input for name
    while(!inAZ(input1)) {
        cout << "Your name must have only letters in it: ";
        cin >> input1;
    }

    // set the player's name
    player.setName(input1);
    cout << endl << "Welcome, " << player.getName() << "!" << endl
    << "You are a fisherman who has become lost at sea during a storm. Try to survive until you're rescued!" << endl;

    int input2;
    do {
        cout << endl << "1. Start game" << endl << "2. View previous game stats     " << endl;
        cin >> input2;
        handleFailedInput();

        switch(input2) {
            // display the map, player info, and show options
            case 1: 
                map.displayMap();
                player.displayPlayerInfo();
                options();
                break;
            // show previous game stats
            case 2: showStats(saveFile); break;
            default: cout << endl << "Invalid choice, try again!" << endl;
        }
    } while(input2 != 1);
}

// check if a string contains only letters
bool Game::inAZ(string str) {
    for(char c: str) {
        if(c < 65 || c > 122 || (c > 90 && c < 97)) {
            return false;
        }
    }
    return true;
}

// read and display the text file containing game stats. Only shows the three most recent players.
void Game::showStats(string filename) {
    // first, count the lines in the file
    int numLines = countLines(filename);
    fstream f;
    f.open(filename);
    string line;
    const int numCol = 4;
    string arr[numCol];
    int count = 0;

    cout << endl << "Loading... " << endl << "Most recent game stats:" << endl << endl;
    // set the number of players to show
    int numShow = 3;
    
    while(getline(f, line)) {
        if(numLines <= numShow && line.length() > 0) {
            split(line, ',', arr, numCol);
            cout << "Name: " << arr[0] << endl << "Final HP: " << arr[1] << endl << "Day: " << arr[2] << endl << "Score: " << arr[3] << endl;
            for(int i = 0; i < numCol; i++) {
                arr[i] = "";
            }
            cout << endl;
            count++;
        }
        numLines--;
    }
    f.close();
    if(count == 0) {
        cout << "No previous games have been played." << endl;
    }
}

// display the game options
void Game::options() {
    int input;
    int moveCount = 0;

    do {
        // check if the player has been rescued
        if(rescue()) {
            break;
        }
        // check if the player has died
        if(player.getHP() <= 0 || player.getWater() <= 0) {
            cout << "You died!" << endl;
            break; 
        }
        // check if the map needs to be reset
        map.resetExplored();

        // call menu() to display the choices
        menu();
        cin >> input;

        handleFailedInput();

        switch(input) {
            // call the appropriate functions to handle each case
            case 1: moveCount += handleMove(moveCount); break;
            case 2: actions(); break;
            case 3: viewInventory(); break;
            case 4: viewAnimals(); break;
            case 5: viewBoats(); break;
            case 6: modifyBoat(); break;  
            case 7: cout << endl << "Thank you for playing!" << endl; break;
            default: cout << endl << "Invalid choice, try again!" << endl;
        }
    } while(input != 7);

    // call saveInfo() to save this game's stats
    saveInfo(saveFile);
}

void Game::menu() {
    cout << endl << "1. Move" << endl;
    if(map.isIsland()) {
        cout << "2. Look for materials" << endl;
    }
    else {
        cout << "2. Cast fishing rod" << endl;
    }
    cout << "3. View inventory" << endl
    << "4. View animal info" << endl
    << "5. View boat info" << endl 
    << "6. Modify boat" << endl
    << "7. End game" << endl;
}

// allows player to fish or look for materials
void Game::actions() {
    string input;
    int animalIndex;
    bool encounter = false;

    if(!map.isExplored()) {
        // set the location to explored
        map.setExplored();
        
        // if the player is on an island, call the lookForMaterials() function, and update the player's water if needed
        if(map.isIsland()) {
            player.setWater(inventory.lookForMaterials());
        }
        // otherwise, the player is on the ocean
        else {
            cout << endl << "Casting... ";
            // set the animalIndex to the result of the call to getRandomAnimalIndex()
            animalIndex = inventory.getRandomAnimalIndex();
            // if an animal is "encountered", set encounter to true
            if(animalIndex != -1) {
                animal = inventory.getAnimal(animalIndex);
                cout << "You hooked a " << animal.getSymbol() << " " << animal.getName() << "!" << endl;
                encounter = true;
            }
            // otherwise, no animal is encountered
            else {
                cout << "Nothing is biting! Try another spot." << endl;
                encounter = false;
            }

            // if an animal is encountered
            if(encounter) {
                // check if the boat is big enough to catch the animal
                if(boat.getName() == "rowboat" && (animal.getName() == "whale" || animal.getName() == "shark" || animal.getName() == "dolphin")) {
                    cout << endl << "...but your boat isn't big enough to catch it!" << endl;
                }
                else if(boat.getName() == "sailboat" && (animal.getName() == "whale" || animal.getName() == "shark")) {
                    cout << endl << "...but your boat isn't big enough to catch it!" << endl;
                }
                else if(boat.getName() == "speedboat" && animal.getName() == "whale") {
                    cout << endl << "...but your boat isn't big enough to catch it!" << endl;
                }
                // if the boat is big enough
                else {
                    do {
                        cout << "Do you want to try to catch it (uses 1 HP)? Enter y/n: ";
                        cin >> input;
                    } while(input != "y" && input != "n");

                    if(input == "y") {
                        player.setHP(-1);
                        cout << endl << "Reeling in... ";
                        // call catchAnimal() on the encountered animal to determine if it is caught
                        if(animal.catchAnimal(animal)) {
                            inventory.addFood(animal);
                            player.incrementNumAnimalsCaught();
                        }
                    }
                }
            }
        }
    }
    // if the location has already been explored
    else {
        if(!map.isIsland()) {
            cout << endl << "You've already fished here! Try another spot." << endl;
        }
        else {
            cout << endl << "You've already searched this island! Try another one." << endl;
        }
    }
}

// the player is rescued if they have a score of 500+
bool Game::rescue() {
    if(player.getScore() >= 500) {
        cout << "A 🚁 helicopter saved you!! Well done!!" << endl;
        return true;
    }
    return false;
}

// write the player's info to the save file 
void Game::saveInfo(string filename) {
    fstream f;
    f.open(filename, fstream::app);
    f << player.getName() << "," << player.getHP() << "," << player.getDay() << "," << player.getScore() << endl;
    f.close();
}

// loop through a file and count the number of lines
int Game::countLines(string filename) {
    fstream f;
    f.open(filename);
    string line;
    int count = 0;
    while(getline(f, line)) {
        count++;
    }
    f.close();
    return count;
}

// process the player's move
int Game::handleMove(int moveCount) {
    int count;
    string input;
    
    do { 
        cout << "Enter direction (n/s/e/w) and number (1-9) (ex: n1): ";
        cin >> input;
    } while(!map.validMove(input));

    count = map.move(input);
    map.displayMap();
    // adjust player's HP
    player.setHP(-1*count*boat.getMoveCost());

    // increment the day and remove a water point every 5 moves
    if(count != 0 && moveCount > 0 && moveCount % 4 == 0) {
        player.incrementDay();
        player.setWater(-1);
    }

    // check if the player encounters an obstacle, and update their HP if needed
    player.setHP(-1*map.encounterObstacle());
    // update the score
    player.setScore();
    player.displayPlayerInfo();

    // check if the move is invalid
    if(count == 0) {
        cout << endl << "You can't go that far! Try another move." << endl;
    }
    return 1;
}

// allow the player to see their inventory
void Game::viewInventory() {
    int input;

    inventory.displayInventory(); 

    // if the player has food to eat, and has HP less than the max HP, offer food to eat
    if(inventory.getNumFoods() > 0 && player.getHP() < player.getMaxHP()) {
        do {
            cout << endl << "Which food do you want to eat? (1+, -1 to quit): ";
            cin >> input;
            handleFailedInput();
        } while(input == 0 || input < -1 || input > inventory.getNumFoods());

        if(input != -1) {
            input--;
            // update player HP based on the food they ate
            player.setHP(inventory.getFood(input).getHP());

            cout << endl << "Eating... " << endl << "... That " << inventory.getFood(input).getSymbol() 
            << " was delicious! You gained " << inventory.getFood(input).getHP() 
            << " health and now have " << player.getHP() << " HP." << endl;

            // if it was the last food, remove the food from the vector
            if(inventory.getFoodCounts(input) == 1) {
                inventory.removeFood(input);
            }
            // otherwise, just remove 1 from the foodCount vector
            else {
                inventory.setFoodCount(input, -1);
            }
        }
    }
}

// allow the player to see all the animals
void Game::viewAnimals() {
    int input;

    cout << endl;
    for(int i = 0; i < inventory.getNumAnimals(); i++) {
        cout << inventory.getAnimal(i).getSymbol() << " ";
    }
    cout << endl;

    do {
        cout << "Enter 1-" << inventory.getNumAnimals() << ": ";
        cin >> input;
        handleFailedInput();
    } while(input < 1 || input > inventory.getNumAnimals());

    // display the selected animal
    inventory.getAnimal(input-1).displayAnimal(); 
}

// allow the player to view all the boats
void Game::viewBoats() {
    int input;

    cout << endl << "Boats:" << endl;
    for(int i = 0; i < inventory.getNumBoats(); i++) {
        cout << inventory.getBoat(i).getSymbol() << " ";
    }
    cout << endl;

    do {
        cout << "Enter 1-" << inventory.getNumBoats() << ": ";
        cin >> input;
        handleFailedInput();
    } while(input < 1 || input > inventory.getNumBoats());

    // display the selected boat
    inventory.getBoat(input-1).displayBoatInfo();
}

// allow the player to modify their boat
void Game::modifyBoat() {
    int input;

    do {
        cout << "   1. Change current boat" << endl
        << "   2. Upgrade boat" << endl;
        cin >> input;
        handleFailedInput();
    } while(input != 1 && input != 2);

    switch(input) {
        // call the changeBoat() function
        case 1: 
            boat = inventory.changeBoat(boat);

            // adjust for differences in emojii widths
            if(boat.getSymbol() == "🛥") {
                map.setBoatSymbol(boat.getSymbol() + "  ");
            }
            else {
                map.setBoatSymbol(boat.getSymbol() + " ");
            }

            // adjust the player's maxHP and maxWater variables depending on the boat they switched to
            player.setMaxHP(boat.getMaxHP());
            player.setMaxWater(boat.getMaxWater());

            // if the player's HP or water is greater than the new maxes, set them to the max
            if(player.getHP() > player.getMaxHP()) {
                player.setHP(player.getMaxHP()-player.getHP());
            }
            if(player.getWater() > player.getMaxWater()) {
                player.setWater(player.getMaxWater()-player.getWater());
            }
            break;
        // call the buyBoat() function
        case 2: inventory.buyBoat(); break;
        default: cout << "Invalid choice, try again!" << endl;
    }
}

// splits a string into pieces
int Game::split(string str, char sep, string arr[], int sizeArr) {
    int numPieces = 0; 
    int arrIndex = 0; 
    int strIndex = 0;
    while(arrIndex < sizeArr && strIndex < (int)str.length()) { 
        if(str[strIndex] != sep) { 
            arr[arrIndex] += str[strIndex]; 
            strIndex++; 
        }
        else { 
            arrIndex++; 
            strIndex++;
            numPieces++;
        }
    }
    numPieces++; 
    if(numPieces > sizeArr) { 
        return -1;
    }
    if(str.length() == 0) {
        return 0;
    }
    return numPieces;
}

// handle the error if cin fails
void Game::handleFailedInput() {
    if (cin.fail())
    {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
