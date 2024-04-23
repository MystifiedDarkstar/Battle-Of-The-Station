#pragma once
#include "Main.h"

struct Attack {

    std::string name;
    std::string description;
    int damage;
    int fuelCost;

    Attack() { // def construct
    
        name = "Default Name";
        description = "Default Description";
        damage = 0;
        fuelCost = 0;

    }

    Attack(std::string attackName, std::string attackDescription, int attackDamage, int attackFuelCost) { // pass by parameter constructor

        name = attackName;
        description = attackDescription;
        damage = attackDamage;
        fuelCost = attackFuelCost;

    }
};

class Ship {

public:
    std::string cardName;
    std::string description;
    int shipHP = 0;
    int maxShipHP = 0;

    Attack attacks[2];

    void printShipInfo(int index);

};

class Destroyer : public Ship {

public:
    Destroyer() { // default constructor
        
        cardName = "Destroyer";
        description = "Destroyer is a ship card.";

        attacks[0] = Attack("Small Laser" , "Fire a small electronic beam at the enemy ship." , 5 , 1);
        attacks[1] = Attack("Rocket" , "Fire a small rocket at the enemy ship." , 10 , 2);

        shipHP = 20;
        maxShipHP = 20;

    }
};

class Cruiser : public Ship {

public:
    Cruiser() { //default constructor
        
        cardName = "Cruiser";
        description = "Cruiser is a ship card.";

        attacks[0] = Attack("Medium Laser", "Fire a medium electronic beam at the enemy ship.", 10, 2);
        attacks[1] = Attack("Assault Missile", "Fire a medium sized missile at the enemy ship.", 15, 4);

        shipHP = 35;
        maxShipHP = 35;
    
    }
};

class Battleship : public Ship {

public:
    Battleship() { //default constructor
        
        cardName = "Battleship";
        description = "Battleship is a ship card.";

        attacks[0] = Attack("Mega Pulse Laser", "Fire a large electronic beam at the enemy ship.", 15, 4);
        attacks[1] = Attack("Torpedo", "Fires a torpedo at the enemy ship causing a large amount of damage.", 25, 6);

        shipHP = 60;
        maxShipHP = 60;

    }
};


