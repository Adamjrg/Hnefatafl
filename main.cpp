#include <iostream>
#include <conio.h>
#include "typeDef.h"

using namespace std;
const string RESET = "\e[0m";
const string BOLD_RED  = "\e[1;31m";
const string HIGHLIGHT  = "\e[7m";
const string BLUE_BOLD = "\x1b[34;1m";


//Main function
int main()
{
    int menu = 0;
    int choice = 0;

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
        main(); //Restart
        break;

    //Game
    case 3:

        cout << "Would you like to play on a 11x11 or 13x13 grid? (11,13)" << endl;
        cin >> choice;
        switch(choice){
        case 11:
            break;
        case 13:
            break;
        default:
            cout << BOLD_RED << "Please enter a valid choice" << RESET << endl;
            getch(); //Wait for user input
            main();
            break;
        }

        break;
    //Invalid input
    default:
        cout << BOLD_RED << "Please enter a valid option" << RESET << endl;
        getch(); //Wait for user input
        main(); //Recursion recall to restart
        break;
    }



    return 0;
}
