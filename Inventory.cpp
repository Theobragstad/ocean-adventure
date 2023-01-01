#include "Inventory.h"

Inventory::Inventory() {
    numCoins = 2; 
    numWood = 3; 

    // call read functions to initialize animal and boat arrays
    readAnimals("animalInfo.txt", animals);
    readBoats("boatInfo.txt", boats);

    // call rangeGenerator() to initialize the ranges array for animal encounter probabilities
    rangeGenerator(animals, ranges, numAnimals);

    // initialize the availableBoats vector with the boats that are available for purchase
    for(int i = 1; i < numBoats; i++) {
        availableBoats.push_back(boats[i]);
    }
    
    // the default boat is already purchased
    purchasedBoats.push_back(boats[0]);
}

Inventory::Inventory(int nC, int nW, vector<Animal> f, vector<int> fC) {
    numCoins = nC;
    numWood = nW;
    vector<Animal> food = f;
    vector<int> foodCounts = fC;
}
        
int Inventory::getNumCoins() const {
    return numCoins;
}

int Inventory::getNumWood() const {
    return numWood;
}

Animal Inventory::getFood(int i) const {
    return food.at(i);
}

int Inventory::getFoodCounts(int i) const {
    return foodCounts.at(i);
}

Animal Inventory::getAnimal(int i) const {
    return animals[i];
}

int Inventory::getNumFoods() const {
    return food.size();
}

int Inventory::getNumBoats() const {
    return numBoats;
}

Boat Inventory::getBoat(int i) const {
    return boats[i]; 
}

int Inventory::getNumAnimals() const {
    return numAnimals;
}

// setNumCoins function to prevent negative coins
void Inventory::setNumCoins(int numCoins) {
    if(this->numCoins+numCoins < 0) {
        this->numCoins = 0;
    }
    else {
        this->numCoins += numCoins;
    }
}

void Inventory::setNumWood(int numWood) {
    if(this->numWood+numWood < 0) {
        this->numWood = 0;
    }
    else {
        this->numWood += numWood;
    }
}

// adds an animal to the food vector
void Inventory::addFood(Animal animal) {
    // check if animal is already in the vector
    int index = -1;
    for(int i = 0; i < food.size(); i++) {
        if(food.at(i).getSymbol() == animal.getSymbol()) {
            index = i;
        }
    }
    // if the animal is not in the vector, add it
    if(index == -1) {
        food.push_back(animal);
        foodCounts.push_back(1);
    }
    // otherwise, increase the foodCount value for that animal
    else {
        foodCounts.at(index)++;
    }
}

void Inventory::setFoodCount(int i, int val) {
    foodCounts.at(i) += val;
}

void Inventory::removeFood(int i) {
    food.erase(food.begin()+i);
    foodCounts.erase(foodCounts.begin()+i);
}

void Inventory::displayInventory() {  
    cout << endl << "Inventory:" << endl << "[🪙 : " << numCoins << ", 🪵 : " << numWood << "]" << endl
    << "Food: [";
    for(int i = 0; i < food.size(); i++) {
        if(i != food.size()-1) {
            cout << food.at(i).getSymbol() << " : " << foodCounts.at(i) << ", ";
        }
        else {
            cout << food.at(i).getSymbol() << " : " << foodCounts.at(i);
        }
    }
    cout << "]" << endl;
}

// read in the animals to fill the animals array from the text file
void Inventory::readAnimals(string filename, Animal animals[]) {
    fstream f;
    f.open(filename);
    string line;
    int numCol = 5;
    string arr[numCol];
    int c = 0;

    while(getline(f, line)) {
        if(line.length() > 0) {
            split(line, ',', arr, numCol);
            animals[c] = Animal(arr[0], arr[1], stoi(arr[2]), stoi(arr[3]), stoi(arr[4]));
            for(int i = 0; i < numCol; i++) {
                arr[i] = "";
            }
            c++;
        }
    }
    f.close();
}

// read in the boats to fill the boats array from the text file
void Inventory::readBoats(string filename, Boat boats[]) {
    fstream f;
    f.open(filename);
    string line;
    int numCols = 7;
    string arr[numCols];
    int c = 0;

    while(getline(f, line)) {
        if(line.length() > 0) {
            split(line, ',', arr, numCols);
            boats[c] = Boat(arr[0], arr[1], stoi(arr[2]), stoi(arr[3]), stoi(arr[4]), stoi(arr[5]), stoi(arr[6]));
            for(int i = 0; i < numCols; i++) {
                arr[i] = "";
            }
            c++; 
        }
    }
    f.close();
}

// return a random index
int Inventory::getRandomAnimalIndex() {
    int r = rand()%100;
    // use findInRange() to find the index of the random number's location in the ranges array
    int i = findInRange(r, ranges, numAnimals);
    return i;
}

// finds the index of the row where a number is found in a 2D range array 
int Inventory::findInRange(int num, int ranges[][2], int size) {
    for(int i = 0; i < size; i++) {
        // if the number is greater than/equal to the lower bound and less than the upper bound, it's location has been found
        if(num >= ranges[i][0] && num < ranges[i][1]) {
            return i;
        }
    }
    return -1;
}

// fills a 2D array based on probabilities
void Inventory::rangeGenerator(Animal arr[], int ranges[][2], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        // set lower bound
        ranges[i][0] = sum;
        sum += arr[i].getChanceOccurence();
        // set upper bound
        ranges[i][1] = sum;
    }
}

// allow the player to find materials based on their probabilities of being found
int Inventory::lookForMaterials() {
    int n = rand() % 100;
    // this algorithm is a simplified version of the one used to get a random animal index (described above)
    if(n < chanceWater) {
        cout << endl << "💧 You found some fresh water and gained a water point!" << endl;
        return 1;
    }
    else if(n < (chanceWater+chanceWood)) {
        cout << endl <<  "🪵 You found a piece of wood!" << endl;
        numWood++;
    }
    else if(n > (chanceWater+chanceWood) && n < (chanceWater+chanceWood+chanceCoin)) {
        cout <<  endl << "🪙 You found an old silver coin!" << endl;
        numCoins++;
    }
    else {
        cout <<  endl << "There's nothing here! Try another island." << endl;
    }
    return 0;

}

// allows the player to buy a boat
void Inventory::buyBoat() {
    int input1;
    string input2;

    // if the player hasn't bought all the available boats
    if(purchasedBoats.size() < 4) {
        // display available boats
        cout << endl << "Available boats:" << endl;
        for(int i = 0; i < availableBoats.size(); i++) {
            cout << availableBoats.at(i).getSymbol() << " ";
        }
        cout << endl << endl;

        // get input for the boat being bought
        do {
            cout << "Enter the number of the boat you want to buy: ";
            cin >> input1;
            handleFailedInput();
        } while(input1 < 1 || input1 > availableBoats.size());

        input1--;
        availableBoats.at(input1).displayBoatInfo();

        // if the player has enough materials to buy the boat
        if(numCoins >= availableBoats.at(input1).getCoinCost() && numWood >= availableBoats.at(input1).getWoodCost()) {
            cout << endl;

            do {
                cout << "Are you sure you want to buy this boat? Enter y/n: ";
                cin >> input2;
            } while(input2 != "y" && input2 != "n");

            if(input2 == "y") {
                // subtract costs
                numCoins -= availableBoats.at(input1).getCoinCost();
                numWood -= availableBoats.at(input1).getWoodCost();
                
                cout << "You bought a " << availableBoats.at(input1).getSymbol() << " " << availableBoats.at(input1).getName() << " !" << endl;
                
                // update boat vectors
                purchasedBoats.push_back(availableBoats.at(input1));
                availableBoats.erase(availableBoats.begin()+input1);
            }
        }
        // if the player doesn't have enough materials to buy the boat they selected
        else {
            if((numCoins < availableBoats.at(input1).getCoinCost()) || (numWood < availableBoats.at(input1).getWoodCost())) {
                cout << "You need ";
            }
            if(numCoins < availableBoats.at(input1).getCoinCost()) {
                cout << availableBoats.at(input1).getCoinCost()-numCoins << " more coins ";
            }
            if(numWood < availableBoats.at(input1).getWoodCost()) {
                cout << "and " << availableBoats.at(input1).getWoodCost()-numWood << " more pieces of wood ";
            }
            cout << "to buy this boat." << endl;
        }
    }
    // if there are no more boats to buy
    else {
        cout << "There are no more boats available to purchase." << endl;
    }
}

// allows the player to change which boat they're playing with
Boat Inventory::changeBoat(Boat b) {
    int input;

    // display purchased boats
    cout << endl << "These are the boat(s) you own:" << endl;
    for(Boat b: purchasedBoats) { 
        cout << b.getSymbol() << " ";
    }
    cout << endl << endl << "You will lose any extra HP and/or water if you switch to a lower level boat." << endl;

    // get input for the boat the player wants to switch to
    do {
        cout << "Enter the number of the boat you want to switch to (-1 to quit): ";
        cin >> input;
        handleFailedInput();
        if(input == -1) {
            break;
        }
    } while(input < 1 || input > purchasedBoats.size());
    
    if(input != -1) {
        input--;
        // check if the player is already using the boat
        if(b.getSymbol() == purchasedBoats.at(input).getSymbol()) {
            cout << endl << "You're already using that boat!" << endl;
            return b;
        }
        cout << "Your boat was changed from " << b.getSymbol() << " to " << purchasedBoats.at(input).getSymbol() << " !" << endl;
        return purchasedBoats.at(input);
    }
    return b;
}

// splits a line into pieces at a separator. Used in file reading functions
int Inventory::split(string str, char sep, string arr[], int sizeArr) {
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

// clear cin if it fails (ie a string is inputted instead of an int)
void Inventory::handleFailedInput() {
    if (cin.fail())
    {
        cin.clear(); 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
