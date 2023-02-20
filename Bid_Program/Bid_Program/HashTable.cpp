//============================================================================
// Name        : HashTable.cpp
// Author      : Michael Pritchard
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"
#include "HashTable.h"

using namespace std;

/*
This is a hash table with a bid struct and a mapping from keys to values.
The following functions have been implemented: Insert, PrintAll, Remove, and
Search.
*/

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;


/**
 * Default constructor
 */
HashTable::HashTable() {
    bids.resize(17939);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    bids.clear();
    delete& bids;
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    int hashVal = 25;
    int hash = key % hashVal;
    return hash;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    int id = stoi(bid.bidId);
    int key = hash(id);
    Bid currentNode;
    currentNode = bid;

    bids.at(key).push_back(currentNode);
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    for (int i = 0; i < bids.size(); ++i) {
        if (bids.at(i).size() > 0) {
            for (auto j : bids.at(i))
                cout << "Key " << i << ": | " << j.bidId << " | " << j.title << " | " << j.amount << " | " << j.fund << endl;
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    int hashVal = stoi(bidId);
    int key = hash(hashVal);
    if (bids.at(key).size() > 0) {
        //cout << "Going to remove from key" << key << endl; // Debugging Purposes
        list<Bid>::const_iterator k;
        for (k = bids.at(key).begin(); k != bids.at(key).end(); k++) {
            if (k->bidId.compare(bidId) == 0) {
                k = bids.at(key).erase(k);
                return;
            }
        }

    }
}

// Asks user for bidId before removing
void HashTable::RemoveHelper() {
    Bid bid;
    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);
    Remove(bid.bidId);
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    int hashVal = stoi(bidId);
    int key = hash(hashVal);
    if (bids.at(key).size() > 0) {
        list<Bid>::const_iterator k;
        for (k = bids.at(key).begin(); k != bids.at(key).end(); k++) {
            if (k->bidId.compare(bidId) == 0) {
                return *k;

            }
        }

    }

    return bid;
}

// Asks user for bidId before searching
void HashTable::SearchHelper() {
    Bid bid;
    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);
        
    bid = Search(bid.bidId);
    if (!bid.bidId.empty()) {
        cout << bid.bidId << ": " << bid.title << " | " << bid.amount
            << " | " << bid.fund << endl;
    }
    else {
        cout << "Bid Id " << bid.bidId << " not found." << endl;
    }

}


/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    
}
Bid HashTable::getBid() {
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
    bid.amount = strToDoubleHt(strAmount, '$');

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

double HashTable::strToDoubleHt(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}


