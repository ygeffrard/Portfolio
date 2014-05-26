/******************************************************************************
                                YARLEY GEFFRARD
                                Binary Search Tree
                                bitreemain.cpp

Title : bitreemain.cpp
Author : Yarley Geffrard
Created on : May 12th, 2014


Description : This program creates a binary tree based on kingdom of species
which is constructed on their based upon their relation. The name and score
of the specie is given from a file on the command line ("./program filename.txt)
each specie is actually a node and vice versa. Each specie's information can
be accessed from their nodes(which is a pointer(an address in memory)).
1.  The program reads this file and stores each item it reads properly into a
    tree so that each specie is linked with its score in one node
    (Example. Node->name, Node->score)
    All the nodes are placed inside a storage (which in our case is queue)
2.  The program then sort all the nodes inside the storage by their score,
    from lowest to greatest (the lowest will be at the front).
3.  We now construct a tree to link each item to each other as follows
    A. Inside the storage of all our nodes we find the first 2 child species
       which are closest to each other, that's determined by their scores.
       The species with the closes scores are joined together to make a new
       hybrid specie as the parent of these 2 species.
    B. The left child of the new hybrid is the lower scored of the 2 child
       species. The right child of the new hybrid is the lower scored of the 2
       child species. The parent of the new hybrid is NULL, which means it has
       no parent. The name of this new hybrid is the concatenation of the
       first child and the second child(Written as "(first child, second child)")
       The score of the new hybrid is the average score of both child species
    C. After creating this new specie we remove both child species from our
       storage and insert this new specie in our storage
    D. This process A-C repeats until we only have one element left in our
       storage which is the ultimate parent of all the trees, it is the "root"
       that can reproduce all the children inside of the tree. It will be
       the hybrid that has all the characteristics of the children used.
4.  We can access this "root" and data by kingdom_bitree, it's information is
    private, and it is a node whose parent is NULL.

Purpose: Create a binary tree of "kingdom of species" which is built upon
their scores to determine the closeness of their relationship to each other

Usage : This program will only properly execute with a file on the commandline
in the format (./program filename.txt). This filename.txt mus consist of
organism's names followed by their scores. Will read through the file and
construct a tree based upon this file, and output its root which will be
a hybrid specie composed of all the organisms that were given in the file.
The output will be presented in balanced parentheses format of the closesness
of their scores to each other, which determines their relationship in the kingdom
Ex.. ((species1, species2),species3)


Build with : g++ -c bitree.cpp
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include "bitree.h"

using namespace std;

template<class T>
bitree<T>::bitree()
{
    //Constructor
    //cout <<"LIFE KINGDOM - BINARY TREE CONSTRUCTOR"<<endl;
}


/*Function which opens the file and place each species and its score into a queue.*/
template<class T>
void bitree<T>::readFile(queue<treeBranch*>& thedata, const char* input)
{
treeBranch *leaf; //leaf to be setup in a tree of type "treeBranch"
T tempScore; //Hold temporary score

    ifstream thefile;
    thefile.open(input); //Reads from the file "numbers.txt" to import into the program
    //Checks to see if file opened correctly
    if ( !thefile.is_open() ){
      cout<<"Unable to open. Please try again.\n"<<endl;
      exit(EXIT_FAILURE);
    }
    else {
    string currdata; //Temporary string to read each item it finds in the file
        // While loop that will iterate through the file and push each name followed by a number into a temp vector
        while(thefile.good())
        {
            thefile >> currdata;
            if (!thefile) break; //If there isn't any new things to read, then it will break out of the forloop
            all_leaves.push_back(currdata); //Push each thing item it finds into the "all_leaves" vector

        }
        thefile.close();//Closes the file
    }

    /**MY NOTE** -> POINTERS ARE PUSHED INTO THE QUEUE AND ADDRRESSES ARE STORED, THEREFORE SHOULDN'T DELETE POINTERS*/
    //For all the species and its scores found it will create a "leaf" node to be pushed into a queue that will later be setup into a tree
    for (unsigned x=0;x<all_leaves.size();x+=2){
        tempScore = atof((all_leaves[x+1]).c_str());

        //If the score is greater then 0 then it will execute creating this new leaf, if not it is simply skipped
        if(tempScore > 0){
        leaf = new treeBranch; //Initializes a new treeBranch each time to be pushed into our data queue
        leaf->name = all_leaves[x]; //Every even index is a name
        leaf->score = tempScore; //Every odd index is a number, which must be converted from a string

        leaf->left = NULL; //We don't know what the left leaf will be so we set its value to NULL
        leaf->parent = NULL; //We don't know what the parent leaf will be so we set its value to NULL
        leaf->right = NULL; //We don't know what the right leaf will be so we set its value to NULL
        thedata.push(leaf); //push each leaf into our "thedata" queue to be setup into a tree
        }

        //This is just in case an organism name's is written and not followed by a number
        //The next value in our vector should be the next organismn string, which would be our current index - 1, since our iteration increases by 2
        //we would simply account for that making x the iteration
        else{
        x = x-1;
        }
    }
    all_leaves.clear();//Clearsvector the vector to free up some space in memory
}


/*Function that will construct the tree and store the smallest scored specie to the left and largest to the right until it creates a root*/
template<class T>
void bitree<T>::constructTree(queue<treeBranch*>& thedata)
{
    sort_kingdom(thedata); //"thedata" queue will be sorted since the data is passed by reference
    treeBranch *new_specie;
    treeBranch *leafL;
    treeBranch *leafR;

    //A base case for the previous score to be used to find our closest species will be the our largest scored specie, since our "thedata" has been sorted, the largest scored specie will be the last(back of "thedata")
    T previousScore = thedata.back()->score;

    //While "thedata" queue is not 1 which means, the only left is our root, this process continues
    while(thedata.size() > 1)
    {
        leafL = new treeBranch; //Creates a new left leaf Node to be used
        leafR = new treeBranch; //Create a new right leaf Node to be used
        new_specie = new treeBranch; //Create a new_specie hybrid to be constructed

        closestSpecies(thedata, leafL, leafR, previousScore); //finds the species with the smallest difference in score apart
        leafL->parent=new_specie; //the parent of the left leaf is this new_specie
        leafR->parent=new_specie; //the parent of the right leaf is this new_specie
        new_specie->name = "("+leafL->name + ","+leafR->name+")"; //the name of this new specie is the concatenation of the (left leaf, right leaf)
        new_specie->score = (leafL->score + leafR->score)/2; //the score of this new specie is the average of the 2 leaves
        new_specie->left = leafL; //the left leaf of the new specie is the leaf(leafL) given
        new_specie->right = leafR; //the right leaf of the new specie is the right(leafR) given
        new_specie->parent = NULL; //this new specie will have no parent, so we set that value to NULL
        //Removes both left and right leaves from "thedata" queue
        removeLeaf(thedata, leafL);
        removeLeaf(thedata, leafR);

        //push this new hybrid specie(new_specie) composed of the 2 leaves back into "thedata" queue
        thedata.push(new_specie);
    }
    //the front "thedata" queue is the tree which will be the ultimate root hybrid tree
    kingdom_bitree = thedata.front();
}


/*copies a queue so that they each have different addresses*/
template<class T>
queue<treeBranch*> bitree<T>::copy_a_queue(queue<treeBranch*> queue_to_copy)
{
    queue <treeBranch*>copy_of_queue;
    //While the size of the queue it has to copy is greater than 0 it must remove the front element of that queue and place it into our new queue
    while(queue_to_copy.size() > 0)
    {
        copy_of_queue.push(queue_to_copy.front());
        queue_to_copy.pop();
    }
    return copy_of_queue;
}


/*Given a queue "thedata" will find the specie with the lowest score*/
template<class T>
treeBranch* bitree<T>::findSmallestScore (queue<treeBranch* > thedata)
{
treeBranch *smallest; //Temporary Node to hold the specie with the lowest score
treeBranch *tester; //Tester Node that will hold the front "thedata" queue
    smallest=thedata.front();

    //While "thedata" queue is not empty it will compare each element in "thedata" queue and return the one with the lowest score
    while(thedata.size() > 0){
    tester = new treeBranch;
    tester = thedata.front();
        if ( (tester->score) < (smallest->score) )
        {
            smallest = new treeBranch;
            smallest = tester; // if it finds another node's score in "thedata" queue lower than our current smallest, then that becomes the node with the lowest score
        }
    thedata.pop();
    }
    return smallest; //returns the Node with the lowest score
}


/*Removes a leaf from a given queue*/
template<class T>
void bitree<T>::removeLeaf(queue<treeBranch*>& thedata, treeBranch *leaf_to_remove)
{
    queue<treeBranch*> update_thedata; //will store a new queue with the element removed

    //While the queue "thedata" size is greater than 0 will pop the front of "thedata", and push it to a temp queue "update_thedata", as long as the front of "thedata" is not equal to the leaf that was removed
    while(thedata.size() > 0)
    {
        if(thedata.front()  != leaf_to_remove)
        {
        //push the front of "thedata" queue into our updated queue which is the "update_thedata" queue
        update_thedata.push(thedata.front());
        }
        thedata.pop();
    }
    //Our updated queue will now equal to our original queue, which is passed by referenced to the function that called it
    thedata = update_thedata;
}


/*Sorts a given queue from lowest scored to Greatest scored*/
template<class T>
void bitree<T>::sort_kingdom(queue<treeBranch*>& thedata)
{
    treeBranch *tempLeaf; //Temporary leaf to hold the specie with the lowest score

    //while the queue "thedata" is not empty, will place the smallest score leaf into another queue which will be sorted
    while(thedata.size() > 0)
    {
        tempLeaf = new treeBranch; //Creates a new tempLeaf
        tempLeaf = findSmallestScore(thedata); //Holds the specie with the lowest score
        sorted_kingdom.push(tempLeaf); //Pushes it into a list which will automatically be sorted since it pushes the smallest value through each iteration of the while
        removeLeaf(thedata, tempLeaf); //Removes the temptree from "thedata" queue which holds our unsorted nodes
    }
    thedata = copy_a_queue(sorted_kingdom);
}



/*finds the closest species to each other in "thedata" queue*/
template<class T>
void bitree<T>::closestSpecies(queue<treeBranch*> thedata, treeBranch* &leftLeaf, treeBranch* &rightLeaf, T smallestDifference)
{
    treeBranch *first_leaf = new treeBranch; //Creates a leaf to be used
    treeBranch *second_leaf = new treeBranch; //Creates a second leaf to be used to compare to the first
    T currentDifference; //Will hold the current difference of scores of 2 leaves

    first_leaf = thedata.front(); //the first leaf in our original "thedata" queue passed from into the function
    thedata.pop(); //Since it is comparing the first element to the others the first(front element) is no longer in our "thedata" queue

    //If "thedata" queue's size is greater than 0, after popping one element from "thedata" queue then, there will be another leaf to compare our first leaf to
    if(thedata.size()>0)
    {
    queue<treeBranch*> temp_data = thedata; //"thedata" queue without the first element will be needed for the next recursion of this process
        while (thedata.size()>0)
        {
            second_leaf = thedata.front(); //The second leaf in our original "thedata" queue passed from into the function
            currentDifference = fabs( (first_leaf->score) - (second_leaf->score) );
            // If the currentDifference it found is smaller than the smallestDifference it found before, then the currentDifference is now the smallestDifference
            if (currentDifference < smallestDifference)
            {
                //The smaller scored leaf always has to be the left of any tree
                //The larger scored leaf always has to be the right of any tree
                if ( (first_leaf->score) < (second_leaf->score) )
                {
                    leftLeaf = first_leaf;
                    rightLeaf = second_leaf;
                }
                else
                {
                    rightLeaf = first_leaf;
                    leftLeaf = second_leaf;
                }
                smallestDifference = currentDifference; //The current Difference will now be the smallest difference in "thedata" queue
            }
            thedata.pop(); //Leaves the other elements it must compare them to inside "thedata" queue
        }
        //Calls the function recursively to find if there is an even smaller difference in the remaining "thedata" queue
        closestSpecies(temp_data, leftLeaf, rightLeaf, smallestDifference);
    }
}


/*Function that will output the tree's data as a string output in the language of balance parentheses
//Should be in the form (((ape,human),monkey),((tiger,lion),elephant)))*/
template<class T>
void bitree<T>::outputTree(treeBranch* Node){
    //Base case -> if the Node is a leaf, it won't have any left or right child, which means its left & right child will be NULL
    if ((Node->left == NULL) && (Node->right == NULL))
    {
        cout <<Node->name;
    }

    //The recursion process continues for both the left child and right child
    else
    {
        cout <<"("; //Before the program check the left node we add an "(" open parentheses
        outputTree(Node->left); //Repeats the process making the left child the current tree to be processed
        cout <<","; //In between the left child and the right child is seperated a ","
        outputTree(Node->right); //Repeats the process making the right child the current tree to be processed
        cout <<")"; //After the program check the right node we add a ")" close parentheses
    }
}

//Destructor
template<class T>
bitree<T>::~bitree()
{
    //Destructor
    while (!sorted_kingdom.empty())
    {
        delete sorted_kingdom.front(); //deletes each node that's in "sorted_kingdom" queue
        sorted_kingdom.pop(); //Also remove them from "sorted_kingdom" queue, which is our storage
    }
    delete kingdom_bitree; //deletes the node with our root
}
