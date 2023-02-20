#include <iostream>


using namespace std;
// The struct to hold bid information including id, title, fund, and amount

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
