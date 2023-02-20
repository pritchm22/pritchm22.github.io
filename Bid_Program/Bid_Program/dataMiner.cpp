#include <iostream>
#include "DataMiner.h"

using namespace std;

LinkedList myBidList;

DataMiner::DataMiner() {

}
// Calling a variety of linked list functions to display information about the data set
DataMiner::DataMiner(LinkedList tempList) {
	myBidList = tempList;
	cout << "Total number of bids: " << myBidList.Size() << endl;
	//myBidList.PrintList();  Routine debugging
	myBidList.FindMinMax();
	myBidList.FindAvgMean();
	myBidList.FindMinMaxBidId();
	myBidList.FindMinMaxAuctionFee();
	myBidList.FindAvgMeanAuctionFee();

	
}