/**
* @file main.cpp
*
* @brief Implementation of the Hnefatafl game.
*
* This file contains the implementation of the Hnefatafl game, including setup, gameplay, and outcome
determination.
* It also provides a testing suite for various game functions.
*
* @author GLOVER Adam
* @date 07/11/2023
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
void playGame()
{
    // Display the game logo
    displayHnefataflLogo();
    BoardSize boardSize;
    Cell board[BOARD_SIZE_MAX][BOARD_SIZE_MAX];
    bool loaded = false;

    if (isSaveFileExists()) {
        cout << "A save file has been found, do you want to resume the game? Yes or No (Y,N)" << endl;
        char answer;
        cin.clear();
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            boardSize = loadBoard(board);
            clearConsole();
            displayBoard(board, boardSize);
            loaded = true;
        } else {
            clearConsole();
            deleteSaveFile();
        }
    }

    // Ask the user to choose the size of the game board
    if (!loaded) {
        bool validInput = chooseSizeBoard(boardSize);
        while (!validInput) {
            cout << "Invalid input, please try again" << endl;
            cin.clear();
            validInput = chooseSizeBoard(boardSize);
        }

        // Initialize the game board
        initializeBoard(board, boardSize);

        // Clear the console
        clearConsole();

        // Display the game board
        displayBoard(board, boardSize);
    }
    //Game loop
    bool isGameOver = false;
    PlayerRole playerRole = ATTACK;


    //Ask the user to play a move
    while (!isGameOver) {

        cout << "Player " << (playerRole == 0 ? "ATTACK" : "DEFENCE") << " turn" << endl;
        Position fromPosition = { -1,-1 };
        Position toPosition = { -1,-1 };
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
        } while (!isValidMovement(playerRole, board, fromPosition, toPosition)|| !isValidPosition(toPosition, boardSize));

        clearConsole();
        //Move the piece
        movePiece(board, fromPosition, toPosition);

        //Check if pieces are captured
        capturePieces(playerRole, board, boardSize, toPosition);

        //Display the board
        displayBoard(board, boardSize);

        //Check if swords left are 0
        if (isSwordLeft(board, boardSize) == 0) {
            isGameOver = true;
            cout << "There is no more sword, the defenders win !" << endl;
        }

        //Check if the king is escaped
        if (isKingEscaped(board, boardSize)) {
            isGameOver = true;
            cout << "The king is escaped, the attackers win !" << endl;
        }
        //Check if the king is captured
        if (isKingCaptured(board, boardSize)) {
            isGameOver = true;
            cout << "The king is captured, the defenders win !" << endl;
        }
        //Check if only Sword are left
        if (!isSwordLeft(board, boardSize)) {
            isGameOver = true;
            cout << "There is no more sword, the defenders win !" << endl;
        }


        //Change the player
        (playerRole == ATTACK) ? playerRole = DEFENSE : playerRole = ATTACK;

        //Save board to a file in case of crash, to be able to resume the game
        saveBoard(board, boardSize);

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
    else {
        cout << "Thanks for playing!" << endl;
    }



}

/**
* @brief Launches the testing suite.
*
* This function runs a suite of tests to validate various game functions.
*/
void launchTests(){
    cout << endl << "********* Start testing *********" << endl << endl;
    test_isValidMovement();
    //test_getPositionFromInput();
    //test_isKingCaptured();
    //test_isKingCapturedV2();
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
    //launchTests();
    playGame();
    return 0;
}
