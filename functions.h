/**
 * @file fonctions.h
 *
 * @brief Declarations of functions for the Hnefatafl game.
 *
 * This file contains the declarations of various functions used in the Hnefatafl game, including
 * board initialization, display, piece movement, capturing, and game state checks.
 *
 * @author JMB - IUT Informatique La Rochelle
 * @date 03/10/2023
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "typeDef.h"

/**
 * @brief Clears the console screen based on the operating system.
 *
 * This function clears the console screen by executing system commands specific to the operating system.
 * On Windows, it uses the "cls" command, and on Linux and macOS, it uses the "clear" command.
 */
void clearConsole();

/**
 * @brief Displays the game logo.
 *
 * This function prints the game logo to the console, which includes ASCII art text and additional information about the game.
 */
void displayHnefataflLogo();

/**
 * @brief Ask the user to choose the size of the game board.
 *
 * This function asks the user to choose the size of the game board
 * (either 11x11 or 13x13) and returns true with the selected size
 * if the input is valid. It returns false if the input is invalid
 * or not an integer.
 *
 * @param aBoardSize - Reference to the BoardSize variable to store the chosen board size.
 * @return True if the input is valid and a size is chosen, false otherwise.
 */
bool chooseSizeBoard(BoardSize& aBoardSize);


/**
 * @brief Display the main menu.
 *
 * This function displays the main menu of the game and asks the user to choose an option.
 *
 * @return The user's choice as an integer.
 */
int displayMenu();

/**
 * @brief Creates a new game
 *
 * This function creates a new game by asking the user to choose the size of the board and if they want to play against an AI.
 *
 * @param aBoardSize - Reference to the BoardSize variable to store the chosen board size.
 * @param aBoard - Reference to the 2D array representing the game board.
 * @param ai - Reference to the boolean variable to store if the game is against an AI or not.
 */
void newGame(BoardSize &aBoardSize, Cell aBoard[][BOARD_SIZE_MAX], bool &ai);


/**
 * @brief Display the rules of the game.
 *
 * This function displays the rules of the game.
 */
void displayRules();


bool chooseSizeBoard(BoardSize& aBoardSize);

/**
 * @brief Initialize the game board based on its size.
 *
 * This function initializes the game board with the specified size. It places
 * the fortresses, king, castle, shields, and swords on the board based on the
 * chosen board size. The board is represented as a 2D array of cells.
 *
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 */
void initializeBoard(Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize);

/**
 * @brief Display the game board with pieces.
 *
 * This function displays the game board with the positions of pieces such as shields,
 * swords, the king, castle, and exits. It also labels rows with letters and columns
 * with numbers for easier player reference.
 *
 * @param aBoard A 2D array representing the game board.
 * @param aBoardSize The size of the game board (either LITTLE or BIG).
 */
void displayBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize);

/**
 * @brief Retrieve a position entered by the user.
 *
 * This function reads user input, validates it as a position in the format of a letter
 * followed by a number (e.g., "A1" or "B2"). If the input is valid, it returns the
 * corresponding Position structure; otherwise, it returns {-1, -1} to indicate an
 * invalid position.
 *
 * @return The Position structure representing the user's input position, or {-1, -1} if invalid.
 */
Position getPositionFromInput();

/**
 * @brief Check if a position is valid within the given board size.
 *
 * This function verifies whether a provided Position structure is valid within the
 * dimensions of the game board, as specified by the given BoardSize. It returns true
 * if the position is valid, meaning it falls within the board's bounds, and false
 * otherwise.
 *
 * @param aPos The Position structure to check for validity.
 * @param aBoardSize The size of the game board.
 * @return True if the position is valid, false otherwise.
 */
bool isValidPosition(const Position& aPos, const BoardSize& aBoardSize);

/**
 * @brief Check if a specific cell on the game board is empty.
 *
 * This function determines whether a particular cell on the game board, as specified
 * by the given Position, is empty. A cell is considered empty if it does not contain
 * any game pieces.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aPos The Position of the cell to check for emptiness.
 * @return True if the cell is empty, false if it contains a game piece.
 */
bool isEmptyCell(const Cell aBoard[][BOARD_SIZE_MAX], const Position& aPos);

/**
 * @brief Check if a selected move is valid for the current player.
 *
 * This function verifies if a selected move, from the starting position to the ending position,
 * is valid for the current player. It checks various conditions such as whether the starting position
 * contains a piece of the active player, if the move is along the same row or column, and if there are any obstacles
 * in the path.
 *
 * @param aPlayer The role of the current player (ATTACK or DEFENSE).
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aStartPos The starting position of the move.
 * @param aEndPos The ending position of the move.
 * @return True if the move is valid, false otherwise.
 */
bool isValidMovement(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos);

/**
 * @brief Move a game piece on the game board.
 *
 * This function moves a game piece from the starting position to the ending position
 * on the game board. It updates the ending position to contain the piece and clears
 * the starting position.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aStartPos The starting position of the move.
 * @param aEndPos The ending position of the move.
 */
void movePiece(Cell aBoard[][BOARD_SIZE_MAX], const Position& aStartPos, const Position& aEndPos);

/**
 * @brief Remove captured pieces from the game board.
 *
 * This function checks for captured pieces in the four adjacent directions
 * to the ending position and removes them based on the game rules.
 *
 * @param aPlayer The current player's role (ATTACK or DEFENSE).
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aEndPos The ending position of the move.
 */
void capturePieces(const PlayerRole& aPlayer, Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aEndPos);

/**
 * @brief Check if there are any attackers (swords) left on the game board.
 *
 * This function iterates through the game board to determine if there are any
 * attacker (sword) pieces remaining.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if there are attackers left, false otherwise.
 */
bool isSwordLeft(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize);

/**
 * @brief Get the position of the king on the game board.
 *
 * This function iterates through the game board to find and return the position
 * of the king piece. If the king is not found, it returns the default position {-1, -1}.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return The position of the king or {-1, -1} if the king is not found.
 */
Position getKingPosition(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize);

/**
 * @brief Check if the king has escaped to a fortress.
 *
 * This function first obtains the position of the king using the getKingPosition function.
 * It then checks if the cell at the king's position is of type FORTRESS, indicating that
 * the king has successfully escaped to a fortress.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if the king has escaped to a fortress, false otherwise.
 */
bool isKingEscaped(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize);

/**
 * @brief Check if the king is captured by 4 elements (attackers, border, or fortress).
 *
 * This function first obtains the position of the king using the getKingPosition function.
 * It then checks the four neighboring positions around the king to determine if any of them
 * contain enemy pieces (attackers), border cells, fortress cells, or castle cells. If all
 * four neighboring positions meet one of these conditions, the king is considered captured.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @return True if the king is captured by 4 elements, false otherwise.
 */
bool isKingCaptured(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) ;

/**
 * @brief Recursively check if the king is blocked.
 *
 * This function recursively checks if the king is blocked from all sides. It starts
 * with the actual king's position and explores neighboring cells in all directions.
 * If the king can move to any neighboring cell, it's not considered blocked.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aKingPos The position of the king (defaults to {-1, -1} to use the actual king's position).
 * @return True if the king is blocked from all sides, false if it can move to at least one neighboring cell.
 */
bool isKingCapturedV2(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, Position aKingPos = {-1, -1});


/**
 * @brief Save the board to a file.
 *
 * This function saves the board to a file in case of crash, to be able to resume the game.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aPlayerRole The role of the player.
 */
void saveBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const PlayerRole& aPlayerRole, const bool& isAi);


/**
 * @brief Load the board from a file.
 *
 * This function loads the board from a file in case of crash, to be able to resume the game.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the board.
 * @param aPlayerRole The role of the player.
 *
 */
void loadBoard(Cell aBoard[][BOARD_SIZE_MAX], BoardSize& aBoardSize, PlayerRole& aPlayerRole, bool& isAi);


/**
 * @brief Check if a save file exists.
 *
 * This function checks if a save file exists.
 *
 * @return True if the save file exists, false otherwise.
 */
bool isSaveFileExists();



/**
 * @brief Check if a statistic file exists.
 *
 * This function checks if a statistic file exists.
 *
 * @return True if the statistic file exists, false otherwise.
 */
bool isStatisticFileExists();



/**
 * @brief Delete the save file.
 *
 * This function deletes the save file.
 *
 */
void deleteSaveFile();


/**
 * @brief Display the board with the chosen piece.
 *
 * This function displays the board with the chosen piece.
 *
 * @param aBoard The game board represented as a 2D array of Cell structures.
 * @param aBoardSize The size of the game board.
 * @param aPos The position of the chosen piece.
 */
void displayChosenPieceBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aPos);


/**
 *
 * @brief Decides the best move for the AI based on a weighted check.
 *
 * If it is the defense's turn, the AI will try to move the king to a fortress if its a better option.
 * The weight is calculated by the number of pieces that can be captured by the move.
 *
 * @param aBoard
 * @param aBoardSize
 * @param aPlayerRole
 * @return
 */
Position chooseBestAiMove(Cell aBoard[][BOARD_SIZE_MAX], BoardSize& aBoardSize, PlayerRole& aPlayerRole);


/**
 *
 * @brief Calculates the score of a move based on the number of pieces that can be captured and other factors.
 *
 * @param aBoard
 * @param aBoardSize
 * @param aPlayerRole
 * @return
 */
int calculateScore(const Cell aBoard[][BOARD_SIZE_MAX], const int aPreviousAmountOfEmpty, const BoardSize& aBoardSize, const PlayerRole& aPlayerRole);



/**
 *
 * @brief Create a statistic file.
 *
 */
void createStatisticFile();



/**
 *
 * @brief read the statistics to a file.
 *
 * @param aAmountOfGames The amount of games played.
 * @param aAmountOfDefenceWins The amount of wins for the defense.
 * @param aAmountOfAttackWins The amount of wins for the attack.
 * @param aAmountOfAiWins The amount of wins for the AI.
 */
void readStatisticFile(int& aAmountOfGames, int&aAmountOfDefenceWins, int& aAmountOfAttackWins, int& aAmountOfAiWins);



/**
 *
 * @brief write the statistics to a file.
 *
 * @param aAmountOfGames The amount of games played.
 * @param aAmountOfDefenceWins The amount of wins for the defense.
 * @param aAmountOfAttackWins The amount of wins for the attack.
 * @param aAmountOfAiWins The amount of wins for the AI.
 */
void writeStatisticFile(int aAmountOfGames, int aAmountOfDefenceWins, int aAmountOfAttackWins, int aAmountOfAiWins);


/**
 *
 * @brief Display the statistics.
 *
 * @param amountOfAiWins The amount of wins for the AI.
 * @param amountOfAttackWins The amount of wins for the attack.
 * @param amountOfDefenceWins The amount of wins for the defense.
 * @param amountOfPlayed The amount of games played.
 */
void displayStatistics(int amountOfPlayed, int amountOfAttackWins, int amountOfDefenceWins, int amountOfAiWins);


/**
 *
 * @brief Display the victory animation.
 *
 * @param aPlayerRole The role of the player.
 */
void displayThanksForPlayingAnimation();


#endif // FUNCTIONS_H
