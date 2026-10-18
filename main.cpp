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
	cout << "Ticker: " << stock.ticker << endl;
	cout << "Days Worth Of Info: " << stock.stockInfo.size() << endl;
	cout << "Latest Closing Price: " << latestClose(stock) << endl;
	cout << "Average Closing Price Over 200 days: " <<
avgClose(stock, 200) << endl;
	cout << "zscore Over 200 days: " << getZScore(stock) << endl;
	cout << "------------" << endl;
	if (theAlgorithm(stock)){
	    cout << "************" << endl;
	    cout << "ALERT - " << stock.ticker << endl;
	    cout << "************" << endl;
	}
    }
    return 0;
}
