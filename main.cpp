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

const int MENU_CHOICES = 6;
const int HISTORY_DAYS = 300;
const int ZSCORE_WINDOW = 100;
const int VOLUME_WINDOW = 100;

int main(){
    bool isRunning = true;
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    cout << "Pick A Stock To Track: " << endl;
    displayStocks(stocks);
    int stockIndex = getChoice(1, static_cast<int>(stocks.size()));
    do {
    const stock& chosen = stocks.at(stockIndex - 1);
    int endIndex = static_cast<int>(chosen.stockInfo.size()) - 1;
    cout << "Ticker: " << chosen.ticker << endl;
    displayMenu();
    int choice = getChoice(1, MENU_CHOICES);
    choice -= 1;
    cout << "************************" << endl;
    switch (choice){
	case 0:
	    displayPriceHistory(chosen, HISTORY_DAYS, endIndex);
	    break;
	case 1:
	    cout << "Daily Change: " << getPercentChange(chosen, endIndex) << "%" << endl;
	    cout << "Intraday Change: " << openToCloseChange(chosen, endIndex) << "%" << endl;
	    break;
	case 2:
	    cout << "ZScore: " << getZScore(chosen, ZSCORE_WINDOW, endIndex) << endl;
	    break;
	case 3: 
	    cout << "Average volume (last " << VOLUME_WINDOW << " days): " << fixed << setprecision(0) << avgVolume(chosen, VOLUME_WINDOW, endIndex) << endl;
	    cout << defaultfloat << setprecision(6);
	    cout << "Volume Ratio: " << volumeRatio(chosen, VOLUME_WINDOW, endIndex) << endl;
	    break;
	case 4: 
	    cout << "Pick A New Stock: " << endl;
	    displayStocks(stocks);
	    stockIndex = getChoice(1, static_cast<int>(stocks.size()));
	    break;
	case 5: 
	    isRunning = false;	    
	}
    cout << "************************" << endl;
    } while (isRunning); 
    return 0;
}
