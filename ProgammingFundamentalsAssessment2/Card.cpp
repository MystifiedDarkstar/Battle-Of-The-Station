#include "Card.h"



void Ship::printShipInfo(int index) {

	std::cout << "\nCard " << index << " : " << cardName
			  << "\n\t> " << description
			  << "\n\t> " << shipHP << " HP / " << maxShipHP << " HP"
			  << "\n  Attacks: "
			  << "\n   Attack 0 : " << attacks[0].name 
			  << "\n\t> " << attacks[0].description
			  << "\n\t> " << attacks[0].damage << " damage per attack."
			  << "\n\t> " << attacks[0].fuelCost << " energy per attack."
			  << "\n   Attack 1 : " << attacks[1].name 
			  << "\n\t> " << attacks[1].description
			  << "\n\t> " << attacks[1].damage << " damage per attack."
			  << "\n\t> " << attacks[1].fuelCost << " energy per attack.\n" << std::endl;

}


