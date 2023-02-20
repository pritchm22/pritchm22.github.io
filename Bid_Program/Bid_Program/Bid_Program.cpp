
//============================================================================
// Name        : Bid_Program.cpp
// Author      : Michael Pritchard
// Description : This file contains the 'main' function. Program execution begins and ends there.
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
#include "CSLinked_List.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "DataMiner.h"

using namespace std;
// An interactive menu program for parsing and loading bid data into 1 of 3 data structures
// (LinkedList, BinarySearchTree,HashTable) and performing basic data mining on the data

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

LinkedList bidList;
BinarySearchTree* bst;
HashTable* bidTable;
DataMiner* myDataMiner;

double strToDouble(string str, char ch);
// Helper function for loading data into LinkedList
void loadLinkedList(csv::Parser file) {
    cout << "You have selected Linked List" << endl;

    // Load into linked list
    
    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');
            
            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl; // Debugging Purposes

               // add this bid to the end
            bidList.Append(bid);
        }
     
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}
// The secondary menu, once the data structure has been chosen
void bidModifierMenu(int dsChoice) {
    int menuChoice = 0;

    while (menuChoice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> menuChoice;

        // Switch Statement
        switch (menuChoice) {
        case 1:
            if (dsChoice == 1) {

                Bid bid;
                bid = bidList.getBid();
                bidList.Append(bid);
                bidList.displayBid(bid);
            }
            else if (dsChoice == 2) {
                Bid bid;
                bid = bst->getBidbst();
                bst->Insert(bid);
            }
            else if (dsChoice == 3) {
                Bid bid;
                bid = bidTable->getBid();
                bidTable->Insert(bid);
            }

            break;

        case 2:
            if (dsChoice == 1) {
                bidList.PrintList();
            }
            else if (dsChoice == 2) {
                bst->InOrder();// bst is a bst pointer
            }
            else if (dsChoice == 3) {
                bidTable->PrintAll();
            }

            break;

        case 3:
            if (dsChoice == 1) {
                bidList.SearchHelper();
            }
            else if (dsChoice == 2) {
                bst->SearchHelper();
            }
            else if (dsChoice == 3) {
                bidTable->SearchHelper();
            }

            break;

        case 4:
            if (dsChoice == 1) {
                bidList.RemoveHelper();
            }
            else if (dsChoice == 2) {
                bst->RemoveHelper();
            }
            else if (dsChoice == 3) {
                bidTable->RemoveHelper();
            }

            break;

        case 9:
            cout << "Good Bye" << endl;
            exit(0);
            break;
        
        }


    }
}

/*
 * The one and only main() method
 * The main menu is displayed here allowing choice of data structure
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */

int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    // Default Case is used everytime
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;

    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;

    default:
        csvPath = "Bid_Data_900.csv";
        bidKey = "98109";
    }

    int choice = 0;
   
        cout << "Welcome to the bid explorer program." << endl;
        cout << "  Choose your data structure to load and hold bid data" << endl;
        cout << "  1. Linked List" << endl;
        cout << "  2. Binary Search Tree" << endl;
        cout << "  3. Hash Table" << endl;
        cout << "  4. Data Mining" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        csv::Parser file = csv::Parser(csvPath);
        switch (choice) {
        case 1:
            loadLinkedList(file);
            bidModifierMenu(choice);
            break;

        case 2:
            cout << "You have selected Binary Search Tree" << endl;
            bst = new BinarySearchTree();
            try {
                // loop to read rows of a CSV file
                for (unsigned int i = 0; i < file.rowCount(); i++) {

                // Create a data structure and add to the collection of bids
                    Bid bid;
                    bid.bidId = file[i][1];
                    bid.title = file[i][0];
                    bid.fund = file[i][8];
                    bid.amount = strToDouble(file[i][4], '$');

                //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;// Debugging purposes

                // Inserts bid into binary search tree
                    bst->Insert(bid);
                }
                // Loads secondary menu
                bidModifierMenu(choice);
            }
            catch (csv::Error& e) {
                std::cerr << e.what() << std::endl;
            }

            break;

        case 3:
            cout << "You have selected Hash Table" << endl;
            bidTable = new HashTable();
            try {
                // loop to read rows of a CSV file
                for (unsigned int i = 0; i < file.rowCount(); i++) {

                // Create a data structure and add to the collection of bids
                    Bid bid;
                    bid.bidId = file[i][1];
                    bid.title = file[i][0];
                    bid.fund = file[i][8];
                    bid.amount = strToDouble(file[i][4], '$');

                //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;// Debugging purposes

                // Insert bid into hash table
                    bidTable->Insert(bid);
                }
                bidModifierMenu(choice);
            }
            catch (csv::Error& e) {
                std::cerr << e.what() << std::endl;
            }
            break;

        case 4:
            
            // Load into linked list
            cout << "Loading CSV file " << csvPath << endl;

            try {
                // loop to read rows of a CSV file
                for (int i = 0; i < file.rowCount(); i++) {

                    // initialize a bid using data from current row (i)
                    Bid bid;
                    bid.bidId = file[i][1];
                    bid.title = file[i][0];
                    bid.fund = file[i][8];
                    bid.amount = strToDouble(file[i][4], '$');

                    // cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl; // Debugging Purposes

                       // adds this bid to the end
                    bidList.Append(bid);
                }


            }
            catch (csv::Error& e) {
                std::cerr << e.what() << std::endl;
            }
            
            // Creates new data miner
            myDataMiner = new DataMiner(bidList);

            break;

        case 9:
            cout << "Good Bye" << endl;
            exit(0);
            break;
        }
  
    
    return 0;
} 
