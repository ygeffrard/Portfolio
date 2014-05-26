/****************************************************************************
                                YARLEY GEFFRARD
                                TIC TAC TOE GAME
                                tictactoemain.cpp


Title : tictactoemain.cpp
Author : Yarley Geffrard
Created on : February 17, 2014
Description : Plays the famous "tic tac toe" game against the computer with Xs
and Os and allows the player to see their progress on an actual tictactoe board

Purpose : Allows tic tac toe to be played using simple Graphic user interface, the
application has a separate interface and implementation which processes the actual game
and all the moves and actual updated board of the game. This game is only played
with Xs and Os. The only thing the user has to worry about is if they want
to play again and typing their name in the beginning of the start of the
program.

Usage : Play Tic Tac Toe agains computer!
Input your name
Choose X or O
and Play!
(C) YARLEY G - Free to use

Build with : g++ -c tictactoemain.cpp
******************************************************************************/

/*
Classes Seperated
To compile:
1. g++ -c tictactoe.cpp - will create tictactoeo.o
2. g++ -c tictactoemain.cpp - will create tictactoemain.o
3. g++ -o tictactoemain tictactoe.o tictactoe.o
4. ./tictactoe
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "tictactoe.h"

using namespace std;

int main()
{

bool replay = true;

while (replay)
   {

    tictactoe userInfo; // Diplays Welcome information for game
    userInfo.setName(); // Asks the user for their name and stores it
    userInfo.setUserSide(); // Asks the user if they want to pick X or O

    char playerSide = userInfo.getUserSide(); //string values stored to main of player's side "X" or "O" from function
    string playerName = userInfo.getName(); // string value stored to main of player's name from function
    cout << "Hi "<< playerName << ". " << "You are "<< playerSide << endl; //Displays user's name and the side they have chosen

//  Just to determine who gets to go first, whoever has X gets to go second
    int compTurn;

    if (playerSide == 'X')
        {
        cout << "You get to go first. Computer is O and gets to go second." << endl;
        compTurn = 1;
        }
    else
        {
        cout << "You get to go second. Computer is X and gets to go first." << endl;
        compTurn = 0;
        }

    userInfo.displayBoard(); //Displays initial board with no values

    userInfo.makeMove(compTurn); //Function that takes which player goes first and starts playing, if computer is 0, it goes first.

    if (userInfo.aWinner() == false) // If there is no winner, and it reaches this far means that the board is full and there is no winner
    {
    cout << "\n\nSorry! The board is full and there is no winner" <<endl;
    }


    char playAgain; // Variable which will store user's answer Yes or No to play again
    bool replayMenu = true; //value which stores replay menu option as true or false

    while (replayMenu) //While replay menu is true it asks the user for the same options again
        {
    cout << "\n\nWould you like to play again? Y or N?" <<endl; //Asks user if they would like to play again.
    cin >> playAgain;
    cout << endl;

        if ((playAgain =='Y') || (playAgain =='y')) // If the user chooses to play again then the game will restart
            {
            replay = true;
            replayMenu = false;
            }
        else if ((playAgain =='N') || (playAgain =='n')) //If the user chooses not to play then the game will end
            {
            cout << "Thank you for playing. Goodbye!\n" <<endl;;
            return 0;
            break;
            }
        else // If the user types anything other then "Y" or "N" then it will ask them to enter "Y" or "N"
            {
            cout << "Please enter Y for Yes or N for No";
            replayMenu = true;
            }
        }
    }

return 0;
}
