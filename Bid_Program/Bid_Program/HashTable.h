#pragma once
#ifndef     _HashT_H_
# define    _HashT_H_

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>
#include <iostream>
#include "CSLinked_List.h"


class HashTable {

private:
    vector<list<Bid>>bids;
    unsigned int hash(int key);


public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    void RemoveHelper();
    Bid Search(string bidId);
    void SearchHelper();
    Bid getBid();
    double strToDoubleHt(string str, char ch);
};

#endif 