#include <iostream>
#include <conio.h>
#include "typeDef.h"

using namespace std;

const string RESET = "\e[0m";
const string BOLD_RED  = "\e[1;31m";
const string HIGHLIGHT  = "\e[7m";
const string BLUE_BOLD = "\x1b[34;1m";

const string BLACK_CHAR = "\u25CB";
const string WHITE_CHAR = "\u25CF";
const string KING_CHAR = "\u25CA";


//Main function
int main()
{
    int menu = 0;
    int choice = 0;
    int boardSize = 0;


    //Welcome message
    system("cls");
    cout << " _   _             __      _         __ _ " << endl;
    cout << "| | | |           / _|    | |       / _| |" << endl;
    cout << "| |_| |_ __   ___| |_ __ _| |_ __ _| |_| |" << endl;
    cout << "|  _  | '_ "<< "\\" << " / _ "<< "\\"<<"  _/ _` | __/ _` |  _| |" << endl;
    cout << "| | | | | | |  __/ || (_| | || (_| | | | |" << endl;
    cout << "\\"<<"_| |_/_| |_|"<<"\\"<<"___|_| "<<"\\"<<"__,_|"<<"\\"<<"__"<<"\\"<<"__,_|_| |_|" << endl;
    cout << endl;
    cout << "Welcome to Hnefatafl" << endl;
    cout << "Please chose an option from the menu:" << endl;
    cout << "(1) Rules" << endl;
    cout << "(2) Credits" << endl;
    cout << "(3) Play" << endl;
    cin >> menu;

    switch (menu) {
    //Rules
    case 1:
        system("cls");
        cout << BOLD_RED << "Setup:" << RESET << endl;
        cout << "The game is played on a square board with a grid of 11x11 or 13x13 squares." << endl;
        cout << "The central square is the throne, and the four corner squares are the escape squares." << endl;
        cout << "The defenders, represented by white pieces, set up in a cross-shaped formation around the king on the central square." << endl;
        cout << "The attackers, represented by black pieces, surround the defenders on all sides." << endl;
        cout << endl;
        cout << BOLD_RED << "Movement:" << RESET << endl;
        cout << "The king moves like the other pieces but can only move one square at a time, vertically or horizontally (not diagonally)." << endl;
        cout << "All other pieces, both attackers and defenders, move like chess rooks (horizontally or vertically) and capture by surrounding an opponent's piece on two opposite sides (horizontally or vertically)." << endl;
        cout << endl;
        cout << BOLD_RED << "Objective:"<< RESET << endl;
        cout << "The attackers win by capturing the defender's king, surrounding it on all four sides." << endl;
        cout << "The defenders win by moving their king to one of the corner squares (escape squares) or by blocking the attackers' movement until they can't make a legal move." << endl;
        cout << endl;
        cout << BOLD_RED <<"Capture Rules:" << RESET << endl;
        cout << "To capture an opponent's piece, you must sandwich it between two of your own pieces along a horizontal or vertical line." << endl;
        cout << "The king can be used to make captures just like other pieces." << endl;
        cout << endl;
        cout << BOLD_RED <<"Turns and Gameplay:" << RESET << endl;
        cout << "Players take turns, starting with the attackers." << endl;
        cout << "The player must move one of their pieces on their turn." << endl;
        cout << "A player can't move through or onto a square occupied by their own piece." << endl;
        cout << endl;
        cout << BOLD_RED << "Winning:" << RESET << endl;
        cout << "If the attackers capture the king, they win." << endl;
        cout << "If the defenders move their king to one of the corner squares or create a situation where the attackers can't make a legal move, they win." << endl;
        cout << endl;
        cout << BOLD_RED << "Stalemate:"<< RESET << endl;
        cout << "If a position repeats three times without any progress (same pieces in the same positions), the game is a draw." << endl;
        cout << endl;
        cout << "These are the fundamental rules of Hnefatafl. The game combines strategy and tactics, and the balance between the attackers and defenders makes for an intriguing and challenging board game." << endl;
        getch();
        main(); //Restart
        break;

    //Credits
    case 2:
        system("cls");
        cout << "This game was coded by " << BLUE_BOLD << "GLOVER Adam" << RESET << endl;
        getch();
        cin.clear();
        cin.ignore();
        main(); //Restart
        break;

    //Game
    case 3:

        cout << "Would you like to play on a 11x11 or 13x13 grid? (11,13)" << endl;
        cin >> choice;
        switch(choice){
        case 11:
            boardSize = LITTLE;
            break;
        case 13:
            boardSize = BIG;
            break;
        default:
            cout << BOLD_RED << "Please enter a valid choice" << RESET << endl;
            cin.clear();
            cin.ignore();
            main();
            break;
        }
        break;
    //Invalid input
    default:
        cout << BOLD_RED << "Please enter a valid option" << RESET << endl;
        cin.clear();
        cin.ignore();
        main(); //Restart
        break;
    }

    Cell gameBoard[boardSize][boardSize];
    //Initializing game board to empty
    for (short int i = 0; i < boardSize;i++)
    {
        for (short int j = 0; j < boardSize;j++) {
            gameBoard[i][j].itsCellType= NORMAL;
            gameBoard[i][j].itsPieceType= NONE;
        }
    }

    //Set black peices
    for (short int i = (boardSize/2)-2; i <= (boardSize/2)+2;i++)
    {
        //Top and bottom pieces
        gameBoard[i][0].itsPieceType= SWORD;
        gameBoard[i][boardSize-1].itsPieceType= SWORD;

        //Left and right side pieces
        gameBoard[0][i].itsPieceType= SWORD;
        gameBoard[boardSize-1][i].itsPieceType= SWORD;
    }
    //Top and bottom center pieces
    gameBoard[boardSize/2][1].itsPieceType = SWORD;
    gameBoard[boardSize/2][boardSize-2].itsPieceType = SWORD;

    //Left and right middle pieces
    gameBoard[1][boardSize/2].itsPieceType = SWORD;
    gameBoard[boardSize-2][boardSize/2].itsPieceType = SWORD;


    //Set white pieces for the big board
    if (boardSize == BIG) {
        for (short int i =(boardSize/2)-3; i <= (boardSize/2)+3; i++) {
            if (i != boardSize/2) {
                gameBoard[i][boardSize/2].itsPieceType = SHIELD;
                gameBoard[boardSize/2][i].itsPieceType = SHIELD;
            }
        }
    }//Set white pieces for the small board
    else if (boardSize == LITTLE)
    {
        int offset = 0;
        for (short int i =(boardSize/2)-2; i <= (boardSize/2)+2; i++)
        {
            for (short int j =(boardSize/2)-offset; j <= (boardSize/2)+offset; j++) {
                gameBoard[i][j].itsPieceType = SHIELD;
            }

            if (i >= boardSize/2) {
                offset-=1;
            } else {
                offset+=1;
            }
        }
    }


    //Set king
    gameBoard[boardSize/2][boardSize/2].itsPieceType = KING;

    //Set Fortress tile
    gameBoard[boardSize/2][boardSize/2].itsCellType = FORTRESS;

    //Set Castle tiles
    gameBoard[0][0].itsCellType = CASTLE;
    gameBoard[0][boardSize-1].itsCellType = CASTLE;
    gameBoard[boardSize-1][0].itsCellType = CASTLE;
    gameBoard[boardSize-1][boardSize-1].itsCellType = CASTLE;


    //Show the board
    cout << " ";
    for(short int i = 1; i <= boardSize; i++) {
        cout << (i > 10 ? "    " : "     ") <<BLUE_BOLD << i << RESET;
    }
    cout << endl;


    char start = 'A';
    for(short int i = 1; i <= boardSize; i++) {
        cout << "   ";
        for(short int j = 1; j < boardSize+1; j++) {
            cout << "+-----";
        }
        cout << "+";
        cout << endl;
        cout <<BLUE_BOLD<< char(start-1+i) << RESET;
        for(short int j = 0; j < boardSize; j++) {
            if (gameBoard[i-1][j].itsPieceType == NONE && gameBoard[i-1][j].itsCellType == NORMAL) {
                cout << "  |   ";
            }
            else if (gameBoard[i-1][j].itsPieceType == SWORD) {
                cout << "  |  "<< BLACK_CHAR;
            }
            else if (gameBoard[i-1][j].itsPieceType == SHIELD){
                cout << "  |  "<< WHITE_CHAR;
            }
            else if (gameBoard[i-1][j].itsPieceType == KING){
                cout << "  |  "<< KING_CHAR;
            }
            else if (gameBoard[i-1][j].itsCellType == CASTLE){
                cout << "  |  "<< "X";
            }
            else if (gameBoard[i-1][j].itsCellType == FORTRESS){
                cout << "  |  "<< "O";
            }
        }
        cout << "  |";
        cout << endl;
    }
    cout << "   ";
    for(short int j = 1; j < boardSize+1; j++) {
        cout << "+-----";
    }
    cout << "+";
    cout << endl;



    return 0;
}
