#pragma once
#ifndef     _BST_H_
# define    _BST_H_

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>
#include <iostream>
#include "CSLinked_List.h"


using namespace std;

struct Node {
    Bid bids;
    Node* right;
    Node* left;
    Node() {
        right = left = nullptr;
    }
    Node(Bid bids) : Node() {
        this->bids = bids;
    }
};

class BinarySearchTree {

private:
    Node* root;


    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    void RemoveHelper();
    Bid Search(string bidId);
    void SearchHelper();
    Bid getBidbst();
   

};

#endif 

