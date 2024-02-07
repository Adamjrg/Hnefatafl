# Hnefatafl

Hnefatafl is a console version of the ancient board game played by the Vikings. It is a two-player game where one player controls the king and his defenders, and the other player controls the attackers. The king’s goal is to escape to one of the corner squares or capture all the attacking peices, while the attackers’ goal is to capture the king by surrounding him on all four sides.

This project was created as a class assignment in C++. It includes an AI opponent, statistics tracking, and graphics rendering in the console.

## Installation

To install and run this project, you need to have a C++ compiler and a terminal emulator that supports ASCII escape codes. You can use any IDE or editor of your choice.

To clone this repository, use the following command:

`git clone https://github.com/adamjrg/hnefatafl.git`  
`cd hnefatafl`

To compile the source code, open it up in your favorite IDE (I use CLion) and press the build button

This will create a .exe file that you can run

## Usage

When you run the program, you will see a menu with the following options:

1. Play against AI: Start a new game against the AI opponent. You can choose the difficulty level and the side you want to play as.
2. Play against human: Start a new game against another human player on the same computer. You can choose the side you want to play as.
3. Load game: Load a previously saved game from a file.
3. Quit: Exit the program.

To select an option, type the number that is becide it and press Enter.

During the game, you will see the board and the pieces displayed in the console. The board is 11x11 or 13x13 squares depending on which option you chose, with the king starting in the center and the attackers surrounding him. The corner squares are marked with O and are the escape points for the king. The pieces are represented by the following symbols:

- ◊: King (white)
- ●: Defender (white)
- ○: Attacker (black)
- O: Escape

To move a piece, Enter the square that you would like to move and then the square where you would like it it move too. You can only move a piece in a straight line, as long as there are no other pieces in the way. You can capture an enemy piece by surrounding it on two opposite sides with your pieces. The king can also participate in captures, but he can only be captured by four attackers. Your game will be saved automatically on quit and can be reloaded by selecting the "Load Game" option in the main menu.

The game ends when either the king reaches a corner square, or the king is captured by the attackers or when all the arrackers are captured. The program will display the result and update the statistics accordingly.

## Features

This project has the following features:

- An AI opponent that uses a score system to calculate which move to make prioritizing escaping the king or capturing a piece. The AI can play only as the deffence, and is relitevely hard to beat as a beginner to the game.
- Statistics tracking that records the number of games played, won, and lost, as well as how many times you played against an AI. The statistics are stored in a file.
- Graphics rendering that uses ASCII to display the board and the pieces in color and with Unicode symbols. The graphics are compatible with most terminal.

## Credits

This project was created by Adam G as a class assignment for DEV1 at the IUT of La Rochelle. The rules and the history of Hnefatafl were based on the following sources:

- [The Rules Of Hnefatafl: Learn To Play “Viking Chess”](https://www.vikingchess.org/rules-of-hnefatafl)
- [HNEFATAFL RULES - The Museum Of Games and Gaming](https://www.mastersofgames.com/rules/hnefatafl-viking-chess-rules.htm)
- [How to play Hnefatafl | Official Rules | UltraBoardGames](https://www.ultraboardgames.com/hnefatafl/game-rules.php)
- And the rules set by the assignement

## Images

<img src="https://github.com/Adamjrg/Hnefatafl/blob/prod/images/MainMenu.PNG" width="400"/> <img src="https://github.com/Adamjrg/Hnefatafl/blob/prod/images/Options.PNG" width="400"/> <img src="https://github.com/Adamjrg/Hnefatafl/blob/prod/images/Rules.PNG" width="400"/>
