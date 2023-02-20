//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Michael Pritchard
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <iostream>
#include <time.h>
#include "BinarySearchTree.h"
#include "CSVparser.hpp"


using namespace std;

/*
This is a binary search tree data structure.  We have a node that contains a
bid and these nodes are connected to each other left and right depending on
the information in the bid. This tree has functions for adding nodes, printing
 the tree in order, removing nodes and search the tree.
*/

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDoublebst(string str, char ch);


/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
        
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    this->inOrder(root);
}


/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {
        root = new Node(bid);
    }
    else {
        this->addNode(root, bid);
    }
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    return NULL;
}
// Asks user for bidId then traverses the tree looking for the bidId then blanks out the bid
void BinarySearchTree::RemoveHelper() {

    Bid bid;
    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);
    
    // ------------------------------Re-implementation of Search----------------------
    string myBidId = bid.bidId;
    int bidIdint = stoi(myBidId);

    Node* currentNode = root;
    while (currentNode != nullptr) {
        int currentNodeBidId = stoi(currentNode->bids.bidId);

        if (bidIdint == currentNodeBidId) {
            currentNode->bids.amount = 0;
            currentNode->bids.fund = "";
            currentNode->bids.title = "";
            return;
        }

        if (bidIdint < currentNodeBidId) {
            currentNode = currentNode->left;
        }

        if (bidIdint > currentNodeBidId) {
            currentNode = currentNode->right;
        }

    }
    //------------------------------------------------------------------------------
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    this->removeNode(root, bidId);
}
// Asks the user for bidId before searching 
void BinarySearchTree::SearchHelper() {

    Bid bid;
    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);
        
    bid = Search(bid.bidId);
    if (!bid.bidId.empty()) {
        cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    }
    else {
        cout << "Bid Id " << bid.bidId << " not found." << endl;
    }

}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    int bidIdint = stoi(bidId);

    Bid bid;
    Node* currentNode = root;
    while (currentNode != nullptr) {
        int currentNodeBidId = stoi(currentNode->bids.bidId);

        if (bidIdint == currentNodeBidId) {
            bid = currentNode->bids;
            return bid;
        }

        if (bidIdint < currentNodeBidId) {
            currentNode = currentNode->left;
        }

        if (bidIdint > currentNodeBidId) {
            currentNode = currentNode->right;
        }
       
    }
        
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    int currentNodeId = stoi(node->bids.bidId);
    int toInsertId = stoi(bid.bidId);

    if (toInsertId < currentNodeId) {
        // Check to see if current node has a left child
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }

        else {
            addNode(node->left, bid);
        }
           
    }
    else {
        // Check to see if current node has right child
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }

        else {
            addNode(node->right, bid);
        }
        
    }
       
    
}

// Recursive Function
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->bids.bidId << " : " << node->bids.title << " | " << node->bids.amount << " | " << node->bids.fund << endl;
        inOrder(node->right);
    }
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBidbst(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
        << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    
}
// Gets the bid from the bst
Bid BinarySearchTree::getBidbst() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDoublebst(strAmount, '$');

    return bid;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDoublebst(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}
