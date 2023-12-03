/**
* @file main.cpp
*
* @brief Implementation of the Hnefatafl game.
*
* This file contains the implementation of the Hnefatafl game, including setup, gameplay, and outcome
* determination.
* It also provides a testing suite for various game functions.
*
* @author GLOVER Adam
* @date 07/11/2023 (DD/MM/YYYY)
*
* version 1.0
* released the 03/12/2023
*
* bug list :
* - isKingCapturedV2() doesn't work fully
* - Save location isn't the best for any other OS than Windows
*/
#include <iostream>
#include "functions.h"
#include "typeDef.h"
#include "tests.h"

using namespace std;


/**
* @brief Function to play the Hnefatafl game.
*
* This function orchestrates the Hnefatafl game, including setup, gameplay, and outcome determination.
*/
void playGame() {
    //Initialize variables
    BoardSize boardSize;
    Cell board[BOARD_SIZE_MAX][BOARD_SIZE_MAX];
    PlayerRole playerRole = ATTACK;
    bool ai = false;
    int amountOfPlayed = 0;
    int amountOfDefenceWins = 0;
    int amountOfAttackWins = 0;
    int amountOfAiWins = 0;

    // Display the game logo
    clearConsole();
    displayHnefataflLogo();

    //Create the statistics file if it doesn't exist
    if (!isStatisticFileExists()) {
        createStatisticFile();
    }
    readStatisticFile(amountOfPlayed, amountOfAttackWins, amountOfDefenceWins, amountOfAiWins);

    //Display the statistics
    displayStatistics(amountOfPlayed, amountOfAttackWins, amountOfDefenceWins, amountOfAiWins);

    //Display the menu
    cin.clear();
    cin.ignore(256, '\n');
    clearConsole();
    displayHnefataflLogo();
    int choice = displayMenu();

    //Change depending on the choice
    clearConsole();
    displayHnefataflLogo();
    switch (choice) {
        case 1: //New game
            newGame(boardSize,board, ai);
            writeStatisticFile(amountOfPlayed+1, amountOfDefenceWins, amountOfAttackWins, amountOfAiWins);
            break;
        case 2: //Load game
            if (isSaveFileExists()) {
                loadBoard(board, boardSize, playerRole, ai);
                displayBoard(board, boardSize);
            }
            else {
                cout << "No save file found, starting a new game" << endl;
                newGame(boardSize, board, ai);
                writeStatisticFile(amountOfPlayed+1, amountOfDefenceWins, amountOfAttackWins, amountOfAiWins);
            }
            break;
        case 3: //Rules
            displayRules();
            playGame();
            break;
        case 4: //Quit
            displayThanksForPlayingAnimation();
            return;
        default: //Invalid choice
            cout << "Invalid choice, please try again" << endl;
            playGame();
            break;

    }


    //Game loop
    bool isGameOver = false;

    while (!isGameOver) {

        //Declare variables
        cout << "Player " << (playerRole == 0 ? "ATTACK" : "DEFENCE") << " turn" << endl;
        Position fromPosition = { -1,-1 };
        Position toPosition = { -1,-1 };

        //Ask the user to choose a piece to move
        do {
            fromPosition = getPositionFromInput();
            if (!isEmptyCell(board,fromPosition)) {
                clearConsole();
                displayChosenPieceBoard(board, boardSize, fromPosition);
                cin.clear();
                toPosition = getPositionFromInput();
            }
            clearConsole();
            displayBoard(board, boardSize);
        } while (!isValidMovement(playerRole, board, fromPosition, toPosition)|| !isValidPosition(toPosition, boardSize)); //Check if the movement is valid

        clearConsole();
        //Move the piece
        movePiece(board, fromPosition, toPosition);

        //Check if pieces are captured
        capturePieces(playerRole, board, boardSize, toPosition);

        //Display the board
        displayBoard(board, boardSize);

        saveBoard(board, boardSize, playerRole, ai);

        //Check if the user is playing against an AI
        if (ai) {
            //Change the player
            (playerRole == ATTACK) ? playerRole = DEFENSE : playerRole = ATTACK;
            clearConsole();

            //Ai choose a move
            Position chosenPos = chooseBestAiMove(board, boardSize, playerRole);
            capturePieces(playerRole, board, boardSize, chosenPos);
            displayBoard(board, boardSize);
            cout << "AI played his turn" << endl;

            //Change the player back to the human
            (playerRole == ATTACK) ? playerRole = DEFENSE : playerRole = ATTACK;
        }

        //Check if swords left are 0
        if (isSwordLeft(board, boardSize) == 0) {
            isGameOver = true;
            cout << "There is no more sword, the defenders win !" << endl;
            writeStatisticFile(amountOfPlayed, amountOfDefenceWins+1, amountOfAttackWins, amountOfAiWins);
        }

        //Check if the king is escaped
        if (isKingEscaped(board, boardSize)) {
            isGameOver = true;
            cout << "The king is escaped, the attackers win !" << endl;
            writeStatisticFile(amountOfPlayed, amountOfDefenceWins, amountOfAttackWins+1, (ai ? amountOfAiWins+1 : amountOfAiWins));
        }
        //Check if the king is captured
        if (isKingCaptured(board, boardSize)) {
            isGameOver = true;
            cout << "The king is captured, the defenders win !" << endl;
            writeStatisticFile(amountOfPlayed, amountOfDefenceWins+1, amountOfAttackWins, amountOfAiWins);
        }
        //Check if only Sword are left
        if (!isSwordLeft(board, boardSize)) {
            isGameOver = true;
            cout << "There is no more sword, the defenders win !" << endl;
            writeStatisticFile(amountOfPlayed, amountOfDefenceWins+1, amountOfAttackWins, amountOfAiWins);
        }


        if (!ai) {
            //Change the player if the user is not playing against an AI
            (playerRole == ATTACK) ? playerRole = DEFENSE : playerRole = ATTACK;
        }

        //Save board to a file in case of crash, to be able to resume the game
        saveBoard(board, boardSize, playerRole, ai);

    }

    //delete the save file
    deleteSaveFile();

    //Ask the user if he wants to play again
    cout << "Would you like to play again? Yes or No (Y,N)" << endl;
    char answer;
    cin.clear();
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        playGame();
    }
    else { //Display the thanks for playing animation
        displayThanksForPlayingAnimation();
    }
}

/**
* @brief Launches the testing suite.
*
* This function runs a suite of tests to validate various game functions.
* It counts the number of tests passed and failed and displays the results.
*/
void launchTests(){
    cout << endl << "********* Start testing *********" << endl << endl;
    int pass = 0;
    int failed = 0;
    test_chooseSizeBoard(pass, failed);
    test_initializeBoard(pass, failed);
    test_getPositionFromInput(pass, failed);
    test_isValidPosition(pass, failed);
    test_isEmptyCell(pass, failed);
    test_isValidMovement(pass, failed);
    test_movePiece(pass, failed);
    test_capturePieces(pass, failed);
    test_isSwordLeft(pass, failed);
    test_getKingPosition(pass, failed);
    test_isKingEscaped(pass, failed);
    test_isKingCaptured(pass, failed);
    test_isKingCapturedV2(pass, failed);

    cout << endl << "********** Test results **********" << endl << endl;
    cout << "Passed tests: " << pass << endl;
    cout << "Failed tests: " << failed << endl;

    cout << endl << "********** End testing **********" << endl << endl;
}


/**
* @brief Main function of the game.
*
* The main function serves as the entry point for the Hnefatafl game. It can be used to start the game or run tests.
*
* @return 0 for successful execution.
*/
int main() {
    launchTests();
    //playGame();
    return 0;
}
