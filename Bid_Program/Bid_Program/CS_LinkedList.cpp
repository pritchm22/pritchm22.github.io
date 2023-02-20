
//============================================================================
// Name        : LinkedList.cpp
// Author      : Michael Pritchard
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>
#include "CSLinked_List.h"
#include "CSVparser.hpp"


using namespace std;

    /*
    This is a linked list with a bid struct where each node is connected to the next
    node, one after another and another.  The following functions have been
    implemented: Append, Prepend, PrintList, Remove, and Search.
    */

    //============================================================================
    // Global definitions visible to all methods and classes
    //============================================================================

double strToDouble(string str, char ch);

    //============================================================================
    // Linked-List class definition
    //============================================================================

    
     //Default constructor
     LinkedList::LinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
     }
         
     //Destructor
    LinkedList::~LinkedList(void) {
        
        return;
    }

    /**
     * Append a new bid to the end of the list
     */
    void LinkedList::Append(Bid bid) {
        node* newNode = new node;
        newNode->data = bid;
        newNode->nextNode = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            ++size;
        }
        else {
            tail->nextNode = newNode;
            tail = newNode;
            ++size;
        }
    }

    /**
     * Prepend a new bid to the start of the list
     */
    void LinkedList::Prepend(Bid bid) {

        node* newNode = new node;
        newNode->data = bid;
        newNode->nextNode = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            ++size;
        }
        else {
            newNode->nextNode = head;
            head = newNode;
            ++size;
        }
    }

    /**
     * Simple output of all bids in the list
     */
    void LinkedList::PrintList() {

        node* temp = head;

        while (temp != nullptr) {
            cout << temp->data.title << "|";
            cout << temp->data.amount << "|";
            cout << temp->data.fund << endl;
            temp = temp->nextNode;
        }
    }
    // Asks the user for bidId before removing
    void LinkedList::RemoveHelper() {

        Bid bid;
        cout << "Enter Id: ";
        cin.ignore();
        getline(cin, bid.bidId);
        Remove(bid.bidId);
    }

    /**
     * Remove a specified bid
     *
     * @param bidId The bid id to remove from the list
     */
    void LinkedList::Remove(string bidId) {
        
         node* temp = head;
         node* prevNode = head;
         
         if (temp == nullptr) { // If empty list 
             return;
         }
         else if (head->data.bidId == bidId && head->nextNode == nullptr) { // List has 1 element
             head = nullptr;
             tail = nullptr;
             delete temp;
         }
         else if (head->data.bidId == bidId && head->nextNode != nullptr) { // Head is to be removed
             temp = temp->nextNode;
             delete prevNode;
             head = temp;
         }
         else { // Removing from the middle or end of the list
             while (temp->data.bidId != bidId) { 
                 prevNode = temp;
                 temp = temp->nextNode;
             }
             prevNode->nextNode = temp->nextNode;
             delete temp;

         } 
    }
    // Asks user for bidId before searching
    void LinkedList::SearchHelper() {

        Bid bid;
        cout << "Enter Id: ";
        cin.ignore();
        getline(cin, bid.bidId);
                
        bid = Search(bid.bidId);
        if (!bid.bidId.empty()) {
            displayBid(bid);
        }
        else {
            cout << "Bid Id " << bid.bidId << " not found." << endl;
        }

    }

    /*
     * Search for the specified bidId
     * @param bidId The bid id to search for
     */
    Bid LinkedList::Search(string bidId) {
        
        node* temp = head;
        node* holder = new node;
        holder->data.bidId = "";
        while (temp != nullptr) {
            //cout << temp->data.bidId << endl;
            if (temp->data.bidId == bidId) {
                return temp->data;
            }
            //cout << "test"; // For debugging
            temp = temp->nextNode;
        }
        return holder->data;

    }


    /**
     * Returns the current size (number of elements) in the list
     */
    int LinkedList::Size() {
        return size;
    }

    //============================================================================
    // Static methods used for testing
    //============================================================================

    /*
     * Display the bid information
     * @param bid struct containing the bid info
     */
    void LinkedList::displayBid(Bid bid) {
        cout << bid.bidId << ": " << bid.title << " | " << bid.amount
            << " | " << bid.fund << endl;
        return;
    }

    /*
     * Prompt user for bid information
     * @return Bid struct containing the bid info
     */
    Bid LinkedList::getBid() {
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
        bid.amount = strToDouble(strAmount, '$');

        return bid;
    }
    // Find the minimum and maximum values in the linked list
    void LinkedList::FindMinMax() {

        node* temp = head;
        double MinVal = 1000000;
        int MaxVal = 0;

        while (temp != nullptr) {
            
            if (temp->data.amount < MinVal && temp->data.amount > 0) {
                MinVal = temp->data.amount;
            }
            if (temp->data.amount > MaxVal) {
                MaxVal = temp->data.amount;
            }
            
            temp = temp->nextNode;
        }
        
        cout << "Minimum Bid Value: $" << MinVal << endl;
        cout << "Maximum Bid Value: $" << MaxVal << endl;
    }

    // Find the average mean and total value of the bids in the linked list
    void LinkedList::FindAvgMean() {

        node* temp = head;
        int TotalVal = 0;
        
        while (temp != nullptr) {
            
            TotalVal += temp->data.amount;
            temp = temp->nextNode;
        }
        double AvgVal = TotalVal / Size();
        cout << "Total Value of all bids: $" << TotalVal << endl;
        cout << "Average Mean of all bids: $" << AvgVal << endl;
    }
    // Find the minimum and maximum bidIds in the linked list
    void LinkedList::FindMinMaxBidId() {

        node* temp = head;
        double MinVal = 1000000;
        double MaxVal = 0;

        while (temp != nullptr) {
            
            string myBidId = temp->data.bidId;
            int bidIdint = stoi(myBidId);

            if (bidIdint < MinVal) {
                MinVal = bidIdint;
            }
            if (bidIdint > MaxVal) {
                MaxVal = bidIdint;
            }
            
            temp = temp->nextNode;
        }
        cout << "Minimum Bid Id: " << MinVal << endl;
        cout << "Maximum Bid Id: " << MaxVal << endl;
    }
    // Finds the minimum and maximum auction fees of the bids in the linked list
    void LinkedList::FindMinMaxAuctionFee() {

        node* temp = head;
        double MinVal = 1000000;
        double MaxVal = 0;

        while (temp != nullptr) {
           
            string auctionFee = temp->data.fund;
            double auctionFeeint = strToDouble(auctionFee, '$');

            if (auctionFeeint < MinVal) {
                MinVal = auctionFeeint;
            }
            if (auctionFeeint > MaxVal) {
                MaxVal = auctionFeeint;
            }
            
            temp = temp->nextNode;
        }
        cout << "Minimum Auction Fee: $" << MinVal << endl;
        cout << "Maximum Auction Fee: $" << MaxVal << endl;
        
    }
    // Finds the average mean of the auction fees in the linked list
    void LinkedList::FindAvgMeanAuctionFee() {

        node* temp = head;
        double totalVal = 0;
        double avgVal = 0;

        while (temp != nullptr) {
           
            string auctionFee = temp->data.fund;
            double auctionFeeint = strToDouble(auctionFee, '$');
            
            totalVal += auctionFeeint;
           
            temp = temp->nextNode;
        }
        avgVal = totalVal / Size();
        cout << "Total Auction Fee: $" << totalVal << endl;
        cout << "Average Auction Fee: $" << avgVal << endl;

    }
    /**
     * Load a CSV file containing bids into a LinkedList
     *
     * @return a LinkedList containing all the bids read
     */
    void loadBids(string csvPath, LinkedList* list) {
        
    }

    /**
     * Simple C function to convert a string to a double
     * after stripping out unwanted char
     *
     * credit: http://stackoverflow.com/a/24875936
     *
     * @param ch The character to strip out
     */

     
    double strToDouble(string str, char ch) {
        str.erase(remove(str.begin(), str.end(), ch), str.end());
        return atof(str.c_str());
    }
    
