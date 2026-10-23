#include <iostream>
#include <iomanip>
#include "stock.h"
#include "analysis.h"
#include "menu.h"
#include "settings.h"

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
const int INDICATOR_CHOICES = 9;
const int HISTORY_DAYS = 251;
const int SETTINGS_MENU = 4;
const int SM_CHOICES = 6;

int main(){
    AnalysisSettings settings;
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
    switch (choice){
	case 0: 
	    runPriceHistory(chosen, endIndex);				
	    break;
	case 1: 
	    runIndicators(chosen, settings, endIndex);
	    break;
	case 2: 
	    stockIndex = changeStock(stocks);
	    break;
	case 3: 
	    changeSettings(chosen, settings);
	    break;
	case 4: 
	    isRunning = false;	    
	    break;
	}
    } while (isRunning); 
    return 0;
}
