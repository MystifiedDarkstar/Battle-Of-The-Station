#pragma once
#include "Main.h"

class Ship;

class Player {
public:
    
    std::vector <Ship*> deck;

    std::vector <Ship*> hand;
    int handMaxCards = 7;

    std::vector <Ship*> battleHand;
    int battleMaxCards = 3;

    int fuel = 10;
    int maxFuel = 10;

    int actions = 2;
    int maxActions = 2;

    std::string playerName;

    int stationHP = 200;
    int maxStationHP = 200;

    void createDeck(); // creates a player deck

    template <typename T, typename U>
    void addCardsToVector(std::vector<T>& vector, int num); // this is used to add cards to deck/hands based on cardtype, prevents multiple for loops. Not used for optimisation but for clean code.

    void shuffleCards();

    void dealCards(int numToDeal);

    void viewHand(); // prints out all the cards in hand, only names of the cards and types of card.
    void viewCard(int index); // print out specific card, with all its details.
    void viewBattleHand(); // print out all details of the cards in play, including station hp
    void viewCardNames(); // prints just the names
    void viewBattleCards(); // prints out compact format of battlecards info for use in attack function for player.

    void searchPlayCardsComputer(); // used to search teh hand and put cards into play for computer pakyers.
    void searchAttackCardsComputer(Player* opponent); // used to search teh cards and attack the oppeonent 
    bool searchAttacksComputer(Player* opponent , int attCardIndex);

    void playCard(int index); // puts spefic card into battle play

    void discardCard(int index); // discards a specific card.

    void attackPlayer(Player* opponent, int oppIndex, int attCardIndex, int attAttIndex); // attack a player using a card
    void attackStation(Player* opponent, int attCardIndex, int attAttIndex);

    void endTurn(); //ends player turn, changes to other players turn.

};




