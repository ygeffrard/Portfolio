/****************************************************************************
                                YARLEY GEFFRARD
                                SUDOKU BOARD
                                sudoku.h Interface


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

Build with : N/A
******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>

#ifndef SUDOKU_H
#define SUDOKU_H

using namespace std;

class sudoku
{
    public:
        sudoku(); //constructor that creates the original random values and sets them unto the board

        // Displays initial default Tic Tac Toe Board
        void displayBoard();
        //virtual ~sudoku();

        // function that stores the vector of strings received from the file and stored into the private member of class "sudoku"
        void setListNumbers(vector <string> x);

        // function that will get and print the list of numbers from the file
        void getListNumbers()
        {
            for (int i=0; i<numberList.size()-1; i++)
            {
            cout <<"   "<<i+1 << ".  "<< numberList[i] << endl;
            }
        }

        //For each number in the number list received from the file, the program will check if it's on the board.
        void findAllNumbersInBoard();

        //Funcion that will count the number of a times a number is shown after being crossed out
        void countNumTimes();

        // Will start the process of find the numbers that are on the number list and is on the gameboard, the initial value is 0 because its the first index of the "storeNumbers" vector
        int findNumbersOnBoard(int i);

        // bool function that checks if the full number on the list received from the file matches any number on the gameboard using the algorithm
        bool checkFullNumber(string selectedNum, int row, int col, int currentIndex);

        // Get and display the list of numbers that are both on the gameboard and on the list using the techniques of the algorithm
        void getNumbersOnBoard()
        {
            cout << "\n\nALL DONE! HERE ARE THE NUMBERS ON THE BOARD."<<endl;
            for (int nb=0; nb<(numbersOnBoard.size()-1); nb++)
            {
            //Displays both the numbers on the board and their coordinates
                cout <<"   "<<nb+1 << ".  "<< numbersOnBoard[nb] <<" is shown "<<numberCount[nb]<<" times."<<endl;
            }
//            cout << "The coordinates are as follow.\nTake into account the ones that are duplicated are shown beneath each other\n" << endl;
//
//            for (int coord=0; coord<(currentCoord.size()); coord++)
//            {
//                cout <<currentCoord[coord] <<endl;
//            }
//            displayBoard();
        }

        // Bool function that will check for the next number recursively until it reaches the end or get stuck on a part of the algorithm
        bool nextDigit(string z, int x, int y, int curIndex);

        //Function that will take a 2D array which has the coordinates of the current valid string that it found on the board
        void locationToString(int loTStr[][2], int sizeLoTStr, int currentIndex);

        ~sudoku();

    //protected:
    private:
        char board[9][9]; // char array that stores the original board with the random generated numbers
        vector <string> theBoard; // vector string that also has the original board which will be tampered with and crossed out
        vector <string> numberList; // vector string that has the numbers on the list received from the file
        vector <string> numbersOnBoard; // vector string that stores the numbers that are both on the list and on the board
        //vector <string> coordNumbersOnBoard; //Stores the coordinates to be displayed neatly to the user on this vector
        vector <string> currentCoord; // Stores the current coordination of the digits of the number that its has fully found
        vector <string> numberCount; //Counter that stores the counter that a specific number is displayed on the board
};

#endif // SUDOKU_H
