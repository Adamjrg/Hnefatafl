/**
 * @file tests.h
 *
 * @brief Declarations of test functions for testing the fonctions implemented in 'fonctions.cpp'.
 *
 * This file contains the declarations of test functions used to verify and validate
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
 * @author JMB - IUT Informatique La Rochelle
 * @date 03/10/2023
 */

#ifndef TESTS_H
#define TESTS_H

/**
 * @brief Test function for the chooseSizeBoard function.
 *
 * This function tests the chooseSizeBoard function by simulating user input and
 * checking the returned values.
 */
void test_chooseSizeBoard(int & pass, int & failed);

/**
 * @brief Test function for the initializeBoard function.
 *
 * This function tests the initializeBoard function by comparing the generated board with expected board configurations.
 */
void test_initializeBoard(int & pass, int & failed);

/**
 * @brief Test function for the getPositionFromInput function.
 *
 * This function tests the getPositionFromInput function by providing various input strings and comparing the
 * returned positions with expected positions.
 */
void test_getPositionFromInput(int & pass, int & failed);

/**
 * @brief Test function for the isValidPosition function.
 *
 * This function tests the isValidPosition function for different board sizes, valid positions, and invalid positions.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isValidPosition(int & pass, int & failed);

/**
 * @brief Test function for the isEmptyCell function.
 *
 * This function tests the isEmptyCell function for different cell types and positions.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isEmptyCell(int & pass, int & failed);

/**
 * @brief Test function for the isValidMovement function.
 *
 * This function tests the isValidMovement function for different types of moves
 * (ATTACK and DEFENSE) and various scenarios, including piece types and board cell types.
 * It counts the number of tests passed and failed and displays the results.
 */
void test_isValidMovement(int & pass, int & failed);

/**
 * @brief Test the movePiece function with different board sizes and piece types.
 *
 * This function tests the movePiece function by setting up various scenarios
 * with different board sizes (LITTLE and BIG) and different piece types (SWORD, SHIELD, KING).
 * It verifies whether pieces are correctly moved on the board.
 */
void test_movePiece(int & pass, int & failed);

/**
 * @brief Test the capturePieces function with various scenarios.
 *
 * This function tests the capturePieces function by setting up different scenarios
 * to capture pieces on the board. It covers scenarios involving attacks and defenses,
 * capturing pieces with various configurations, and checking the results.
 */
void test_capturePieces(int & pass, int & failed);

/**
 * @brief Test function for isSwordLeft.
 *
 * This function tests the behavior of the isSwordLeft function to determine if swords are present on the board.
 * It performs two test cases:
 * 1. Ensures that isSwordLeft correctly detects the absence of swords.
 * 2. Ensures that isSwordLeft correctly detects the presence of swords.
 */
void test_isSwordLeft(int & pass, int & failed);

/**
 * @brief Test function for getKingPosition.
 *
 * This function tests the behavior of the getKingPosition function to retrieve the position of the king on the board.
 * It performs multiple test cases for different board sizes and positions of the king.
 */
void test_getKingPosition(int & pass, int & failed);

/**
 * @brief Test function for isKingEscaped.
 *
 * This function tests the behavior of the isKingEscaped function to check if the king has escaped from the board.
 * It performs multiple test cases for different board sizes and king positions.
 */
void test_isKingEscaped(int & pass, int & failed);

/**
 * @brief Test function for isKingCaptured.
 *
 * This function tests the behavior of the isKingCaptured function to check if the king is captured by attackers.
 * It performs multiple test cases for different scenarios on a specified board size (LITTLE).
 */
void test_isKingCaptured(int & pass, int & failed);

/**
 * @brief Test function for isKingCapturedV2.
 *
 * This function tests the behavior of the isKingCapturedV2 function to check if the king is captured by attackers
 * with advanced scenarios. It performs multiple test cases for different scenarios on a specified board size (LITTLE).
 */
void test_isKingCapturedV2(int & pass, int & failed);


#endif // TESTS_H
