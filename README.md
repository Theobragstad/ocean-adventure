#### Ocean Exploration 

Terminal-based exploration/adventure/survival game   

Building this game gave me further/deeper experience with C++ and object-oriented-programming as well as basic game design and mechanics such as game probabilities and random events.  

Primary features:  
- You are lost at sea
- Take control of a boat and explore an ocean map with islands as you try to survive until you're rescued
- Fish for a variety of sea creatures in water, or search for resources like water and wood on land
  - Actions are implemented with a degree of randomness to simulate a real world situation
- Find coins to upgrade your boat to improve its performance and catch larger animals
- Eat the animals you catch to replenish your health
- Survive for as many days as you can without running out of health or water
- Encounter random events like storms and sharks that hurt you
- Learn about the animals you might encounter
- Keep track of your food and supplies in your inventory
- Save your score and view previous scores
- And more...

Also, the code is designed with an emphasis on modularity of game elements, such as through dynamic file reading of information for sea creatures and boats, so additional features can be added to expand game content without needing to implement major invasive changes to the project structure or codebase.


How to run:  
Compile: g++ -std=c++20 Game.cpp Inventory.cpp Player.cpp Map.cpp Boat.cpp Animal.cpp main.cpp    
Run: ./a.out


https://user-images.githubusercontent.com/48075045/210169964-15631322-3dfb-4cba-a236-b00091c6b6e4.mp4

