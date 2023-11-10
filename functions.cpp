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

#include "typeDef.h"
#include "functions.h"

using namespace std;

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


void displayHnefataflLogo(){
    cout << " _   _             __      _         __ _ " << endl;
    cout << "| | | |           / _|    | |       / _| |" << endl;
    cout << "| |_| |_ __   ___| |_ __ _| |_ __ _| |_| |" << endl;
    cout << "|  _  | '_ "<< "\\" << " / _ "<< "\\"<<"  _/ _` | __/ _` |  _| |" << endl;
    cout << "| | | | | | |  __/ || (_| | || (_| | | | |" << endl;
    cout << "\\"<<"_| |_/_| |_|"<<"\\"<<"___|_| "<<"\\"<<"__,_|"<<"\\"<<"__"<<"\\"<<"__,_|_| |_|" << endl;
    cout << endl;
    cout << "Welcome to Hnefatafl" << endl;
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
