#include <iostream>
#include "stock.h"
#include "analysis.h"

using namespace std;

int stockAmt(){
    int amt;
    cout << "How many stocks do you want to track?: ";
    cin >> amt;
    return amt;
}

string readTicker(){
    string stockName;
    cout << "Enter stock to track: ";
    cin >> stockName;
    return stockName;
}

int main(){
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    for (const stock& stock : stocks){
	int endIndex = static_cast<int>(stock.stockInfo.size()) - 1;
	cout << "Ticker: " << stock.ticker << endl;
	cout << "Days Worth Of Info: " << stock.stockInfo.size() << endl;
	cout << "Latest Closing Price: " << latestClose(stock) << endl;
	cout << "Average Closing Price Over 200 days: " <<
avgClose(stock, 200, endIndex) << endl;
	cout << "zscore Over 200 days: " << getZScore(stock, endIndex) << endl;
	cout << "------------" << endl;
	if (theAlgorithm(stock, endIndex)){
	    cout << "************" << endl;
	    cout << "ALERT - " << stock.ticker << endl;
	    cout << "************" << endl;
	}
    }
    return 0;
}
