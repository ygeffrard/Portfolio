/****************************************************************************
                                YARLEY GEFFRARD
                                SUDOKU BOARD
                                sudokumain.cpp Implementation


Title : sudoku.cpp
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

Build with : g++ -c sudoku.cpp
******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "sudoku.h"

using namespace std;

sudoku::sudoku() //constructor
{
char fullRow[] = "_________"; //Initial char array that is blank with a size of 9

    int x, y; // Dummy values to set initial values for row and column of updatedBoard to blank space '_'

    //Sets initial values on the board to be random generated numbers between 0 through 9 and will store it to "theBoard" private class string vector
    for (x=0; x < 9; x++)
        {
        for (y=0; y < 9; y++)
            {
            board[x][y] = char((rand()%10+0)+ '0'); //Generate random number 0-9 and store it to the char array "board"
            fullRow[y] = board[x][y]; // Stores each row generated in the board to a char called "fullRow"
            }
            theBoard.push_back(fullRow); // Stores each row into the string vector "theBoard"
        }
}

void sudoku::displayBoard() // Displays initial default Tic Tac Toe Board
{
int x, y;
    char R00[] = "\n\n  (0,0) 0 1 2 3 4 5 6 7 8\n";
// Row with Column coordinates
    char R0[] = "   R0   _|_|_|_|_|_|_|_|_\n";
// 1st Row with Row coordinates
    char R1[] = "   R1   _|_|_|_|_|_|_|_|_\n";
// 2nd Row with Row coordinates
    char R2[] = "   R2   _|_|_|_|_|_|_|_|_\n";
// 3rd Row with Row coordinates
    char R3[] = "   R3   _|_|_|_|_|_|_|_|_\n";
// 4th Row with Row coordinates
    char R4[] = "   R4   _|_|_|_|_|_|_|_|_\n";
// 5th Row with Row coordinates
    char R5[] = "   R5   _|_|_|_|_|_|_|_|_\n";
// 6th Row with Row coordinates
    char R6[] = "   R6   _|_|_|_|_|_|_|_|_\n";
// 7th Row with Row coordinates
    char R7[] = "   R7   _|_|_|_|_|_|_|_|_\n";
// 8th Row with Row coordinates
    char R8[] = "   R8   _|_|_|_|_|_|_|_|_\n";
// 9th Row with Row coordinates

     //For loop that gets the information from the numbers in the board to display to the user
     for (x = 8, y=0; x < 25, y<9; x= x+2, y++)
        {
            R0[x] = theBoard[0][y];
            R1[x] = theBoard[1][y];
            R2[x] = theBoard[2][y];
            R3[x] = theBoard[3][y];
            R4[x] = theBoard[4][y];
            R5[x] = theBoard[5][y];
            R6[x] = theBoard[6][y];
            R7[x] = theBoard[7][y];
            R8[x] = theBoard[8][y];
        }

    cout << R00 << R0 << R1 << R2 << R3 << R4 << R5 << R6 << R7 << R8 << endl; //Displays the board
}

// function that stores the vector of strings received from the file and stored into the private member of class "sudoku"
void sudoku::setListNumbers(vector <string> x)
{
    numberList = x;
}

void sudoku::findAllNumbersInBoard()
{
//For each number in the number list received from the file, the program will check if it's on the board.
for (int eachNumber = 0; eachNumber < (numberList.size()-1); eachNumber ++)
    {
        if (findNumbersOnBoard(eachNumber) == true) //If the number is on the list then it will store it to the vector "numbersOnBoard" which holds all the numbers on the board
        {
            cout << "All Done!"<< numberList[eachNumber] <<"is on the board" <<endl;
            numbersOnBoard.push_back(numberList[eachNumber]);
        }
        else
        {
            cout << numberList[eachNumber] << "\nis not on the board\n" <<endl;
        }
    }
}

void sudoku::countNumTimes()
{
string numToString; //string th
int theCounter;
string multiCoordinates;

//For each number in the number list received from the file, the program will check if it's on the board.
for (int eachNumber = 0; eachNumber < (numberList.size()-1); eachNumber ++)
    {
        theCounter = findNumbersOnBoard(eachNumber);
        if (theCounter > 0) //If the number is on the list then it will store it to the vector "numbersOnBoard" which holds all the numbers on the board
        {
            //cout << "All Done!"<< numberList[eachNumber] <<"is on the board" <<endl;
            numbersOnBoard.push_back(numberList[eachNumber]);
            numToString = char(theCounter + '0');
            numberCount.push_back(numToString);
            //cout << currentCoord[1] <<endl;
        }

//        else if (theCounter > 1)
//        {
//            numbersOnBoard.push_back(numberList[eachNumber]);
//            numToString = char(theCounter + '0');
//            numberCount.push_back(numToString);
//
//            for (int coordIndex = 0; coordIndex < theCounter; coordIndex ++)
//            {
//                //theCoord = currentCoord[coordIndex];
//                multiCoordinates.push_back('1');
//                multiCoordinates.push_back('&');
//            }
//
//            coordNumbersOnBoard.push_back(multiCoordinates);
//
//        }

        else //That number isn't on the board
        {
            //cout << numberList[eachNumber] << "\nis not on the board\n" <<endl;
        }
    }
}

// Will start the process of find the numbers that are on the number list and is on the gameboard, the initial value is 0 because its the first index of the "storeNumbers" vector
int sudoku::findNumbersOnBoard(int i)
{
int counterDuplicates = 0;
int row, col;
int sizeOfNumList = numberList.size()-1;

string selectedNum; // string that will store the selected number into a string
        //For loop will iterate through both x and y of "theBoard" string vector to find a match
        for (row=0; row <= 8; row++)
            {
            for (col=0; col <= 8; col++)
                {
                 if (numberList[i][0] == theBoard[row][col]) //For each number on the list the program will check if the first digit matches another digit on the board
                    {
                        selectedNum = numberList[i]; //sets the string "selectNum" to be the full number of that current number it found on the list to matchup
                        if (checkFullNumber(selectedNum, row, col, i)) //If after checking the full it is on the board
                            {
                            counterDuplicates++;
                        //cout << "Counter Duplicate of " << selectedNum << "--> "<< counterDuplicates;
                            }
                    }
                 }
             }
        return counterDuplicates;
            //i++; //Will go to the next number on the list if that current number isn't on the board after irating through the entire board
}

//bool function that checks if the full number on the list received from the file matches any number on the gameboard using the algorithm
bool sudoku::checkFullNumber(string num, int row, int col, int CurrentIndex)
{
        if (nextDigit(num, row, col, CurrentIndex)) //Will to see if the next digit on the current number it is checking is true
        {
        return true;
        }
        else
        {
        return false;
        }
}

//bool function that will check for the next number recursively until it reaches the end or get stuck on a part of the algorithm
bool sudoku::nextDigit(string searchNum, int x, int y, int currentIndex)
{
int strand = 1; // the next strand will always be 1 because it is the second number from the current digit it's checking for
bool foundANum = true; // bool value to store true if it has found the next digit to match vertically, horizontally or diagnolly

int theSize = 1; //Size of the number of digits of the current number being processed is initially 1 to count for the first digit

vector <string> locationsToCross; //Array of int to store the locations that are to be crossed out
int locationsArray[searchNum.size()][2]; //Array that will store the the row and column location of each next digit found
string originalNumber = searchNum; //String vector that will revert back all the locations if the entire number isn't a match

locationsArray[0][0] = x; // Sets the first digit row location
locationsArray[0][1] = y; // Sets the first digit of the column location

int location=1; //Index for locations that will be crossed out

//tempLocationsArray.push_back(searchNum[0]) // Saves the inital firs digit value
theBoard[x][y] = '-'; //Crosses out the initial first digit location to be blank

while (foundANum)
    {
        if ( ((x+1)<9) && (searchNum[strand] == theBoard[x+1][y]) ) //check for the digit on the right
        {
            x = x+1;
            foundANum = true;
        }

        else if ( ((y+1)<9) && (searchNum[strand] == theBoard[x][y+1]) ) //check for the digit on top
        {
            y = y+1;
            foundANum = true;
        }

        else if ( ((x+1)<9) && ((y+1)<9) && (searchNum[strand] == theBoard[x+1][y+1]) ) //check for the digit on the top right
        {
            x = x+1;
            y = y+1;
            foundANum = true;
        }

        else if ( ((x-1)>=0) && (searchNum[strand] == theBoard[x-1][y]) ) //check for the digit to the left
        {
            x = x-1;
            foundANum = true;
        }

        else if ( ((y-1)>=0) && (searchNum[strand] == theBoard[x][y-1]) ) //check for the digit below
        {
            y = y-1;
            foundANum = true;
        }

        else if ( ((x-1)>=0) && ((y+1)<9) && (searchNum[strand] == theBoard[x-1][y+1]) ) //check for the digit on the top left
        {
            x = x-1;
            y = y+1;
            foundANum = true;
        }

        else if ( ((x-1)>=0) && ((y-1)>=0) && (searchNum[strand] == theBoard[x-1][y-1]) ) //check for the digit on the bottom left
        {
            x = x-1;
            y = y-1;
            foundANum = true;
        }

        else if ( ((x+1)<9) && ((y-1)>=0) && (searchNum[strand] == theBoard[x+1][y-1]) ) //check for the digit on the bottom right
        {
            x = x+1;
            y = y-1;
            foundANum = true;
        }

        //If it's unable to find a next number then it will return false and unable to find the next number
        else{
            foundANum = false; //No necessary but "foundANum" being false means that next digits is not on the board
            int rowLoc; //iterator for the row location
            int colLoc; //iterator for the column location

                for (int digits =0; digits < theSize; digits++)
                {
                rowLoc = locationsArray[digits][0]; //stores the location of the row to the temporary "rowLoc" variable
                colLoc = locationsArray[digits][1]; //stores the location of the column to the temporary "colLoc" variable
                theBoard[rowLoc][colLoc] = originalNumber[digits]; //Crosses out that location to be blank
                }
            return false;
            break;
        }

        if (foundANum) // if it has found a next digit that's a match then it will check if that was not the last digit in the number
        {
            locationsArray[location][0] = x; //Array that stores each row coordinate it finds
            locationsArray[location][1] = y; //Array that stores each column coordinate it finds
            theBoard[x][y] = '-'; //Crosses out that location to be blank

            searchNum.erase (0,1); //Erases first digit of the number to continue the process
            location++;
            theSize++;
            if (searchNum.size() <= 1) //If that was the last number then it will return true
            {
            locationToString(locationsArray, theSize, currentIndex); // Function that will store the coordinates of the full number that it has found
            return true;
            }
            // If it's not the last number then the function will reloop back to the while loop
        }
    }

}

//Function that will take a 2D array which has the coordinates of the current valid string that it found on the board
void sudoku::locationToString(int loTStr[][2], int sizeLoTStr, int i)
{
char numToStringx; //To hold x, row coordinates
char numToStringy; //To hold y, column coordinates
string numToString; //String that will store the the full coordinates

        //For each coordinate it will store the row and column value to the string "numToString"
        for (int coord = 0; coord < sizeLoTStr; coord ++ )
        {
        numToStringx = char((loTStr[coord][0])+ '0'); // Sets the row coordinate to a string
        numToStringy = char((loTStr[coord][1])+ '0'); // Sets the column coordinate to a string
        //The lines below will set - > (X,Y) for each coordinate to display for user
        numToString.push_back('(');
        numToString.push_back(numToStringx);
        numToString.push_back(',');
        numToString.push_back(numToStringy);
        numToString.push_back(')');
        }
    // The full coordinates and locations will be stored into private member string vector "currentCoord" which will match with the current valid number
    currentCoord.push_back(numToString);
}

sudoku::~sudoku()
{
    //deconstructor
    for (int x=0; x < 9;x++)
    {
        for(int y=0; y < 9;y++)
        {
            board[x][y]='\0';
        }
    }
    theBoard.clear();
    numberList.clear();
    numbersOnBoard.clear();
    currentCoord.clear();
    numberCount.clear();

}
