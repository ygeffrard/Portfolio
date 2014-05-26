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


Build with : N/A
*******************************************************************************/

#ifndef BITREE_H
#define BITREE_H

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

//treeBranch which may have a parent, a left & right child, a name and its score
struct treeBranch
{
        treeBranch *parent; //Will hold the parent node of the node
        treeBranch *left; //Will hold the node of the left treebranch
        treeBranch *right; //Will hold the node of the right treebranch
        std::string name; //Will hold the organism's name
        double score; //Will hold the organism's score
        //treeBranch *prev; //Will be used to have the order of the unsorted list
};

template<class T>
class bitree
{
    public:
        bitree(); //Default constructor for the binary tree

        //function that reads and stores the information from the file into a queue of unsorted leaves to be sorted into a tree
        void readFile(std::queue<treeBranch*>&, const char*);
        /*function that builds the tree with subtrees whose scores are closest to each other*/
        //Each node will have 1.root 2.The 2 leaves (left & right) 3.the name 4.the score(average score of its subleaves)
        void constructTree(std::queue<treeBranch*>&);
        //copies a queue so that they each have different addresses
        std::queue<treeBranch*>copy_a_queue(std::queue<treeBranch*>);
        //Given a queue "thedata", it will find the specie with the lowest score
        treeBranch* findSmallestScore(std::queue<treeBranch*>);
        //Will return the name of root of a tree once it has been constructed
        std::string getRoot_Name(){
            return (kingdom_bitree->name);
        }
        //Will return the score root of a tree once it has been constructed
        T getRoot_Score(){
            return (kingdom_bitree->score);
        }
        //Will return the root of a tree once it has been constructed using Balance Parentheses Method
        void printTree_NameBalPar(){
            outputTree(kingdom_bitree);
            std::cout <<std::endl;
        }

        //Destrutor
        ~bitree();


    private:

        /**PRIVATE DATA**/
        //Vector that will store every element followed by its score all as leaves, meaning they're not setup as a tree yet
        std::vector <std::string> all_leaves;
        //The constructed binary tree will be stored in this "kingdom_bitree" queue
        treeBranch *kingdom_bitree;
        //The unconstructed binary tree will be store in this "sorted_kingdom" queue
        std::queue<treeBranch*> sorted_kingdom;

        /**PRIVATE FUNCTIONS**/
        //Removes a leaf from a given queue
        void removeLeaf(std::queue<treeBranch*>&, treeBranch *leaf_to_remove);
        //Sorts a given queue from lowest scored to Greatest scored
        void sort_kingdom(std::queue<treeBranch*>&);
        //finds the closest species to each other in "thedata" queue
        void closestSpecies(std::queue<treeBranch*>, treeBranch*&L, treeBranch*&R, T);
        //Function that will output the tree's data as a string output in the language of balance parentheses
        //Should be in the form (((ape,human),monkey),((tiger,lion),elephant)))
        void outputTree(treeBranch *Node);
};

#endif // BITREE_H
