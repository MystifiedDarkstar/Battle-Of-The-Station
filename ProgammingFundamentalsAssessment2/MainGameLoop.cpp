#include "main.h"

Player player1; // user input
Player player2; // ai controlled



enum GameStates
{
    Default,
    UserTurn,
    AITurn,
    GameOver
};

GameStates cGameState;

std::string commands[9] = { "view_hand" , "view_card" , "view_battle" , "play_card" , "discard" , "attack" ,  "endturn" , "quit" , "commands"};

bool isAITurnInProgress = false;

std::string userInput = "";

int main()
{

    startGame();

}

void printGameHeader() {

    system("cls");
    std::cout << " ____            _     _     _                     __     _     _                      _             _     _                 " << std::endl;
    std::cout << "| __ )    __ _  | |_  | |_  | |   ___      ___    / _|   | |_  | |__     ___     ___  | |_    __ _  | |_  (_)   ___    _ __  " << std::endl;
    std::cout << "|  _ \\   / _` | | __| | __| | |  / _ \\    / _ \\  | |_    | __| | '_ \\   / _ \\   / __| | __|  / _` | | __| | |  / _ \\  | '_ \\ " << std::endl;
    std::cout << "| |_) | | (_| | | |_  | |_  | | |  __/   | (_) | |  _|   | |_  | | | | |  __/   \\__ \\ | |_  | (_| | | |_  | | | (_) | | | | |" << std::endl;
    std::cout << "|____/   \\__,_|  \\__|  \\__| |_|  \\___|    \\___/  |_|      \\__| |_| |_|  \\___|   |___/  \\__|  \\__,_|  \\__| |_|  \\___/  |_| |_|" << std::endl;

    if (cGameState == UserTurn)
    {
        std::cout << "\n" << player1.fuel << " fuel / " << player1.maxFuel << " fuel" << std::endl;
        std::cout << player1.actions << " actions / " << player1.maxActions << " actions" << std::endl;
    }
    else if (cGameState == AITurn)
    {
        std::cout << "\nCOMPUTER'S TURN" << std::endl;
    }
}

void startGame() {

    printTextToConsole("Would you like to start a new game? Yes OR No.");
    std::cout << "\n> ";

    std::cin >> userInput;
    userInput = convertStringToLowercase(userInput);
    std::cout << userInput;
    if (userInput == "yes")
    {
        //start game loop
        printTextToConsole("Ok. What is your username?");
        std::cout << "\n> ";

        std::cin >> userInput;

        player1.playerName = userInput;
        player2.playerName = "Computer";

        std::cin.ignore();
        gameLoop();
    }
}

void gameLoop() {

    player1.createDeck();

    player2.createDeck();

    startPlayerTurn();

    while (player1.stationHP > 0 && player2.stationHP > 0 && (cGameState == UserTurn || cGameState == AITurn))
    {
        if (cGameState == UserTurn)
        {
            userInput = convertStringToLowercase(userInput);
            if (userInput == "view_hand")
            {
                printTextToConsole("You are now viewing your hand.");
                player1.viewHand();

                system("pause");
                askPlayerInput();
            }
            else if (userInput == "view_card")
            {
                printTextToConsole("Which card would you like to view further details for?");
                player1.viewCardNames();
                std::cout << "\n> ";

                bool isInvalidInput = true;
                int index = 0;
                
                std::cin >> index;

                while (isInvalidInput) {
                    if (index < player1.hand.size() && index >= 0)
                    {
                        printTextToConsole("You are now viewing the specified card");
                        player1.viewCard(index);
                        isInvalidInput = false;
                    }
                    else
                    {
                        printTextToConsole("Which card would you like to view further details for?");
                        player1.viewCardNames();
                        std::cout << "\n> ";
                        std::cin >> index;
                    }
                }
                std::cin.ignore();
                system("pause");
                askPlayerInput();
            }
            else if (userInput == "view_battle")
            {
                printTextToConsole("This is your battlehand:");

                player1.viewBattleHand();

                system("pause");
                askPlayerInput();
            }
            else if (userInput == "play_card")
            {
                if (player1.actions > 0)
                {
                    printTextToConsole("Which card would you like to move into play? Enter a card index.");

                    player1.viewCardNames();

                    std::cout << "\n> ";

                    bool isInvalidInput = true;
                    int index = 0;

                    std::cin >> index;

                    while (isInvalidInput) {
                        if (index < player1.hand.size() && index >= 0)
                        {
                            player1.playCard(index);
                            isInvalidInput = false;
                        }
                        else
                        {
                            printTextToConsole("Invalid Input.");
                            player1.viewCardNames();
                            std::cout << "\n> ";
                            std::cin >> index;
                        }
                    }
                    std::cin.ignore();
                    system("pause");
                    askPlayerInput();
                }
                else
                {
                    printTextToConsole("You do not have enough actions left to move cards into play!");
                    system("pause");
                    askPlayerInput();
                }
            }
            else if (userInput == "discard")
            {
                if (player1.actions > 0)
                {
                    printTextToConsole("Which card would you like to discard? Enter a card index.");
                    player1.viewCardNames();

                    std::cout << "\n> ";

                    bool isInvalidInput = true;
                    int index = 0;

                    std::cin >> index;

                    while (isInvalidInput) {
                        if (index < player1.hand.size() && index >= 0)
                        {
                            player1.discardCard(index);
                            isInvalidInput = false;
                        }
                        else
                        {
                            printTextToConsole("Invalid Input.");
                            player1.viewCardNames();
                            std::cout << "\n> ";
                            std::cin >> index;
                        }
                    }

                    std::cin.ignore();
                    system("pause");
                    askPlayerInput();
                }
                else
                {
                    printTextToConsole("You do not have enough actions left to discard cards!");
                    system("pause");
                    askPlayerInput();
                }
            }
            else if (userInput == "attack")
            {
                //check if we have cards to attack with, otherwise no point.
                if (player1.battleHand.size() > 0)
                {
                    printTextToConsole("Which card would you like to attack? Enter a integer index.");
                    player2.viewBattleCards();
                    std::cout << "> ";
                    int oppIndex = 0;
                    std::cin >> oppIndex;

                    if (oppIndex >= 0 && oppIndex <= player2.battleHand.size())
                    {
                        printTextToConsole("Which card would you like to use to attack? Enter a integer index.");
                        player1.viewBattleHand();
                        std::cout << "> ";
                        int attCardIndex = 0;
                        std::cin >> attCardIndex;

                        if (attCardIndex >= 0 && attCardIndex < player1.battleHand.size())
                        {
                            printTextToConsole("Which attack would you like to use? Enter a integer index.");
                            player1.viewBattleHand();
                            std::cout << "> ";
                            int attAttIndex = 0;
                            std::cin >> attAttIndex;

                            if (oppIndex == 0)
                            {
                                //station
                                player1.attackStation(&player2, attCardIndex, attAttIndex);
                            }
                            else if (oppIndex > 0)
                            {
                                // card
                                player1.attackPlayer(&player2, oppIndex - 1, attCardIndex, attAttIndex);
                            }
                            else
                            {
                                //errror
                                printTextToConsole("That attack index does not exist. Try again later.");
                            }
                        }
                        else
                        {
                            //the card you want to use dosent exist
                            printTextToConsole("The card at the index you entered does not exist! Try again.");
                        }
                    }
                    else
                    {
                        //that enemy card does not exist
                        printTextToConsole("That enemy card does not exist! Try again.");
                    }
                    std::cin.ignore();
                    system("pause");
                    askPlayerInput();
                }
                else
                {
                    //you have no cards to attack with?
                    printTextToConsole("You have no cards to use to attack the enemy. Try putting cards into play first!");
                    system("pause");
                    askPlayerInput();
                }
            }
            else if (userInput == "commands")
            {
                printGameHeader();
                printCommands();

                system("pause");
                askPlayerInput();
            }
            else if (userInput == "endturn")
            {
                printTextToConsole("Ending the player turn. . .");
                Sleep(1500);
                cGameState = AITurn;
                //call ai function
                startAITurn();
            }
            else if (userInput == "quit")
            {
                cGameState = GameOver;
                quitGame();
                break; 
            }
            else
            {
                // invalid input
                std::cout << "\n"; // prep line space between
                printTextToConsole("Invalid Input. Please enter a valid command.");
                std::cout << "\n > ";
                std::getline(std::cin, userInput);
            }
        }
        else if (cGameState == AITurn && !isAITurnInProgress)
        {
            isAITurnInProgress = true;
        }
    }
}

void printCommands() {

    std::cout << "\nCommands: \n" << std::endl;
    for (std::string x : commands)
    {
        std::cout << "  " << x << "\n";
    }
}

void askPlayerInput() {

    if (cGameState == UserTurn)
    {
        printTextToConsole("Please input your chosen command.");

        std::cout << "\n> "; // create line for input
        std::getline(std::cin, userInput); // wait for player input
    }
}

void quitGame() {

    printGameHeader();

    //ai won
    if (player1.stationHP <= 0)
    {
        cGameState = GameOver;
        printTextToConsole("The game is over. The AI has defeated " + player1.playerName);
    }
    //player won
    else if (player2.stationHP <= 0)
    {
        cGameState = GameOver;
        printTextToConsole("The game is over." + player1.playerName + " has won the game!");
    }
    else
    {
        // we quit
        printTextToConsole("Quitting the game. . . .");
        Sleep(1000);
    }
}

void startPlayerTurn() {

    printGameHeader();

    cGameState = UserTurn;
    player1.dealCards(2);
    player1.endTurn();

    askPlayerInput();

}

void startAITurn() {

    player2.endTurn();

    printGameHeader();
    printTextToConsole("It is now " + player2.playerName + "'s turn.");

    //deal ai cards
    player2.dealCards(2);

    Sleep(1500);

    // put cards into play until all actions are used
    // search through the cards and find the best ones to put into play. 
    player2.searchPlayCardsComputer();

    Sleep(1500);

    // attack player until all fuel is used
    player2.searchAttackCardsComputer(&player1);

    Sleep(1500);

    std::cout << "\nEnd Of Computer Turn. . . \n" << std::endl;
    Sleep(1000);

    // end turn and pass play to the player
    cGameState = UserTurn;

    system("pause");

    startPlayerTurn();

}

std::string setTopBottomLine(int sentLength) {

    std::string topBottomLine = "";

    for (int i = 0; i < sentLength; i++)
    {
        topBottomLine += "*";
    }
    return topBottomLine;

}

void printTextToConsole(std::string input) {

    printGameHeader();
    Sleep(100);
    std::cout << "\n" << setTopBottomLine(input.length() + 6) << "\n"
              << "*  " << input << "  *\n"
              << setTopBottomLine(input.length() + 6) << "\n";

}

