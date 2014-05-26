/****************************************************************************
                                YARLEY GEFFRARD
                                TIC TAC TOE GAME
                                tictactoe.h Interface


Title : tictactoe.h
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

Build with : tictactoe.h
******************************************************************************/

/*Header File, all classses prototypes and declarations
*/
#include <iostream>
#include <string>
#include <cstdlib>

#ifndef tictactoe_H
#define tictactoe_H

//const int dimension = 3;

class tictactoe
{
	public:
        tictactoe(); // public class member which is used to display welcome screen

		void setName (); // sets the name of the user received from user

        std::string getName() // gets the name of the user received from user
        {
            return name;
		}

		void setUserSide(); // sets the side X or O of the user received from user

        char getUserSide() // gets the side X or O of the user received from user
        {
            return userSide;
		}

		char getCompSide() // gets the side X or O of the computer
        {
            return compSide;
		}

        void displayBoard(); // function that just displays the initial blank board

        void displayUpdatedBoard(); // function to display updated board after each user's turn

        void computerMove(); //Function which plays for computer

        void playerMove(); //Function that processes player's turn

        bool aWinner(); // Determine if there are 3 Xs or 3 Os that are together in a row, column, or diagonally after the turn

//      bool playSmart(char theSide, int x, int y);

        bool boardNotFull(char theSide); // Determine if the board is not full, there is still one "_"

        bool validMove(char someMove, int x, int y); //Determines if a given move is valid and if it isn't it asks the user for another move, if it is it sets the given move the user's/computer's selected place value

        void makeMove(int comp); //Function that accepts the values for computer's and player's turns and request that the game starts

        void theWinner(char gameWinner); // Sets the winner of the game to either Computer or the user who's playing and prints out their name

        //Destructors
//        ~void setName ();
//        ~void setUserSide();
//        ~void displayUpdatedBoard();
//        ~void makeMove(int comp);
//        ~void theWinner(char gameWinner);
//        ~void displayUpdatedBoard();


	private:
        std::string name; //private class member to store name of user
        char userSide; //private class member to store side 'X' or 'O' of user
        char compSide; //private class member to store side 'X' or 'O' of computer
        char updatedBoard[3][3]; //private class member that stores update of the multiDimensional array of the board
        std::string winner; //private class member to store nam
};


#endif //Tictactoe_H
