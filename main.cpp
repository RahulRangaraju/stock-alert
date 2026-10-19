#include <iostream>
#include <iomanip>
#include "stock.h"
#include "analysis.h"
#include "menu.h"

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
/*
int main(){
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    int numDays = 200;
    for (const stock& stock : stocks){
	int endIndex = static_cast<int>(stock.stockInfo.size() - 1);
	cout << "Ticker: " << stock.ticker << endl;
	cout << "Total Days In Set: " << stock.stockInfo.size() << endl;
	cout << stock.stockInfo.at(endIndex - numDays + 1).date.substr(0,10) << " to " << stock.stockInfo.at(endIndex).date.substr(0,10) << endl;
	cout << "Latest Open Price: $" << latestOpen(stock, endIndex) << endl;
	cout << "Latest Closing Price: $" << latestClose(stock, endIndex) << endl;
	cout << "Intraday Change: " << openToCloseChange(stock, endIndex) << "%" << endl;
	cout << "Previous Open Price: $" << prevOpen(stock, endIndex) << endl;
	cout << "Previous Closing Price: $" << prevClose(stock, endIndex) << endl;
	cout << "Percent Change (Close-to-Close): " << getPercentChange(stock, endIndex) << "%" << endl;
	cout << "Average Closing Price Over " << numDays << " days: " <<
avgClose(stock, numDays, endIndex) << endl;
	cout << "zscore Over " << numDays << " days: " << getZScore(stock, numDays, endIndex) << endl;
	cout << "Average volume over " << numDays << " days (excludes latest day): " << fixed << setprecision(0) << avgVolume(stock, numDays, endIndex) << endl;
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
*/

/*
int main(){
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    int numDays = 1;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    cout << "Pick A Stock To Track: " << endl;
    displayStocks(stocks);
    int choice = getChoice(1, static_cast<int>(stocks.size()));
    const stock& chosen = stocks.at(choice - 1);
    int endIndex = static_cast<int>(chosen.stockInfo.size()) - 1;
    displayPriceHistory(stocks.at(choice - 1), numDays, endIndex);
    
    return 0;
}
*/

const int MENU_CHOICES = 6;

int main(){
    bool isRunning = true;
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    int numDays = 1;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    cout << "Pick A Stock To Track: " << endl;
    displayStocks(stocks);
    int choice = getChoice(1, static_cast<int>(stocks.size()));
    const stock& chosen = stocks.at(choice - 1);
    int endIndex = static_cast<int>(chosen.stockInfo.size()) - 1;
    cout << "Ticker: " << chosen.ticker << endl;
    displayMenu();
    choice = getChoice(1, MENU_CHOICES);
    choice -= 1;
    do {
    switch (choice){
	case 0:
	    displayPriceHistory(chosen, numDays, endIndex);
	case 1:
	    cout << "Daily Change" << openToCloseChange(chosen, endIndex) << endl;
	case 2:
	    cout << "ZScore: " << getZScore(chosen, numDays, endIndex) << endl;
	case 3: 
	    cout << "Average volume (last " << numDays << " days)" << avgVolume(chosen, numDays, endIndex) << endl;
	    cout << "Volume Ratio: " << volumeRatio(chosen, numDays, endIndex);
	case 4: 
	    displayStocks(stocks);
	    choice = getChoice(1, static_cast<int>(stocks.size()));
	    displayMenu();
	case 5: 
	    isRunning = false;	    
	}
    } while (isRunning); 
    return 0;
}
