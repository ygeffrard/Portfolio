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


Build with : g++ -c bitreemain.cpp
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "bitree.h"
#include "bitree.cpp" //Needed this so I don't get the undefined error message

using namespace std;

int main(int argc,char *argv[])
{
    if (argc!= 2){
        cout <<"Invalid format or file input. Need to be:\n"<<argv[0]<<" fileinput.txt\n"<<endl;
    }

    else{
    bitree <double>kingdom;// kingdom of class binary tree (which is titled "bitree")
    queue<treeBranch*>dataFile; //storage that will eventually carry a queue which has datafiles of the species and their score into a queue

    //Reads the datafile stores it into a queue
    kingdom.readFile(dataFile, argv[1]);
    //With the dataFile it will now make a binaryTree with all the leaves from the dataFile
    kingdom.constructTree(dataFile);

    //cout << kingdom.getRoot_Name() <<endl; //Easily output the name of the root of the tree after it has been constructed
    cout << kingdom.getRoot_Score() <<endl; //Easily output the score of the root of the tree after it has been constructed
    kingdom.printTree_NameBalPar(); //Outputs the tree in the language of Balance Parentheses
    }
}
