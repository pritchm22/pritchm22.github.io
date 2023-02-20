#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;


int main(int argc, char* argv[]) {
	

    string csvPath, bidKey;
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
        cout << "Default Bid Data" << endl;
        csvPath = "Bid_Data_20.csv";
        bidKey = "98109";
    }

	return 0;
}