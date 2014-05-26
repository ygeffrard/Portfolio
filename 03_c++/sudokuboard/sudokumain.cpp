/****************************************************************************
                                YARLEY GEFFRARD
                                SUDOKU BOARD
                                sudokumain.cpp


Title : sudokumain.cpp
Author : Yarley Geffrard
Created on : February 26th, 2014
Description : Plays a search game on a "sudoku" board. Automatically fill the
gameboard of 9x9 Boxes with the numbers 0 through 9, the program will read
each line of numbers in a txt file, then use a recursive algorithm to
determine if the numbers in the file is in the board. If a number is used
it can't be used again. After going through all the numbers on the board it
will find which numbers in the file were found it will be stored in the program
then displayed for the user.

Purpose : Fill a 9x9 game board up with random numbers 0-9, then find set of numbers
in a file that's in the board diagnolly, verticaly and horizontally without a
number being used twice. Also will count how many times a number appeared with its coordinates

Usage : Find the set of numbers in a file that's in a gameboard of 9x9 and count how many times they appeared

Build with : g++ -c sudokumain.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "sudoku.h"

using namespace std;

int main()
{

    sudoku game; //declares object 'game' of class sudoku
    game.displayBoard(); // Displays the initial gameboard with random numbers generated in it

    ifstream theGame; //
    theGame.open("numbers.txt"); //Reads from the file "numbers.txt" to import into the program
    if(!theGame.is_open()) //If the game is unable to find the file then it will exit and display this error message
    {
        cout << "Unable to open the file. Goodbye!\nTry placing the file 'numbers.txt' in the same folder as your program."<< endl;
        exit(EXIT_FAILURE);
    }

    string currentNumber; //string that will store the current number
    theGame >> currentNumber; //to read from the file into the current number
    vector <string> storeNumbers; //String vector that will store the numbers read from the file
    storeNumbers.push_back(currentNumber); //Will store the first line to the "store numbers" vector

    while(theGame.good()) // While loop that will iterate through the object which came from the file and store the rest of the numbers to the "store numbers" vector
    {
        theGame >> currentNumber;
        storeNumbers.push_back(currentNumber);
    }

    game.setListNumbers(storeNumbers); // Will set the the "storeNumbers" vector to a private function to save in the program
    cout << "   List of numbers in the file:" <<endl;
    game.getListNumbers(); // Will display the list of numbers read from the file
//    game.findAllNumbersInBoard(); //Function that will find all the numbers on the board
    game.countNumTimes(); // Function that counts the number of times a number is show from the list on the board
//    game.findNumbersOnBoard(0); // Will start the process of find the numbers that are on the number list and is on the gameboard, the initial value is 0 because its the first index of the "storeNumbers" vector
    game.getNumbersOnBoard(); // Get and display the list of numbers that are both on the gameboard and on the list using the techniques of the algorithm

return 0;
}


/* My findings show that this program was able to find an average of
10 different numbers after running it a few times. These 10 numbers are
mostly the shorter length numbers and not the longer ones. The shortest
numbers are the ones that appeared a duplicate amount of times. My coordinates
are show beneath the findings of numbers.
*/
