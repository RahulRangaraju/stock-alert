#include <iostream>
#include <iomanip>
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
    int numDays = 200;
    for (const stock& stock : stocks){
	int endIndex = static_cast<int>(stock.stockInfo.size()) - 1;
	cout << "Ticker: " << stock.ticker << endl;
	cout << "Days Worth Of Info: " << stock.stockInfo.size() << endl;
	cout << "Latest Open Price: $" << latestOpen(stock, endIndex) << endl;
	cout << "Latest Closing Price: $" << latestClose(stock, endIndex) << endl;
	cout << "Intraday Change: " << openToCloseChange(stock, endIndex) << "%" << endl;
	cout << "Previous Open Price: $" << prevOpen(stock, endIndex) << endl;
	cout << "Previous Closing Price: $" << prevClose(stock, endIndex) << endl;
	cout << "Percent Change (Close-to-Close): " << getPercentChange(stock, endIndex) << "%" << endl;
	cout << "Average Closing Price Over " << numDays << " days: " <<
avgClose(stock, numDays, endIndex) << endl;
	cout << "zscore Over " << numDays << " days: " << getZScore(stock, numDays, endIndex) << endl;
	cout << "Average volume over " << numDays << " days: " << fixed << setprecision(0) << avgVolume(stock, numDays, endIndex) << endl;
	cout << "Trading Volume On Last Trading Day: " << stock.stockInfo.at(endIndex).tradeVol << endl;
	cout << defaultfloat << setprecision(6);
	cout << "Volume Ratio (" << numDays << " days): " << volumeRatio(stock, numDays, endIndex) << endl;
	cout << "------------" << endl;
	if (theAlgorithm(stock, numDays, endIndex)){
	    cout << "************" << endl;
	    cout << "ALERT - " << stock.ticker << endl;
	    cout << "************" << endl;
	}
    }
    return 0;
}
