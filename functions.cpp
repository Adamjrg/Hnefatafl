/**
 * @file functions.cpp
 *
 * @brief Implementation of the functions the game Hnefatafl.
 *
 * This file contains the implementation of functions used to verify and validate
 * the functionality of the functions implemented in 'fonctions.cpp.'
 * These test functions are designed to thoroughly test various aspects of the code
 * in 'fonctions.cpp' to ensure that it performs as expected.
 * They cover a range of scenarios and edge cases, helping to identify and resolve
 * any potential issues or bugs in the codebase.
 * The tests are conducted on different board sizes and configurations,
 * providing comprehensive coverage to guarantee the reliability and correctness
 * of the functions in 'fonctions.cpp.'
 * Overall, 'test.cpp' plays a crucial role in maintaining code quality and robustness by confirming
 * that the functions it tests meet their intended specifications."
 *
 * @author GLOVER Adam
 * @date 07/11/2023
 */

#include <iostream>
#include <fstream>

#include "typeDef.h"
#include "functions.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

const string RESET = "\e[0m";
const string BOLD_RED  = "\e[1;31m";
const string HIGHLIGHT  = "\e[7m";
const string BLUE_BOLD = "\x1b[34;1m";

const string BLACK_CHAR = "\u25CB";
const string WHITE_CHAR = "\u25CF";
const string KING_CHAR = "\u25CA";


/**
 * @brief Clears the console depending on the operating system
 *
 */
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#elif __APPLE__
    system("clear");
#endif
}

void universalSleep(int milliseconds)
{
#ifdef _WIN32
    // Windows
    Sleep(milliseconds);
#else
    // Unix-like systems
    usleep(milliseconds * 1000); // usleep uses microseconds, so multiply by 1000 to convert to milliseconds
#endif
}


void displayHnefataflLogo(){
    cout << R"(
     _   _             __      _         __ _
    | | | |           / _|    | |       / _| |
    | |_| |_ __   ___| |_ __ _| |_ __ _| |_| |
    |  _  | '_  \/ _ \  _/ _` | __/ _` |  _| |
    | | | | | | |  __/ || (_| | || (_| | | | |
    \_| |_/_| |_|\___|_| \__,_|\__\__,_|_| |_|)" << endl;
    cout << endl;
    cout << "Welcome to "<< BLUE_BOLD <<"Hnefatafl" << RESET << ", coded by " << BLUE_BOLD <<  "GLOVER Adam D2" << RESET << endl;
}

int displayMenu() {
    cout << R"(
---------------------------------------------⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀
    ⠀⢠⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⡄⠀
    ⠀⣿⣿⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⠀
    ⠀⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⠀
    ⠀⢹⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⢠⣴⣦⡄⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⡏⠀      1. New Game
    ⠀⠀⢿⣿⣿⡿⠋⣠⡶⠀⣠⣴⡆⠠⢤⡤⠄⢰⣦⣄⠀⢶⣄⠙⢿⣿⣿⡿⠀⠀      2. Load Game
    ⠀⠀⠈⢿⠋⣠⡾⠋⣠⣾⣿⣿⡇⢰⣤⣤⡆⢸⣿⣿⣷⣄⠙⢷⣄⠙⡿⠁⠀⠀      3. Rules
    ⠀⠀⠀⠀⣴⠏⢠⣾⣿⣿⣿⣿⡇⠸⠿⠿⠇⢸⣿⣿⣿⣿⣷⡄⠹⣦⠀⠀⠀⠀      4. Quit
    ⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⡇⠀⠒⠒⠀⢸⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⡇⢸⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀
    ⠀⠀⠀⠀⠛⠛⠛⠛⠛⠛⠛⠛⠃⠈⣉⣉⠁⠘⠛⠛⠛⠛⠛⠛⠛⠛⠀⠀⠀⠀
    ⠀⠀⠀⠀⢿⠀⠾⣿⠷⠀⣿⣿⡇⢀⣉⣉⡀⢸⣿⣿⠀⠾⣿⠷⠀⡿⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
---------------------------------------------⠀⠀⠀⠀⠀
Enter your choice:)" << endl;
    int choice = 0;
    cin.clear();
    cin >> choice;
    return choice;
}

void newGame(BoardSize &aBoardSize, Cell aBoard[][BOARD_SIZE_MAX], bool &ai) {
    cout << "Do you want to play against an AI? Yes or No (Y,N)" << endl;
    char answerAI;
    cin.clear();
    cin >> answerAI;
    if (answerAI == 'Y' || answerAI == 'y') {
        ai = true;
    }
    else {
        ai = false;
    }

    bool validInput = chooseSizeBoard(aBoardSize);
    while (!validInput) {
        cout << "Invalid input, please try again" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        validInput = chooseSizeBoard(aBoardSize);
    }

    // Initialize the game board
    initializeBoard(aBoard, aBoardSize);

    // Clear the console
    clearConsole();

    // Display the game board
    displayBoard(aBoard, aBoardSize);
}

void displayRules() {
    clearConsole();
    cout << BOLD_RED << "Setup:" << RESET << endl;
    cout << "The game is played on a square board with a grid of 11x11 or 13x13 squares." << endl;
    cout << "The central square is the throne, and the four corner squares are the escape squares." << endl;
    cout
            << "The defenders, represented by white pieces, set up in a cross-shaped formation around the king on the central square."
            << endl;
    cout << "The attackers, represented by black pieces, surround the defenders on all sides." << endl;
    cout << endl;
    cout << BOLD_RED << "Movement:" << RESET << endl;
    cout
            << "The king moves like the other pieces, vertically or horizontally (not diagonally)."
            << endl;
    cout
            << "All other pieces, both attackers and defenders, move like chess rooks (horizontally or vertically) and capture by surrounding an opponent's piece on two opposite sides (horizontally or vertically)."
            << endl;
    cout << endl;
    cout << BOLD_RED << "Objective:" << RESET << endl;
    cout << "The attackers win by capturing the defender's king, surrounding it on all four sides." << endl;
    cout
            << "The defenders win by moving their king to one of the corner squares (escape squares) or by blocking the attackers' movement until they can't make a legal move."
            << endl;
    cout << endl;
    cout << BOLD_RED << "Capture Rules:" << RESET << endl;
    cout
            << "To capture an opponent's piece, you must sandwich it between two of your own pieces along a horizontal or vertical line."
            << endl;
    cout << "The king can be used to make captures just like other pieces." << endl;
    cout << endl;
    cout << BOLD_RED << "Turns and Gameplay:" << RESET << endl;
    cout << "Players take turns, starting with the attackers." << endl;
    cout << "The player must move one of their pieces on their turn." << endl;
    cout << "A player can't move through or onto a square occupied by their own piece." << endl;
    cout << endl;
    cout << BOLD_RED << "Winning:" << RESET << endl;
    cout << "If the attackers capture the king, they win." << endl;
    cout
            << "If the defenders move their king to one of the corner squares or create a situation where the attackers can't make a legal move, they win."
            << endl;
    cout << endl;
    cout << BOLD_RED << "Stalemate:" << RESET << endl;
    cout
            << "If a position repeats three times without any progress (same pieces in the same positions), the game is a draw."
            << endl;
    cout << endl;
    cout
            << "These are the fundamental rules of Hnefatafl. The game combines strategy and tactics, and the balance between the attackers and defenders makes for an intriguing and challenging board game."
            << endl;
    cout << "Press Enter to continue..." << endl;
    cin.clear();
    cin.ignore(255, '\n');
    getchar();
}


bool chooseSizeBoard(BoardSize &aBoardSize){
    int choice = 0;
    cout << "Would you like to play on a 11x11 or 13x13 grid? (11,13)" << endl;
    cin >> choice;
    switch(choice){
        //Choose size LITTLE (11)
        case 11:
            aBoardSize = LITTLE;
            return true;

            //Choose size BIG (13)
        case 13:
            aBoardSize = BIG;
            return true;

            //Invalid input
        default:
            return false;
            break;
    }
}

void initializeBoard(Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    for (short int i = 0; i < aBoardSize;i++)
    {
        for (short int j = 0; j < aBoardSize;j++) {
            aBoard[i][j].itsCellType= NORMAL;
            aBoard[i][j].itsPieceType= NONE;
        }
    }

    //Set black peices
    for (short int i = (aBoardSize/2)-2; i <= (aBoardSize/2)+2;i++)
    {
        //Top and bottom pieces
        aBoard[i][0].itsPieceType= SWORD;
        aBoard[i][aBoardSize-1].itsPieceType= SWORD;

        //Left and right side pieces
        aBoard[0][i].itsPieceType= SWORD;
        aBoard[aBoardSize-1][i].itsPieceType= SWORD;
    }
    //Top and bottom center pieces
    aBoard[aBoardSize/2][1].itsPieceType = SWORD;
    aBoard[aBoardSize/2][aBoardSize-2].itsPieceType = SWORD;

    //Left and right middle pieces
    aBoard[1][aBoardSize/2].itsPieceType = SWORD;
    aBoard[aBoardSize-2][aBoardSize/2].itsPieceType = SWORD;


    //Set white pieces for the big board
    if (aBoardSize == BIG) {
        for (short int i =(aBoardSize/2)-3; i <= (aBoardSize/2)+3; i++) {
            if (i != aBoardSize/2) {
                aBoard[i][aBoardSize/2].itsPieceType = SHIELD;
                aBoard[aBoardSize/2][i].itsPieceType = SHIELD;
            }
        }
    }//Set white pieces for the small board
    else if (aBoardSize == LITTLE)
    {
        int offset = 0;
        for (short int i =(aBoardSize/2)-2; i <= (aBoardSize/2)+2; i++)
        {
            for (short int j =(aBoardSize/2)-offset; j <= (aBoardSize/2)+offset; j++) {
                aBoard[i][j].itsPieceType = SHIELD;
            }

            if (i >= aBoardSize/2) {
                offset-=1;
            } else {
                offset+=1;
            }
        }
    }


    //Set king
    aBoard[aBoardSize/2][aBoardSize/2].itsPieceType = KING;

    //Set Fortress tile
    aBoard[aBoardSize/2][aBoardSize/2].itsCellType = CASTLE;

    //Set Castle tiles
    aBoard[0][0].itsCellType = FORTRESS;
    aBoard[0][aBoardSize-1].itsCellType = FORTRESS;
    aBoard[aBoardSize-1][0].itsCellType = FORTRESS;
    aBoard[aBoardSize-1][aBoardSize-1].itsCellType = FORTRESS;
}

void displayBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    cout << "    King: " << KING_CHAR << "      Shield:" << WHITE_CHAR << "      Sword:" << BLACK_CHAR << "     Fortress:O" << "     Castle:X"  <<endl;
    cout << " ";
    for(short int i = 1; i <= aBoardSize; i++) {
        cout << (i > 10 ? "    " : "     ") <<BLUE_BOLD << i << RESET;
    }
    cout << endl;


    char start = 'A';
    for(short int i = 1; i <= aBoardSize; i++) {
        cout << "   ";
        for(short int j = 1; j < aBoardSize+1; j++) {
            cout << "+-----";
        }
        cout << "+";
        cout << endl;
        cout <<BLUE_BOLD<< char(start-1+i) << RESET;
        for(short int j = 0; j < aBoardSize; j++) {
            if (aBoard[i-1][j].itsPieceType == NONE && aBoard[i-1][j].itsCellType == NORMAL) {
                cout << "  |   ";
            }
            else if (aBoard[i-1][j].itsPieceType == SWORD) {
                cout << "  |  "<< BLACK_CHAR;
            }
            else if (aBoard[i-1][j].itsPieceType == SHIELD){
                cout << "  |  "<< WHITE_CHAR;
            }
            else if (aBoard[i-1][j].itsPieceType == KING){
                cout << "  |  "<< KING_CHAR;
            }
            else if (aBoard[i-1][j].itsCellType == CASTLE){
                cout << "  |  "<< "X";
            }
            else if (aBoard[i-1][j].itsCellType == FORTRESS){
                cout << "  |  "<< "O";
            }
        }
        cout << "  |";
        cout << endl;
    }
    cout << "   ";
    for(short int j = 1; j < aBoardSize+1; j++) {
        cout << "+-----";
    }
    cout << "+";
    cout << endl;
}

Position getPositionFromInput() {
    Position pos;
    char row;
    int col;
    cout << "Enter the position (e.g. A1): ";
    cin >> row >> col;
    string extra;
    cin.clear();
    getline(cin, extra);

    row = toupper(row);
    //Check if they are in the correct order
    if (isdigit(row) && isalpha(col)) {
        cout << BOLD_RED << "The row and column are in the wrong order." << RESET << endl;
        pos.itsCol = -1;
        pos.itsRow = -1;
        return pos;
    }

    //Check if empty
    if (row == '\0' || col == '\0') {
        cout << BOLD_RED << "The row and column are empty." << RESET << endl;
        pos.itsCol = -1;
        pos.itsRow = -1;
        return pos;
    }

    if (extra != "") {
        cout << BOLD_RED << "Incorrect format" << RESET << endl;
        pos.itsCol = -1;
        pos.itsRow = -1;
        return pos;
    }

    //Check if the row is valid
    if (row < 'A' || row > 'Z') {
        cout << BOLD_RED << "The row is not valid." << RESET << endl;
        pos.itsCol = -1;
        pos.itsRow = -1;
        return pos;
    }

    pos.itsCol = col-1;
    pos.itsRow = row-65;
    return pos;
}

bool isValidPosition(const Position& aPos, const BoardSize& aBoardSize) {
    if (aPos.itsRow >= 0 && aPos.itsRow < aBoardSize && aPos.itsCol >= 0 && aPos.itsCol < aBoardSize) {
        return true;
    }
    return false;
}

bool isEmptyCell(const Cell aBoard[][BOARD_SIZE_MAX], const Position& aPos) {
    if (aBoard[aPos.itsRow][aPos.itsCol].itsPieceType == NONE) {
        return true;
    }
    return false;
}

bool isValidMovement(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos) {
    //Check if the start position is empty
    if (isEmptyCell(aBoard, aStartPos)) {
        cout << BOLD_RED << "The starting position is empty." << RESET << endl;
        return false;
    }

    //Check if the piece belongs to the player
    if (aPlayer == ATTACK && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != SWORD) {
        cout << BOLD_RED << "The piece does not belong to the attacker." << RESET << endl;
        return false;
    }
    else if (aPlayer == DEFENSE && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != SHIELD && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        cout << BOLD_RED << "The piece does not belong to the defender." << RESET << endl;
        return false;
    }

    //Check if the end position is empty
    if (!isEmptyCell(aBoard, aEndPos)) {
        cout << BOLD_RED << "The ending position is not empty." << RESET << endl;
        return false;
    }

    //Check if the move is along the same row or column
    if (aStartPos.itsRow != aEndPos.itsRow && aStartPos.itsCol != aEndPos.itsCol) {
        cout << BOLD_RED << "The move must be along the same row or column." << RESET << endl;
        return false;
    }

    //Check if only the king can go on the fortress
    if (aBoard[aEndPos.itsRow][aEndPos.itsCol].itsCellType == FORTRESS && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        cout << BOLD_RED << "Only the king can go on the fortress." << RESET << endl;
        return false;
    }

    //Check if only the king can pass on the castle
    if (aBoard[aEndPos.itsRow][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        cout << BOLD_RED << "Only the king can pass above and on the castle." << RESET << endl;
        return false;
    }

    //Check if there is the castle in the path
    if (aStartPos.itsRow == aEndPos.itsRow && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        //Check left
        if (aStartPos.itsCol > aEndPos.itsCol) {
            for (short int i = aStartPos.itsCol-1; i > aEndPos.itsCol; i--) {
                if (aBoard[aStartPos.itsRow][i].itsCellType == CASTLE) {
                    cout << BOLD_RED << "The castle is in the path." << RESET << endl;
                    return false;
                }
            }
        }
            //Check right
        else {
            for (short int i = aStartPos.itsCol+1; i < aEndPos.itsCol; i++) {
                if (aBoard[aStartPos.itsRow][i].itsCellType == CASTLE) {
                    cout << BOLD_RED << "The castle is in the path." << RESET << endl;
                    return false;
                }
            }
        }
    }
    else if (aStartPos.itsCol == aEndPos.itsCol && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        //Check up
        if (aStartPos.itsRow > aEndPos.itsRow) {
            for (short int i = aStartPos.itsRow-1; i > aEndPos.itsRow; i--) {
                if (aBoard[i][aStartPos.itsCol].itsCellType == CASTLE) {
                    cout << BOLD_RED << "The castle is in the path." << RESET << endl;
                    return false;
                }
            }
        }
            //Check down
        else {
            for (short int i = aStartPos.itsRow+1; i < aEndPos.itsRow; i++) {
                if (aBoard[i][aStartPos.itsCol].itsCellType == CASTLE) {
                    cout << BOLD_RED << "The castle is in the path." << RESET << endl;
                    return false;
                }
            }
        }
    }


    //Check if there is a piece in the path
    if (aStartPos.itsRow == aEndPos.itsRow) {
        //Check left
        if (aStartPos.itsCol > aEndPos.itsCol) {
            for (short int i = aStartPos.itsCol-1; i > aEndPos.itsCol; i--) {
                if (!isEmptyCell(aBoard, {aStartPos.itsRow, i})) {
                    cout << BOLD_RED << "There is a piece in the path." << RESET << endl;
                    return false;
                }
            }
        }
            //Check right
        else {
            for (short int i = aStartPos.itsCol+1; i < aEndPos.itsCol; i++) {
                if (!isEmptyCell(aBoard, {aStartPos.itsRow, i})) {
                    cout << BOLD_RED << "There is a piece in the path." << RESET << endl;
                    return false;
                }
            }
        }
    }
    else if (aStartPos.itsCol == aEndPos.itsCol) {
        //Check up
        if (aStartPos.itsRow > aEndPos.itsRow) {
            for (short int i = aStartPos.itsRow-1; i > aEndPos.itsRow; i--) {
                if (!isEmptyCell(aBoard, {i, aStartPos.itsCol})) {
                    cout << BOLD_RED << "There is a piece in the path." << RESET << endl;
                    return false;
                }
            }
        }
            //Check down
        else {
            for (short int i = aStartPos.itsRow+1; i < aEndPos.itsRow; i++) {
                if (!isEmptyCell(aBoard, {i, aStartPos.itsCol})) {
                    cout << BOLD_RED << "There is a piece in the path." << RESET << endl;
                    return false;
                }
            }
        }
    }


    return true;
}

void movePiece(Cell aBoard[][BOARD_SIZE_MAX], const Position& aStartPos, const Position& aEndPos) {
    aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType = aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType;
    aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType = NONE;
}

void capturePieces(const PlayerRole& aPlayer, Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aEndPos) {
    const PieceType enemyPiece = (aPlayer == ATTACK) ? SHIELD : SWORD;
    const PieceType friendlyPiece = (aPlayer == ATTACK) ? SWORD : SHIELD;
    const bool isDefence = (aPlayer == DEFENSE);

    // Up
    if (aEndPos.itsRow - 2 >= 0 && aBoard[aEndPos.itsRow - 1][aEndPos.itsCol].itsPieceType == enemyPiece && aBoard[aEndPos.itsRow - 1][aEndPos.itsCol].itsPieceType != KING) {
        int row = aEndPos.itsRow - 2;
        if ((aBoard[row][aEndPos.itsCol].itsPieceType == friendlyPiece || (aBoard[row][aEndPos.itsCol].itsCellType == CASTLE && aBoard[row][aEndPos.itsCol].itsPieceType != KING) || aBoard[row][aEndPos.itsCol].itsCellType == FORTRESS) || (isDefence && aBoard[row][aEndPos.itsCol].itsPieceType == KING)) {
            aBoard[row+1][aEndPos.itsCol].itsPieceType = NONE;
        }
    }

    // Down
    if (aEndPos.itsRow + 2 < aBoardSize && aBoard[aEndPos.itsRow + 1][aEndPos.itsCol].itsPieceType == enemyPiece && aBoard[aEndPos.itsRow + 1][aEndPos.itsCol].itsPieceType != KING) {
        int row = aEndPos.itsRow + 2;
        if ((aBoard[row][aEndPos.itsCol].itsPieceType == friendlyPiece || (aBoard[row][aEndPos.itsCol].itsCellType == CASTLE && aBoard[row][aEndPos.itsCol].itsPieceType != KING) || aBoard[row][aEndPos.itsCol].itsCellType == FORTRESS)|| (isDefence && aBoard[row][aEndPos.itsCol].itsPieceType == KING)) {
            aBoard[row-1][aEndPos.itsCol].itsPieceType = NONE;
        }
    }

    // Left
    if (aEndPos.itsCol - 2 >= 0 && aBoard[aEndPos.itsRow][aEndPos.itsCol - 1].itsPieceType == enemyPiece && aBoard[aEndPos.itsRow][aEndPos.itsCol - 1].itsPieceType != KING) {
        int col = aEndPos.itsCol - 2;

        if ((aBoard[aEndPos.itsRow][col].itsPieceType == friendlyPiece || (aBoard[aEndPos.itsRow][col].itsCellType == CASTLE && aBoard[aEndPos.itsRow][col].itsPieceType != KING) || aBoard[aEndPos.itsRow][col].itsCellType == FORTRESS) || (isDefence && aBoard[aEndPos.itsRow][col].itsPieceType == KING)) {
            aBoard[aEndPos.itsRow][col+1].itsPieceType = NONE;
        }
    }

    // Right
    if (aEndPos.itsCol + 2 < aBoardSize && aBoard[aEndPos.itsRow][aEndPos.itsCol + 1].itsPieceType == enemyPiece && aBoard[aEndPos.itsRow][aEndPos.itsCol + 1].itsPieceType != KING) {
        int col = aEndPos.itsCol + 2;
        if ((aBoard[aEndPos.itsRow][col].itsPieceType == friendlyPiece || (aBoard[aEndPos.itsRow][col].itsCellType == CASTLE && aBoard[aEndPos.itsRow][col].itsPieceType != KING) || aBoard[aEndPos.itsRow][col].itsCellType == FORTRESS) || (isDefence && aBoard[aEndPos.itsRow][col].itsPieceType == KING)) {
            aBoard[aEndPos.itsRow][col-1].itsPieceType = NONE;
        }
    }
}




bool isSwordLeft(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    for (short int i = 0; i < aBoardSize; i++) {
        for (short int j = 0; j < aBoardSize; j++) {
            if (aBoard[i][j].itsPieceType == SWORD) {
                return true;
            }
        }
    }
    return false;
}

Position getKingPosition(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    Position pos = {-1, -1};
    for (short int i = 0; i < aBoardSize; i++) {
        for (short int j = 0; j < aBoardSize; j++) {
            if (aBoard[i][j].itsPieceType == KING) {
                pos.itsRow = i;
                pos.itsCol = j;
                return pos;
            }
        }
    }
    return pos;
}

bool isKingEscaped(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    Position kingPos = getKingPosition(aBoard, aBoardSize);
    if (kingPos.itsRow == -1 || kingPos.itsCol == -1) {
        return false;
    }
    if (aBoard[kingPos.itsRow][kingPos.itsCol].itsCellType == FORTRESS) {
        return true;
    }
    return false;
}

bool isKingCaptured(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    Position kingPos = getKingPosition(aBoard, aBoardSize);

    //Up
    if (kingPos.itsCol - 1 < 0 || aBoard[kingPos.itsRow][kingPos.itsCol-1].itsPieceType == SWORD || aBoard[kingPos.itsRow][kingPos.itsCol-1].itsCellType == CASTLE || aBoard[kingPos.itsRow][kingPos.itsCol-1].itsCellType == FORTRESS) {
        //Down
        if (kingPos.itsCol + 1 >= aBoardSize || aBoard[kingPos.itsRow][kingPos.itsCol+1].itsPieceType == SWORD || aBoard[kingPos.itsRow][kingPos.itsCol+1].itsCellType == CASTLE || aBoard[kingPos.itsRow][kingPos.itsCol+1].itsCellType == FORTRESS) {
            //Left
            if (kingPos.itsRow - 1 < 0 || aBoard[kingPos.itsRow-1][kingPos.itsCol].itsPieceType == SWORD || aBoard[kingPos.itsRow-1][kingPos.itsCol].itsCellType == CASTLE || aBoard[kingPos.itsRow-1][kingPos.itsCol].itsCellType == FORTRESS) {
                //Right
                if (kingPos.itsRow + 1 >= aBoardSize || aBoard[kingPos.itsRow+1][kingPos.itsCol].itsPieceType == SWORD || aBoard[kingPos.itsRow+1][kingPos.itsCol].itsCellType == CASTLE || aBoard[kingPos.itsRow+1][kingPos.itsCol].itsCellType == FORTRESS) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isPieceSurrounded(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aPos) {

    //Check if the piece is surrounded walls included and cell type included
    if (aPos.itsRow - 1 < 0 || aBoard[aPos.itsRow-1][aPos.itsCol].itsPieceType != NONE || aBoard[aPos.itsRow-1][aPos.itsCol].itsCellType == CASTLE || aBoard[aPos.itsRow-1][aPos.itsCol].itsCellType == FORTRESS) {
        if (aPos.itsRow + 1 >= aBoardSize || aBoard[aPos.itsRow+1][aPos.itsCol].itsPieceType != NONE || aBoard[aPos.itsRow+1][aPos.itsCol].itsCellType == CASTLE || aBoard[aPos.itsRow+1][aPos.itsCol].itsCellType == FORTRESS) {
            if (aPos.itsCol - 1 < 0 || aBoard[aPos.itsRow][aPos.itsCol-1].itsPieceType != NONE || aBoard[aPos.itsRow][aPos.itsCol-1].itsCellType == CASTLE || aBoard[aPos.itsRow][aPos.itsCol-1].itsCellType == FORTRESS) {
                if (aPos.itsCol + 1 >= aBoardSize || aBoard[aPos.itsRow][aPos.itsCol+1].itsPieceType != NONE || aBoard[aPos.itsRow][aPos.itsCol+1].itsCellType == CASTLE || aBoard[aPos.itsRow][aPos.itsCol+1].itsCellType == FORTRESS) {
                    return true;
                }
            }
        }
    }
    return false;
}


bool isKingCapturedV2(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, Position aKingPos)
{
    // If the king's position is not specified, find it
    if (aKingPos.itsRow == -1 || aKingPos.itsCol == -1) {
        aKingPos = getKingPosition(aBoard, aBoardSize);
    }

    // Check if the king is surrounded by pieces or walls
    if (isPieceSurrounded(aBoard, aBoardSize, aKingPos)) {
        return true;
    }

    // Check if the king can move to any neighboring cell
    if (aKingPos.itsRow - 1 >= 0 && aBoard[aKingPos.itsRow-1][aKingPos.itsCol].itsPieceType == NONE && aBoard[aKingPos.itsRow-1][aKingPos.itsCol].itsCellType != CASTLE && aBoard[aKingPos.itsRow-1][aKingPos.itsCol].itsCellType != FORTRESS) {
        if (!isKingCapturedV2(aBoard, aBoardSize, {aKingPos.itsRow-1, aKingPos.itsCol})) {
            return false;
        }
    }
    if (aKingPos.itsRow + 1 < aBoardSize && aBoard[aKingPos.itsRow+1][aKingPos.itsCol].itsPieceType == NONE && aBoard[aKingPos.itsRow+1][aKingPos.itsCol].itsCellType != CASTLE && aBoard[aKingPos.itsRow+1][aKingPos.itsCol].itsCellType != FORTRESS) {
        if (!isKingCapturedV2(aBoard, aBoardSize, {aKingPos.itsRow+1, aKingPos.itsCol})) {
            return false;
        }
    }
    if (aKingPos.itsCol - 1 >= 0 && aBoard[aKingPos.itsRow][aKingPos.itsCol-1].itsPieceType == NONE && aBoard[aKingPos.itsRow][aKingPos.itsCol-1].itsCellType != CASTLE && aBoard[aKingPos.itsRow][aKingPos.itsCol-1].itsCellType != FORTRESS) {
        if (!isKingCapturedV2(aBoard, aBoardSize, {aKingPos.itsRow, aKingPos.itsCol - 1})) {
            return false;
        }
    }
    if (aKingPos.itsCol + 1 < aBoardSize && aBoard[aKingPos.itsRow][aKingPos.itsCol+1].itsPieceType == NONE && aBoard[aKingPos.itsRow][aKingPos.itsCol+1].itsCellType != CASTLE && aBoard[aKingPos.itsRow][aKingPos.itsCol+1].itsCellType != FORTRESS) {
        if (!isKingCapturedV2(aBoard, aBoardSize, {aKingPos.itsRow, aKingPos.itsCol + 1})) {
            return false;
        }
    }

}

void saveBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const PlayerRole& aPlayer, const bool& isAi) {
    ofstream oFile("C:\\Windows\\Temp\\save.txt");

    // Check if the file was opened successfully
    if (oFile.is_open()) {
        // Write the board size to the file
        oFile << aBoardSize << endl;
        oFile << aPlayer << endl;
        oFile << isAi << endl;

        // Write the board contents to the file
        for (short int i = 0; i < aBoardSize; ++i) {
            for (short int j = 0; j < aBoardSize; ++j) {
                oFile << aBoard[i][j].itsCellType << " " << aBoard[i][j].itsPieceType << endl;
            }
        }

        // Close the file
        oFile.close();
    }
}

void loadBoard(Cell aBoard[][BOARD_SIZE_MAX], BoardSize & boardSize, PlayerRole & playerRole, bool & isVsAI) {
    ifstream iFile("C:\\Windows\\Temp\\save.txt");

    int size = 0;
    int player = 0;
    // Check if the file was opened successfully
    if (iFile.is_open()) {
        // Read the board size from the file

        iFile >> size;
        iFile >> player;
        iFile >> isVsAI;
        size == 11 ? boardSize = LITTLE : boardSize = BIG;
        player == 0 ? playerRole = ATTACK : playerRole = DEFENSE;

        // Read the board contents from the file
        int cell = 0;
        int piece = 0;
        for (short int i = 0; i < size; ++i) {
            for (short int j = 0; j < size; ++j) {
                iFile >> cell >> piece;
                aBoard[i][j].itsCellType = static_cast<CellType>(cell);
                aBoard[i][j].itsPieceType = static_cast<PieceType>(piece);
            }
        }

        // Close the file
        iFile.close();
        cout << "The game was loaded successfully." << endl;
    }

}

bool isSaveFileExists() {
    ifstream iFile("C:\\Windows\\Temp\\save.txt");
    return iFile.good();
}

void deleteSaveFile() {
    remove("C:\\Windows\\Temp\\save.txt");
}


void displayChosenPieceBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aPos) {
    cout << "    King: " << KING_CHAR << "      Shield:" << WHITE_CHAR << "      Sword:" << BLACK_CHAR << "     Fortress:O" << "     Castle:X"  <<endl;
    cout << " ";
    for(short int i = 1; i <= aBoardSize; i++) {
        cout << (i > 10 ? "    " : "     ") <<BLUE_BOLD << i << RESET;
    }
    cout << endl;


    char start = 'A';
    for(short int i = 1; i <= aBoardSize; i++) {
        cout << "   ";
        for(short int j = 1; j < aBoardSize+1; j++) {
            cout << "+-----";
        }
        cout << "+";
        cout << endl;
        cout <<BLUE_BOLD<< char(start-1+i) << RESET;
        for(short int j = 0; j < aBoardSize; j++) {
            if (aBoard[i-1][j].itsPieceType == NONE && aBoard[i-1][j].itsCellType == NORMAL) {
                cout << "  |   ";
            }
            else if (aBoard[i-1][j].itsPieceType == SWORD) {
                if (i-1 == aPos.itsRow && j == aPos.itsCol) {
                    cout << "  |  "<< HIGHLIGHT << BLUE_BOLD << BLACK_CHAR << RESET;
                } else {
                    cout << "  |  "<< BLACK_CHAR;
                }
            }
            else if (aBoard[i-1][j].itsPieceType == SHIELD){
                if (i-1 == aPos.itsRow && j == aPos.itsCol) {
                    cout << "  |  "<< HIGHLIGHT << BLUE_BOLD << WHITE_CHAR << RESET;
                } else {
                    cout << "  |  "<< WHITE_CHAR;
                }
            }
            else if (aBoard[i-1][j].itsPieceType == KING){
                if (i-1 == aPos.itsRow && j == aPos.itsCol) {
                    cout << "  |  "<< HIGHLIGHT << BLUE_BOLD << KING_CHAR << RESET;
                } else {
                    cout << "  |  "<< KING_CHAR;
                }
            }
            else if (aBoard[i-1][j].itsCellType == CASTLE){
                cout << "  |  "<< "X";
            }
            else if (aBoard[i-1][j].itsCellType == FORTRESS){
                cout << "  |  "<< "O";
            }
        }
        cout << "  |";
        cout << endl;
    }
    cout << "   ";
    for(short int j = 1; j < aBoardSize+1; j++) {
        cout << "+-----";
    }
    cout << "+";
    cout << endl;
}

bool isValidMovementSilent(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos) {
    //Check if the start position is empty
    if (isEmptyCell(aBoard, aStartPos)) {
        return false;
    }

    //Check if the piece belongs to the player
    if (aPlayer == ATTACK && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != SWORD) {
        return false;
    }
    else if (aPlayer == DEFENSE && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != SHIELD && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        return false;
    }

    //Check if the end position is empty
    if (!isEmptyCell(aBoard, aEndPos)) {
        return false;
    }

    //Check if the move is along the same row or column
    if (aStartPos.itsRow != aEndPos.itsRow && aStartPos.itsCol != aEndPos.itsCol) {
        return false;
    }

    //Check if only the king can go on the fortress
    if (aBoard[aEndPos.itsRow][aEndPos.itsCol].itsCellType == FORTRESS && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        return false;
    }

    //Check if only the king can pass on the castle
    if (aBoard[aEndPos.itsRow][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        return false;
    }

    //Check if there is the castle in the path
    if (aStartPos.itsRow == aEndPos.itsRow && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        //Check left
        if (aStartPos.itsCol > aEndPos.itsCol) {
            for (short int i = aStartPos.itsCol-1; i > aEndPos.itsCol; i--) {
                if (aBoard[aStartPos.itsRow][i].itsCellType == CASTLE) {
                    return false;
                }
            }
        }
            //Check right
        else {
            for (short int i = aStartPos.itsCol+1; i < aEndPos.itsCol; i++) {
                if (aBoard[aStartPos.itsRow][i].itsCellType == CASTLE) {
                    return false;
                }
            }
        }
    }
    else if (aStartPos.itsCol == aEndPos.itsCol && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING) {
        //Check up
        if (aStartPos.itsRow > aEndPos.itsRow) {
            for (short int i = aStartPos.itsRow-1; i > aEndPos.itsRow; i--) {
                if (aBoard[i][aStartPos.itsCol].itsCellType == CASTLE) {
                    return false;
                }
            }
        }
            //Check down
        else {
            for (short int i = aStartPos.itsRow+1; i < aEndPos.itsRow; i++) {
                if (aBoard[i][aStartPos.itsCol].itsCellType == CASTLE) {
                    return false;
                }
            }
        }
    }


    //Check if there is a piece in the path
    if (aStartPos.itsRow == aEndPos.itsRow) {
        //Check left
        if (aStartPos.itsCol > aEndPos.itsCol) {
            for (short int i = aStartPos.itsCol-1; i > aEndPos.itsCol; i--) {
                if (!isEmptyCell(aBoard, {aStartPos.itsRow, i})) {
                    return false;
                }
            }
        }
            //Check right
        else {
            for (short int i = aStartPos.itsCol+1; i < aEndPos.itsCol; i++) {
                if (!isEmptyCell(aBoard, {aStartPos.itsRow, i})) {
                    return false;
                }
            }
        }
    }
    else if (aStartPos.itsCol == aEndPos.itsCol) {
        //Check up
        if (aStartPos.itsRow > aEndPos.itsRow) {
            for (short int i = aStartPos.itsRow-1; i > aEndPos.itsRow; i--) {
                if (!isEmptyCell(aBoard, {i, aStartPos.itsCol})) {
                    return false;
                }
            }
        }
            //Check down
        else {
            for (short int i = aStartPos.itsRow+1; i < aEndPos.itsRow; i++) {
                if (!isEmptyCell(aBoard, {i, aStartPos.itsCol})) {
                    return false;
                }
            }
        }
    }


    return true;
}


int getAmountEmptyCells(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize) {
    int amount = 0;
    for (short int i = 0; i < aBoardSize; i++) {
        for (short int j = 0; j < aBoardSize; j++) {
            if (aBoard[i][j].itsPieceType == NONE) {
                amount++;
            }
        }
    }
    return amount;
}

int calculateScore(const Cell aBoard[][BOARD_SIZE_MAX], const int aPreviousAmountOfEmpty, const BoardSize& aBoardSize, const PlayerRole& aPlayerRole) {
    int score = 0;

    // Check if the king is captured
    if (aPlayerRole == ATTACK) {
        if (isKingCaptured(aBoard, aBoardSize)) {
            return +1000000;
        }
    }

    if (aPlayerRole == DEFENSE) {
        if (isKingEscaped(aBoard, aBoardSize)) {
            return +1000000;
        }
    }

    //Check amount of captures the move did, the more captures the better
    int captures = 0;
    int amountOfEmpty = getAmountEmptyCells(aBoard, aBoardSize);
    captures =  amountOfEmpty - aPreviousAmountOfEmpty;
    score += captures * 1000;

    return score;
}


Position chooseBestAiMove(Cell aBoard[][BOARD_SIZE_MAX], BoardSize& aBoardSize, PlayerRole& aPlayerRole) {
    Position bestMove = {-1, -1};
    Position previousPos = {-1, -1};

    int bestScore = INT_MIN;
    int amountOfEmpty = getAmountEmptyCells(aBoard, aBoardSize);

    // Check all possible moves
    for (short int i = 0; i < aBoardSize; ++i) {
        for (short int j = 0; j < aBoardSize; ++j) {
            if (aBoard[i][j].itsPieceType == SWORD || aBoard[i][j].itsPieceType == SHIELD || aBoard[i][j].itsPieceType == KING) {
                // Check all possible moves for the current piece
                for (short int k = 0; k < aBoardSize; ++k) {
                    for (short int l = 0; l < aBoardSize; ++l) {
                        // Check if the move is valid
                        if (isValidMovementSilent(aPlayerRole, aBoard, {i, j}, {k, l})) {
                            //Save the board
                            Cell tempBoard[BOARD_SIZE_MAX][BOARD_SIZE_MAX];
                            for (short int m = 0; m < aBoardSize; ++m) {
                                for (short int n = 0; n < aBoardSize; ++n) {
                                    tempBoard[m][n].itsCellType = aBoard[m][n].itsCellType;
                                    tempBoard[m][n].itsPieceType = aBoard[m][n].itsPieceType;
                                }
                            }

                            // Make the move
                            PieceType piece = aBoard[i][j].itsPieceType;
                            movePiece(aBoard, {i, j}, {k, l});
                            capturePieces(aPlayerRole, aBoard, aBoardSize, {k, l});

                            // Calculate the score of the move
                            int score = calculateScore(aBoard, amountOfEmpty, aBoardSize, aPlayerRole);

                            // Restore the board
                            for (short int m = 0; m < aBoardSize; ++m) {
                                for (short int n = 0; n < aBoardSize; ++n) {
                                    aBoard[m][n].itsCellType = tempBoard[m][n].itsCellType;
                                    aBoard[m][n].itsPieceType = tempBoard[m][n].itsPieceType;
                                }
                            }



                            // Check if the score is better than the current best score
                            if (score > bestScore) {
                                bestScore = score;
                                bestMove = {i, j};
                                previousPos = {k, l};
                            }
                        }
                    }
                }
            }
        }
    }

    movePiece(aBoard, bestMove, previousPos);

    cout << "The AI moved from " << char(bestMove.itsRow + 65) << bestMove.itsCol + 1 << " to " << char(previousPos.itsRow + 65) << previousPos.itsCol + 1 << " Score: " << bestScore << endl;
    return previousPos;
}

void createStatisticFile() {
    ofstream oFile("C:\\Windows\\Temp\\statistic.txt");


    // Check if the file was opened successfully
    if (oFile.is_open()) {
        // Write the board size to the file
        oFile << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << endl;

        // Close the file
        oFile.close();
    }
}

bool isStatisticFileExists() {
    ifstream iFile("C:\\Windows\\Temp\\statistic.txt");
    return iFile.good();
}

void readStatisticFile(int& aAmountOfGames, int&aAmountOfDefenceWins, int& aAmountOfAttackWins, int& aAmountOfAiWins) {
    ifstream iFile("C:\\Windows\\Temp\\statistic.txt");

    // Check if the file was opened successfully
    if (iFile.is_open()) {
        // Read the board size from the file
        iFile >> aAmountOfGames >> aAmountOfDefenceWins >> aAmountOfAttackWins >> aAmountOfAiWins >> aAmountOfAiWins;

        // Close the file
        iFile.close();
    }
}

void writeStatisticFile(int aAmountOfGames, int aAmountOfDefenceWins, int aAmountOfAttackWins, int aAmountOfAiWins) {
    remove("C:\\Windows\\Temp\\statistic.txt");
    ofstream oFile("C:\\Windows\\Temp\\statistic.txt");

    // Check if the file was opened successfully
    if (oFile.is_open()) {
        // Write the board size to the file
        oFile << aAmountOfGames << " " << aAmountOfDefenceWins << " " << aAmountOfAttackWins << " " << aAmountOfAiWins << endl;
        // Close the file
        oFile.close();
    }
}

void displayStatistics(int amountOfPlayed, int amountOfAttackWins, int amountOfDefenceWins, int amountOfAiWins) {
    cout << "-------------------" << BLUE_BOLD << "Statistics"<< RESET << "-----------------------" << endl;
    cout << "Amount of games played: " << amountOfPlayed << endl;
    cout << "Amount of AI wins: " << amountOfAiWins << endl;
    cout << "Amount of attack wins: " << amountOfAttackWins << endl;
    cout << "Amount of defence wins: " << amountOfDefenceWins << endl;
    cout << "---------------------------------------------------" << endl;
}

void displayThanksForPlayingAnimation() {
    clearConsole();
    cout << R"(
        ███        ▄█    █▄       ▄████████ ███▄▄▄▄      ▄█   ▄█▄    ▄████████
    ▀█████████▄   ███    ███     ███    ███ ███▀▀▀██▄   ███ ▄███▀   ███    ███
       ▀███▀▀██   ███    ███     ███    ███ ███   ███   ███▐██▀     ███    █▀
        ███   ▀  ▄███▄▄▄▄███▄▄   ███    ███ ███   ███  ▄█████▀      ███
        ███     ▀▀███▀▀▀▀███▀  ▀███████████ ███   ███ ▀▀█████▄    ▀███████████
        ███       ███    ███     ███    ███ ███   ███   ███▐██▄            ███
        ███       ███    ███     ███    ███ ███   ███   ███ ▀███▄    ▄█    ███
       ▄████▀     ███    █▀      ███    █▀   ▀█   █▀    ███   ▀█▀  ▄████████▀
                                                        ▀
                                                                                )" << endl;
    universalSleep(200);
    cout << R"(
           ▄████████  ▄██████▄     ▄████████
          ███    ███ ███    ███   ███    ███
          ███    █▀  ███    ███   ███    ███
         ▄███▄▄▄     ███    ███  ▄███▄▄▄▄██▀
        ▀▀███▀▀▀     ███    ███ ▀▀███▀▀▀▀▀
          ███        ███    ███ ▀███████████
          ███        ███    ███   ███    ███
          ███         ▀██████▀    ███    ███
                                  ███    ███
                                                                                )" << endl;
    universalSleep(200);
    cout << R"(
         ██▓███   ██▓    ▄▄▄     ▓██   ██▓ ██▓ ███▄    █   ▄████
        ▓██░  ██▒▓██▒   ▒████▄    ▒██  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
        ▓██░ ██▓▒▒██░   ▒██  ▀█▄   ▒██ ██░▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
        ▒██▄█▓▒ ▒▒██░   ░██▄▄▄▄██  ░ ▐██▓░░██░▓██▒  ▐▌██▒░▓█  ██▓
        ▒██▒ ░  ░░██████▒▓█   ▓██▒ ░ ██▒▓░░██░▒██░   ▓██░░▒▓███▀▒
        ▒▓▒░ ░  ░░ ▒░▓  ░▒▒   ▓▒█░  ██▒▒▒ ░▓  ░ ▒░   ▒ ▒  ░▒   ▒
        ░▒ ░     ░ ░ ▒  ░ ▒   ▒▒ ░▓██ ░▒░  ▒ ░░ ░░   ░ ▒░  ░   ░
        ░░         ░ ░    ░   ▒   ▒ ▒ ░░   ▒ ░   ░   ░ ░ ░ ░   ░
                     ░  ░     ░  ░░ ░      ░           ░       ░
                                  ░ ░
                                                                                )" << endl;
    universalSleep(200);
}
