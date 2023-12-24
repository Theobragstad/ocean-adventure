build: Animal.cpp Animal.h Boat.cpp Boat.h Inventory.cpp Inventory.h main.cpp Game.cpp Game.h Map.cpp Map.h Player.cpp Player.h Makefile
	g++ Animal.cpp Boat.cpp Inventory.cpp main.cpp Game.cpp Map.cpp Player.cpp -std=c++20 -o ocean-adv
