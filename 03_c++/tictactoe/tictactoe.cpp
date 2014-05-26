/****************************************************************************
                                YARLEY GEFFRARD
                                TIC TAC TOE GAME
                                tictactoe.cpp Implementation


Title : tictactoe.cpp
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

Build with : g++ -c tictactoe.cpp
******************************************************************************/


#include <iostream>
#include <string>
#include <cstdlib>
#include "tictactoe.h"


using namespace std;

tictactoe::tictactoe() //binary scope resolution operator - tictactoe is a member of tictactoe(Class). the second "tictactoe" is the constructor.
// This displays the welcome screen and the board of the game.
{
	cout << "\n\n*************************************" << endl;
	cout << "*                                   *" << endl;
	cout << "* 	Welcome to Tic Tac Toe	    *" << endl;
	cout << "*    				    *" << endl;
	cout << "*************************************\n\n" << endl;
}


void tictactoe::setName() //Function that asks user to enter their name and stores it to the string "name"
{
    cout << "Please enter your name" << endl;
    string uN; // String that stores user's name
	cin >> uN;
	name = uN; // String "name" is in a private class tictactoe and is now the name that the user entered
}


void tictactoe::setUserSide() //Fucntion that asks user to choose X or O
{
    cout << "Please enter which side you prefer X or O" << endl;
	char uS; // String that stores the user's side X or O
	cin >> uS;
	cout << endl;
	if ((uS == 'X') || (uS == 'x')) //If it is lower case or upper case X, the user will be upper case "X"
	{
            userSide = 'X';
            compSide = 'O';
	}
	else if ((uS == '0') || (uS == 'O') || (uS == 'o')) //If it is lower case or upper case O, the user will be upper case "O"
	{
            userSide = 'O';
            compSide = 'X';
    }
    else // If the user entered anything but X,x,O,o,0 then it will ask them to enter the appropriate value
    {
    cout << "Please try again.\n" <<endl;
    setUserSide();
    }

}


void tictactoe::displayBoard() // Displays initial default Tic Tac Toe Board
{
    char R0[] = "\n\n         C0       C1      C2    \n (0,0)\n";
// Row with Column coordinates

    char R1[] = "              |       |        \n   R0     _   |   _   |   _   \n              |       |        \n       -----------------------\n";
// 1st Row with Row coordinates

    char R2[] = "              |       |        \n   R1     _   |   _   |   _    \n              |       |        \n       -----------------------\n";
// 2nd Row with Row coordinates

    char R3[] = "              |       |        \n   R2     _   |   _   |   _    \n              |       |        \n";
// 3rd Row with Row coordinates

    R1[42] = '_'; // Place value for Row 1, Column 0
    R1[50] = '_'; // Place value for Row 1, Column 1
    R1[58] = '_'; // Place value for Row 1, Column 2
    R2[42] = '_'; // Place value for Row 2, Column 0
    R2[50] = '_'; // Place value for Row 2, Column 1
    R2[58] = '_'; // Place value for Row 2, Column 2
    R3[42] = '_'; // Place value for Row 3, Column 0
    R3[50] = '_'; // Place value for Row 3, Column 1
    R3[58] = '_'; // Place value for Row 3, Column 2

    cout << R0 <<R1<< R2 <<R3 <<endl; //Displays the board

int x, y; // Dummy values to set initial values for row and column of updatedBoard to blank space '_'
    for (x=0; x < 3; x++)
        for (y=0; y < 3; y++)
            {
            updatedBoard[x][y] = '_';
            }
}


void tictactoe::displayUpdatedBoard() // Displays initial default Tic Tac Toe Board
{
    char R0[] = "\n\n         C0       C1      C2    \n (0,0)\n";
// Row with Column coordinates

    char R1[] = "              |       |        \n   R0     _   |   _   |   _   \n              |       |        \n       -----------------------\n";
// 1st Row with Row coordinates

    char R2[] = "              |       |        \n   R1     _   |   _   |   _    \n              |       |        \n       -----------------------\n";
// 2nd Row with Row coordinates

    char R3[] = "              |       |        \n   R2     _   |   _   |   _    \n              |       |        \n";
// 3rd Row with Row coordinates

    R1[42] = updatedBoard[0][0]; // Place value for Row 1, Column 0
    R1[50] = updatedBoard[0][1]; // Place value for Row 1, Column 1
    R1[58] = updatedBoard[0][2]; // Place value for Row 1, Column 2
    R2[42] = updatedBoard[1][0]; // Place value for Row 2, Column 0
    R2[50] = updatedBoard[1][1]; // Place value for Row 2, Column 1
    R2[58] = updatedBoard[1][2]; // Place value for Row 2, Column 2
    R3[42] = updatedBoard[2][0]; // Place value for Row 3, Column 0
    R3[50] = updatedBoard[2][1]; // Place value for Row 3, Column 1
    R3[58] = updatedBoard[2][2]; // Place value for Row 3, Column 2

    cout << R0 <<R1<< R2 <<R3 <<endl; //Displays the board
}


void tictactoe::makeMove(int comp) //Function that accepts the values for computer's and player's first turn and request that the game starts
{
    if (comp == 0)
    {
        cout << "Computer, please go.\n" <<endl;
        computerMove(); // If the computer is 0 then they go first
    }
    else
    {
        cout << name << " please go.\n" <<endl;
        playerMove(); // If the computer is not 0 then the player goes first
    }
}


void tictactoe::computerMove() //Function which plays for computer
{
int x = rand()%3+0; // Generates a random value from 0 to 2 for which row to try to play in
int y = rand()%3+0; // Generates a random value from 0 to 2 for which column to try to play in

//if (playSmart(getUserSide(), x, y) == true)
//{
        if (validMove(getCompSide(), x, y) == true) //If the move is valid it will first store the Computer's side (X or O) to the selected place value
        {
        bool checkBoardOk = boardNotFull(userSide); // Checks to see if the board is not full
        bool checkAWinner = aWinner(); // Checks to see if there is not a winner yet

        displayUpdatedBoard(); // It will then display the board so the user can see the new move computer made
            if (checkAWinner == true) // If it was a winning move then it will return back to the "main" and display the winner
            {
            theWinner(getCompSide());
            }

            else if ((checkAWinner == false) && (checkBoardOk == true))
            {
            playerMove ();
            }
        }

        else // If it is not a valid move then computer will get to go and try again
        {
        computerMove();
        }
//}

//else // If it is not a smart move then it will try to find elsewhere to go
//{
//computerMove();
//}

}


void tictactoe::playerMove() //Function that processes player's turn
{
int x;
int y;
    cout << "It's your turn!" <<endl;
    cout << "\nPlease enter which Row you'd like to play in. \nYou can choose Row 0, Row 1, or Row 2." <<endl;
    cin >> x;
    cout << "\n\nPlease enter which Column you'd like to play in. \nYou can choose Column 0, Column 1, or Column 2." <<endl;
    cin >> y;

    if ((x > 2) && (y > 2) ) //Validate that the user didn't enter a number greater than 2
    {
    cout << "You must enter 0, 1, or 2 for both the Row and Column" <<endl;
    playerMove();
    }

        if (validMove(getUserSide(), x, y) == true) //If the move is valid it will first store the User's side (X or O) to the selected place value
        {
        bool checkBoardOk = boardNotFull(compSide); // Checks to see if the board is not full
        bool checkAWinner = aWinner(); // Checks to see if there is not a winner yet

        displayUpdatedBoard(); // It will then display the board so the user can see the new move

            if (checkAWinner == true) // If it was a winning move then it will return back to the "main" and display the winner
            {
            theWinner(getUserSide());
            }

            else if ((checkAWinner == false) && (checkBoardOk == true)) // If it is not a winning move then computer will get to go
            {
            cout << "\n\nComputer's Turn!" <<endl;
            computerMove();
            }
        }

        else
        {
        cout << "\n"<< getName() << " please make a valid move." <<endl;
        displayUpdatedBoard(); // Displays the updated board before the player make their move
        playerMove(); // Calls back the same player function so the player can try to make another move
        }
}

bool tictactoe::validMove (char someMove, int x, int y) //Determines if a given move is valid and if it isn't it asks the user for another move, if it is it sets the given move the user's/computer's selected place value
{
    if (updatedBoard[x][y] == '_')
    {
    updatedBoard[x][y] = someMove; // If that move is a blank space it replaces it with X or O depending on who is making the move, if the player was X, then it will place an X there.
    return true;
    }

    else
    {
    return false;
    }
}


bool tictactoe::aWinner() // Determine if there are 3 Xs or 3 Os that are together in a row, column, or diagonally after the turn
{
char gameWinner; // Character that stores the value for the winner of the game "X" or "O"

// If statement that checks the first diagnol from left to right are all the same to determine the winner
if ((updatedBoard[0][0] == updatedBoard[1][1]) && (updatedBoard[1][1] == updatedBoard[2][2]) && (updatedBoard[0][0] != '_' ))
    {
    gameWinner = updatedBoard[1][1];
    //theWinner(gameWinner);
    return true;
    }
// If statement that checks the first diagnol from right to left are all the same to determine the winner
else if ((updatedBoard[0][2] == updatedBoard[1][1]) && (updatedBoard[1][1] == updatedBoard[2][0]) && (updatedBoard[0][2] != '_' ))
    {
    gameWinner = updatedBoard[1][1];
    //theWinner(gameWinner);
    return true;
    }

// Else statement that checks if the values of a row or column are all the same to determine the winner
else
    {
int row; //Dummy variables for loop to search in row
int column; //Dummy variables for loop to search in column

    for (row=0; row < 3;row++ ) //Searches each row to see if a row's columns' values are equivalent
        {
            if ((updatedBoard[row][0] == updatedBoard[row][1]) && (updatedBoard[row][1] == updatedBoard[row][2]) && (updatedBoard[row][1] != '_' ))
            {
            gameWinner = updatedBoard[row][0]; // Stores if X or O is the winning value
            //theWinner(gameWinner); // Uses that X or O to determine if computer won or the user
            return true;
            }

        }

    for (column=0; column < 3; column++) //Searches each column to see if a column's rows' values are equivalent
        {
            if ((updatedBoard[0][column] == updatedBoard[1][column]) && (updatedBoard[0][column] == updatedBoard[2][column]) && (updatedBoard[0][column] != '_' ))
            {
            gameWinner = updatedBoard[row][column];// Stores if X or O is the winning value
            //theWinner(gameWinner); // Uses that X or O to determine if computer won or the user
            return true;
            }
            else
            {
            return false;
            }
        }
    }
}

// Will make the computer play smart depending on the board
//bool tictactoe::playSmart(char theUserSide, int x, int y) //Determines if this is a smart move
//{
//char tempBoard[3][3];
//
//
//    for (int v=0; v < 3; v++)
//    {
//        for (int w=0; w <3; w++)
//        {
//            {
//            tempBoard[v][w] = updatedBoard[v][w];
//            }
//        }
//
//    }
//
//tempBoard[x][y] = theUserSide;
//
//    if ( (x == 1) && (y == 1)) // If computer plays 1,1 then it's playing in the center
//    {
//
//        // Check if the user has a possible diagonal left to right win, then computer must play in the middle
//        if ( ( (tempBoard[0][0] == theUserSide) || (tempBoard[1][1] == theUserSide) || (tempBoard[2][2] == theUserSide)  ) && ( (tempBoard[0][0] == tempBoard[2][2]) || (tempBoard[1][1] == tempBoard[0][0]) || (tempBoard[1][1] == tempBoard[2][2]) ) && (tempBoard[1][1] == '_')  )
//        {return true;}
//
//        // Check if the user has a possible diagonal right to left win, then computer must play in the middle
//        else if ( ( (tempBoard[0][2] == theUserSide) || (tempBoard[1][1] == theUserSide) || (tempBoard[2][0] == theUserSide) ) && ( (tempBoard[0][2] == tempBoard[2][0]) || (tempBoard[0][2] == tempBoard[1][1]) || (tempBoard[1][1] == tempBoard[2][0]) ) && (tempBoard[1][1] == '_')  )
//        {return true;}
//
//        else
//        {
//        for (int v = 0; v < 3; v++)
//        {
//            for (int w = 0; w < 3; w++)
//            {
//            if ( (v != 1) && (w != 1))
//                {
//                if (tempBoard[v][w] = tempBoard[x][y])
//                    {return true;}
//                }
//            }
//        }
//        }
//    }
//
//
//    else
//    {
//            int row = x; // Searches all possibilities of that row to see if the user would win with that move
//                if ( ( (tempBoard[row][0] == theUserSide) &&  ( (tempBoard[row][1] == theUserSide) || (tempBoard[row][2] == theUserSide) ) )   ||    ( (tempBoard[row][1] == theUserSide) &&  ( (tempBoard[row][0] == theUserSide) || (tempBoard[row][2] == theUserSide) ) ))
//                    {
//                    return true;
//                    }
//
//                else
//                    {
//
//                    int column == y; // Searches all possibilities of that column to see if the user would win with that move
//                    if ( ( (tempBoard[0][column] == theUserSide) &&  ( (tempBoard[1][column] == theUserSide) || (tempBoard[2][column] == theUserSide) ) )   ||    ( (tempBoard[1][column] == theUserSide) &&  ( (tempBoard[0][column] == theUserSide) || (tempBoard[2][column] == theUserSide) ) ))                    }
//                        {
//                        return true;
//                        }
//
//
//    }



    // Check if the user has a possible diagonal left to right win, then computer must play in the middle
//    if ( (tempBoard[0][0] == theUserSide) && (tempBoard[0][0] == tempBoard[2][2]) && (tempBoard[1][1] == '_')  )
//      {
//      if ( (x == 1) && (y ==1))
//        {return true;}
//        else
//            {return false;}
//      }
//
//    // Check if the user has a possible diagonal right to left win, then computer must play in the middle
//    if ( (tempBoard[0][2] == theUserSide) && (tempBoard[0][2] == tempBoard[2][0]) && (tempBoard[1][1] == '_')  )
//      {
//      if ( (x == 1) && (y ==1))
//        {return true;}
//        else
//            {return false;}
//      }
//
//    // Check if the user has a possible row win, then computer must defend
//    for (v = 0; v < 3; v++)
//    {
//    if ( (tempBoard[v][0] == theUserSide) && (tempBoard[v][0] == tempBoard[v][1]) && (tempBoard[v][2] == '_') )
//      {
//      if ( (x == v) && (y == 2))
//        {return true;}
//        else
//            {return false;}
//      }
//
//    if ( (tempBoard[v][0] == theUserSide) && (tempBoard[v][0] == tempBoard[v][2]) && (tempBoard[v][1] == '_') )
//      {
//      if ( (x == v) && (y == 1))
//        {return true;}
//        else
//            {return false;}
//      }
//    }
//
//
//|| ( (tempBoard[0][0] == tempBoard[0][2]) && (tempBoard[0][1] == '_') )
//}


bool tictactoe::boardNotFull(char theSide) // Determine if the board is not full, that means there is still one "_", Also captures in the side which is playing "X" or  "O"
{
int blankCount=0; //Counter for available blank spaces in the game
int x; // Temp storage variable for the row
int y; // Temp storage variable for the column

    for (int row=0; row < 3; row++) // 2 for loops which go through the rows and column to search for  blank spaces.
        {
            for (int column=0; column < 3; column++)
                {
                if (updatedBoard[row][column] == '_') // if the row and column  is blank, then it will store that location to x and y and count 1 for "blankCount"
                    {
                        blankCount = blankCount + 1;
                        x = row;
                        y = column;
                    }
                }
        }

    if (blankCount > 1) // If there are more than 1 blank space then it will resume back to that player, either Computer or the User and the game will continue
    {
        return true;
    }
    else if ((blankCount == 1) && (aWinner()==false)) //If there is only one blank space and there is no winner, then it will automatically fill in that blank space with the opposite user which will make the game over
    {
        cout << "\nLooks like there is only space left to move! it will be automatically filled" <<endl;
        updatedBoard[x][y] = theSide;
        return false;
    }

}


void tictactoe::theWinner(char gameWinner) // Sets the winner of the game to either Computer or the user who's playing and prints out their name
{

string winner; // String that stores the winner either computer or the user

if (gameWinner == compSide) //Sets the winner value to computer
    {
    winner = "Computer";
    cout << "Sorry. Computer Won:(." <<endl;
    }
else
    {
    winner = getName(); //Sets the winner value to the user's name
    cout <<"YOU WON!" <<endl;
    }
}

//Destructors
//    ~void tictactoe::setName ()
//    {
//        delete uN;
//    }
//    ~void tictactoe::setUserSide()
//    {
//        delete compSide;
//        delete userSide;
//    }
//
//    ~void tictactoe::makeMove(int comp)
//    {
//        delete comp;
//    }
//    ~void tictactoe::theWinner(char gameWinner)
//    {
//        delete winner;
//    }
//    ~void tictactoe::displayUpdatedBoard()
//    {
//        delete[] R0;
//        delete[] R1;
//        delete[] R2;
//        delete[] R3;
//    }
