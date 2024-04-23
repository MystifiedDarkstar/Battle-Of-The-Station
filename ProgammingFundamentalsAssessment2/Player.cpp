#include "Player.h"

void Player::createDeck() {

	int numOfDestroyers = 10;
	int numOfCruisers = 6;
	int numOfBattleships = 4;

	// create instances of the cards and add them to the deck vector
	addCardsToVector<Ship*, Destroyer>(deck, numOfDestroyers);
	addCardsToVector<Ship*, Cruiser>(deck, numOfCruisers);
	addCardsToVector<Ship*, Battleship>(deck, numOfBattleships);
	
	shuffleCards();

	printTextToConsole("Initialising deck of cards for " + playerName + "....");
	Sleep(1500);
	printTextToConsole("Initialised deck for " + playerName + ".");
	Sleep(500);
	
}

template <typename T, typename U>
void Player::addCardsToVector(std::vector<T>& vector, int num) {

	for (int i = 0; i < num; i++)
	{
		vector.push_back(new U);
	}
}

void Player::shuffleCards() {

	//iterate over every element in deck
	for (int i = 0; i < deck.size(); i++)
	{
		// seed a random number that will be used for swap
		int randomNumber = random(0, deck.size() - 1);
		
		//check if random number is equal to the number we are iteration, will cause error if so, so we -1
		if (randomNumber == i)
		{
			if (randomNumber == 0)
			{
				randomNumber = randomNumber + 1;
				std::swap(deck[i], deck[randomNumber]);
			}
			else
			{
				randomNumber = randomNumber - 1;
				std::swap(deck[i], deck[randomNumber]);
			}
			
		}
		//run code if not
		else
		{
			std::swap(deck[i], deck[randomNumber]);
		}
	}
}

void Player::dealCards(int numToDeal) {

	// when called deal x number of cards to the player hand, we take from the last index of the deck, since thats where we pop off from.

	// check if their is space for all elements, if not return a value which we can store. If u cannot store all, store upto the max amount. 
	int space = handMaxCards - hand.size();
	
	if (space >= numToDeal)
	{
		// there is enough space to deal all of the cards
		for (int i = 0; i < numToDeal; i++)
		{
			// add the last element in our deck to the hand, i do the last element because this is where we pop off the stack from.
			hand.push_back(deck[deck.size() - 1]);
			//pop off the last element off the stack.
			deck.pop_back();
		}
		printTextToConsole("Dealt cards to " + playerName);
	}
	else
	{
		//there is not enough room to deal all of the cards, deal upto the max amount
		for (int i = 0; i < space; i++)
		{
			// add the last element in our deck to the hand, i do the last element because this is where we pop off the stack from.
			hand.push_back(deck[deck.size() - 1]);
			//pop off the last element off the stack.
			deck.pop_back();
		}
		printTextToConsole("Dealt cards to " + playerName + ". Hand is full.");
	}
}

void Player::viewHand() {

	for (int i = 0; i < hand.size(); i++)
	{
		std::cout << "\nCard " << i << " : " << hand[i]->cardName
				  << "\n> " << hand[i]->description << std::endl;
	}
	std::cout << "\n";
}

void Player::viewCard(int index) {

			hand[index]->printShipInfo(index);
}

void Player::viewBattleHand() {

	//check if we have cards in the battlehand
	if (battleHand.size() > 0)
	{
		//there is cards in the battlehand
		//iterate over all cards in the battlehand.
		for (int i = 0; i < battleHand.size(); i++)
		{
			//call print ship info on the current element
			battleHand[i]->printShipInfo(i);
		}
	}
	else
	{
		//their is no cards in the battlehand
		printTextToConsole("There are no cards in " + playerName + "'s hand!");
	}
}

void Player::viewCardNames() {

	std::cout << "\n";
	for (int i = 0; i < hand.size(); i++)
	{
		std::cout << "Card " << i << " : " << hand[i]->cardName << "\n";
	}
}

void Player::viewBattleCards() {

	printTextToConsole(playerName + "'s cards in play: ");
	//ITERATE ALL ELEMENTS IN BATTLE HAND
	std::cout << "  0. Space Station  ( " << stationHP << " HP , " << maxStationHP << " HP )." << std::endl;
	for (int i = 1; i <= battleHand.size(); i++)
	{
		std::cout << "  " << i << ". " << battleHand[i-1]->cardName << " ( " << battleHand[i-1]->shipHP << " HP , " << battleHand[i-1]->maxShipHP << " HP )." << std::endl;
	}
	
}

void Player::playCard(int index) {

	if (index >= 0 && index <= hand.size()-1)
	{
		int space = battleMaxCards - battleHand.size();
		// check battlehand has space, if not throw an error
		if (space >= 1)
		{
			// there is space to put a card into play
			battleHand.push_back(hand[index]); // add card to battlehand at the back
			hand.erase(hand.begin() + index); // erase the card in we just added.
			actions--;
			printTextToConsole("Added " + battleHand[battleHand.size() - 1]->cardName + " to the battlehand.");
		}
		else
		{
			//there is not room to put a card into play
			printTextToConsole("There is not room to put " + hand[index]->cardName + " into play. Please try another command.");
		}
	}
	else
	{
		printTextToConsole("Could not find card in " + playerName + "'s hand!");
	}
	std::cout << "\n";
}

void Player::discardCard(int index) {

	printTextToConsole("Successfully discarded " + hand[index]->cardName + " in your hand.");
	actions--;
	hand.erase(hand.begin() + index);

}

void Player::attackPlayer(Player* opponent, int oppIndex , int attCardIndex, int attAttIndex) {

	if (oppIndex < opponent->battleHand.size() && oppIndex >= 0)
	{
		//check if the player has enough fuel to attack
		if (fuel >= battleHand[attCardIndex]->attacks[attAttIndex].fuelCost)
		{
			// attack a ship
			opponent->battleHand[oppIndex]->shipHP -= battleHand[attCardIndex]->attacks[attAttIndex].damage;
			//remove fuel from player for the attack.
			fuel -= battleHand[attCardIndex]->attacks[attAttIndex].fuelCost;
			if (opponent->battleHand[oppIndex]->shipHP <= 0)
			{
				// its ded
				printTextToConsole(playerName + " has dealt " + std::to_string(battleHand[attCardIndex]->attacks[attAttIndex].damage) + " damage to " + opponent->playerName + "'s " + opponent->battleHand[oppIndex]->cardName + ". It has been destroyed!");
				//remove the card from the enemy array
				opponent->battleHand.erase(opponent->battleHand.begin() + oppIndex);

			}
			else
			{
				// its alive, give user overview of what happened
				printTextToConsole(playerName + " has dealt " + std::to_string(battleHand[attCardIndex]->attacks[attAttIndex].damage) + " damage to " + opponent->playerName + "'s " + opponent->battleHand[oppIndex]->cardName + ". It has " + std::to_string(opponent->battleHand[oppIndex]->shipHP) + " HP remaining.");
			}
		}
		else
		{
			// you do not have enough fuel to attack
			printTextToConsole("You do not have enough fuel to attack, Consider ending your turn if you have used all of your other actions!");
		}
	}
	else
	{
		// u trash input
		printTextToConsole("Could not find card " + std::to_string(oppIndex) + " in " + opponent->playerName + "'s battle hand to attack!");
	}
	std::cout << "\n";
}

void Player::attackStation(Player* opponent, int attCardIndex, int attAttIndex) {

	// player wants to attack station
	if (fuel >= battleHand[attCardIndex]->attacks[attAttIndex].fuelCost)
	{
		opponent->stationHP = opponent->stationHP - battleHand[attCardIndex]->attacks[attAttIndex].damage;
		fuel -= battleHand[attCardIndex]->attacks[attAttIndex].fuelCost;
		if (opponent->stationHP <= 0)
		{
			// its ded
			printTextToConsole(playerName + " has destroyed " + opponent->playerName + "'s station. " + playerName + " has won the game!");
			system("pause");
			quitGame();
		}
		else
		{
			// its alive, give user overview of what happened
			printTextToConsole(playerName + " has dealt " + std::to_string(battleHand[attCardIndex]->attacks[attAttIndex].damage) + " to " + opponent->playerName + "'s station. It has " + std::to_string(opponent->stationHP) + " remaining.");
		}
	}
	else
	{
		// you do not have enough fuel to attack
		printTextToConsole("You do not have enough fuel to attack, consider ending your turn if you have used all of your other actions!");
	}
	std::cout << "\n";
}

void Player::endTurn() {

	//reset fuel for this player on next turn
	fuel = maxFuel;
	actions = maxActions;

}

void Player::searchPlayCardsComputer() {

	bool IsNoBattleships = false;
	bool IsNoCruisers = false;
	int n = 0; // iterator used to set bools

	//while we have actions and our hand has cards, this will run
	// as soon as one condition is not true this loop breaks
	while (actions > 0 && hand.size() > 0 && battleHand.size() != battleMaxCards)
	{
		//iterate all cards in the hand
		for (int i = 0; i < hand.size(); i++)
		{
			if (battleHand.size() != battleMaxCards)
			{
				if (hand[i]->cardName == "Battleship")
				{
					// move card into play
					playCard(i);
					actions--;
					Sleep(500);
				}
				else if (hand[i]->cardName == "Cruiser" && IsNoBattleships)
				{
					// move card into play
					playCard(i);
					actions--;
					Sleep(500);
				}
				else if (hand[i]->cardName == "Destroyer" && IsNoCruisers)
				{
					//move card into play
					playCard(i);
					actions--;
					Sleep(500);
				}
				else
				{
					// there was none of the current card im looking for, set bools
					if (!IsNoBattleships && n == 0)
					{
						IsNoBattleships = true;
						n++;
						continue;
					}
					else if (!IsNoCruisers && n == 1)
					{
						IsNoCruisers = true;
						n++;
						continue;
					}
				}
				Sleep(1500);
			}
			else
			{
				break;
			}
		}
	}
}

void Player::searchAttackCardsComputer(Player* opponent) {

	bool IsNoBattleships = false;
	bool IsNoCruisers = false;
	bool IsNoDestroyers = false;

	bool IsAttacking = true;
	int n = 0; // iterator used to set bools

	while (fuel > 0 && battleHand.size() > 0 && IsAttacking)
	{
		//iterate all cards in the battle hand
		for (int i = 0; i < battleHand.size(); i++)
		{
			if (battleHand[i]->cardName == "Battleship")
			{
				IsNoBattleships = searchAttacksComputer(opponent, i); // if this returns true we wont keep checking battleships because we dont have the fuel available to attack.
				Sleep(1000);
			}
			else if (battleHand[i]->cardName == "Cruiser" && IsNoBattleships)
			{
				IsNoCruisers = searchAttacksComputer(opponent, i); // if this returns true we wont keep checking cruisers because we dont have the fuel available to attack.
				Sleep(1000);
			}
			else if (battleHand[i]->cardName == "Destroyer" && IsNoCruisers)
			{
				IsNoDestroyers = searchAttacksComputer(opponent, i); // if this returns true we wont keep checking destroyers because we dont have the fuel available to attack.
				Sleep(1000);
			}
			else if (IsNoBattleships && IsNoCruisers && IsNoDestroyers)
			{
				//we dont have fuel
				IsAttacking = false;
				break;
			}
			else
			{
				// there was none of the current card im looking for, set bools
				if (!IsNoBattleships && n == 0)
				{
					IsNoBattleships = true;
					n++;
				}
				else if (!IsNoCruisers && n == 1)
				{
					IsNoCruisers = true;
					n++;
				}
				Sleep(500);
			}
		}
	}
}

bool Player::searchAttacksComputer(Player* opponent, int attCardIndex) {

	if (battleHand[attCardIndex]->attacks[1].damage > battleHand[attCardIndex]->attacks[0].damage && battleHand[attCardIndex]->attacks[1].fuelCost <= fuel)
	{
		// do attack at index 1
	
		//cehck if ooponent has cards to attack
		if (opponent->battleHand.size() > 0)
		{
			attackPlayer(opponent, 0, attCardIndex, 1);
			return false;
		}
		// if they dont we attack station
		else
		{
			attackStation(opponent, attCardIndex, 1);
			return false;
		}
	}
	else if (battleHand[attCardIndex]->attacks[0].fuelCost <= fuel)
	{
		// do attack at index 0
				//cehck if ooponent has cards to attack
		if (opponent->battleHand.size() > 0)
		{
			attackPlayer(opponent, 0, attCardIndex, 0);
			return false;
		}
		// if they dont we attack station
		else
		{
			attackStation(opponent, attCardIndex, 0);
			return false;
		}
	}
	else
	{
		return true;
	}
}
	






