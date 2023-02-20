#ifndef     _LINKEDLIST_H_
# define    _LINKEDLIST_H_

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>
#include <iostream>
#include "Utility.cpp"

using namespace std;

    enum DataType {
        eFILE = 0,
        ePURE = 1
    };
        

    class LinkedList {
        struct node {
            Bid data;
            node* nextNode;

        };

    private:
       
        node* head;
        node* tail;
        int size;

    public:

        LinkedList();
        ~LinkedList(void);
        void Append(Bid bid);
        void Prepend(Bid bid);
        void PrintList();
        void Remove(string bidId);
        void RemoveHelper();
        Bid Search(string bidId);
        void SearchHelper();
        Bid getBid();
        void displayBid(Bid bid);
        void FindMinMax();
        void FindAvgMean();
        void FindMinMaxBidId();
        void FindMinMaxAuctionFee();
        void FindAvgMeanAuctionFee();
        int Size();
    };

    


#endif 
