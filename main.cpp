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
const int HISTORY_MENU_CHOICES = 4;
const int INDICATOR_CHOICES = 9;
const int HISTORY_DAYS = 251;
const int ZSCORE_WINDOW = 251;
const int VOLUME_WINDOW = 250;
const int TREND_WINDOW = 251;
const int DRAWDOWN_WINDOW = 251;
const int VOLATILITY_WINDOW = 251;
const int RSI_WINDOW = 14;

int main(){
    bool isRunning = true;
    bool priceHistoryLoop = true;
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
    int totalInfo = static_cast<int>(chosen.stockInfo.size());
    cout << "Ticker: " << chosen.ticker << endl;
    displayMenu();
    int choice = getChoice(1, MENU_CHOICES);
    choice -= 1;
    switch (choice){
	case 0:
	    {
	//    priceHistoryMenu();
	//    displayPriceHistory(chosen, HISTORY_DAYS, endIndex);
	    do {
		priceHistoryLoop = true;
		cout << "******************" << endl;
		priceHistoryMenu();
		cout << "******************" << endl;
		int subChoice = getChoice(1, HISTORY_MENU_CHOICES);
	    switch (subChoice){
		case 1: {
		    string date;
		    cout << "Enter a date: (yyyy-mm-dd): ";
		    cin >> date;
		    int index = findDateIndex(chosen, date);
		    if (index == -1){
			cout << "No Data For That Date..." << endl;
		    }
		    displayPriceHistory(chosen, 1, index);
		    break;
		}
		case 2: {
		    cout << "******************" << endl;
		    string start;
		    string end;
		    cout << "Enter A Start Date: ";
		    cin >> start;
		    cout << "Enter A End Date: ";
		    cin >> end;
		    int sIndex = findDateIndex(chosen, start);
		    int eIndex = findDateIndex(chosen, end);
		    if (sIndex == -1 || eIndex == -1){
			cout << "******************" << endl;
			cout << "Invalid Range" << endl;
			cout << "******************" << endl;
		    }
		    int range = eIndex - sIndex;
		    if (range < 0){
			cout << "Invalid Range" << endl;
		    }
		    cout << "******************" << endl;
		    displayPriceHistory(chosen, range + 1, eIndex);
		    break;
		}
		case 3: 
		    displayPriceHistory(chosen, totalInfo, endIndex);
		    break;
		case 4:
		    priceHistoryLoop = false;
		    break;
	    } 
	    }while (priceHistoryLoop);
	    break;
	    }
	case 1: {
	    bool isInd = true;
	    cout << "******************" << endl;
	    // cout << "ZScore: " << getZScore(chosen, ZSCORE_WINDOW, endIndex) << endl;
	    cout << "Indicators: " << endl;
	    cout << "******************" << endl;
	    do {
	    isInd = true;
	    indicatorMenu();
	    int iChoice = getChoice(0, INDICATOR_CHOICES);
		switch (iChoice){
		    case 1: 
			cout << "******************" << endl;
			cout << "ZScore: " << getZScore(chosen, ZSCORE_WINDOW, endIndex) << endl;
			cout << "******************" << endl;
			break;
		    case 2: 
			if (longestDownStreak(chosen, endIndex) == -1){
			    cout << "******************" << endl;
			    cout << "Not Enough Data" << endl;
			    cout << "******************" << endl;
			    break;
			}
			cout << "******************" << endl;
			cout << "Longest Downstreak Over " << totalInfo << " Days: " << longestDownStreak(chosen, endIndex) << endl;
			cout << "Current Downstreak: " << currentDownStreak(chosen, endIndex) << endl;
			cout << "******************" << endl;
			break;
		    case 3: 
			cout << "******************" << endl;
			if (relativeStrengthIndex(chosen, RSI_WINDOW, endIndex) == -1){
			    cout << "RSI: N/A" << endl;
			}
			else {
			    cout << "RSI (" << RSI_WINDOW << " days): " << relativeStrengthIndex(chosen, RSI_WINDOW, endIndex) << endl;
			}
			cout << "******************" << endl;
			break;
		    case 4:
			cout << "******************" << endl;
			cout << "Trend Ratio: " << trendRatio(chosen, TREND_WINDOW, endIndex) << endl;
			cout << "******************" << endl;
			break;
		    case 5: 
			cout << "******************" << endl;
			cout << "Average volume (last " << VOLUME_WINDOW << " days): " << fixed << setprecision(0) << avgVolume(chosen, VOLUME_WINDOW, endIndex) << endl;
			cout << "Today's Volume: " << chosen.stockInfo.at(endIndex).tradeVol << endl;
			cout << defaultfloat << setprecision(6);
			cout << "Volume Ratio: " << volumeRatio(chosen, VOLUME_WINDOW, endIndex) << endl;
			cout << "******************" << endl;
			break;
		    case 6: 
			cout << "******************" << endl;
			if (gapPercent(chosen, endIndex) == -1000){
			    cout << "Gap Percent: N/A" << endl;
			} else {
			cout << "Gap Percent: " << gapPercent(chosen, endIndex) << "%" << endl;
			}
			cout << "******************" << endl;
			break;
		    case 7:
			cout << "******************" << endl;
			if (closeLocation(chosen, endIndex) == -1){
			    cout << "Close Location: N/A" << endl;
			}
			else {
			cout << "Close Location: " << closeLocation(chosen, endIndex) << endl;
			}
			cout << "******************" << endl;
			break;
		    case 8:
			cout << "******************" << endl;
			if (drawdownFromHigh(chosen, DRAWDOWN_WINDOW, endIndex) == -1000){
			    cout << "Drawdown From High: N/A" << endl;
			}	
			else {
			    cout << "Drawdown From High (" << DRAWDOWN_WINDOW << " days): " << drawdownFromHigh(chosen, DRAWDOWN_WINDOW, endIndex) << "%" << endl;
			}
			cout << "******************" << endl;
			break;
		    case 9:
			cout << "******************" << endl;
			if (volatilityRatio(chosen, VOLATILITY_WINDOW, endIndex) == -1){
			    cout << "Volatility Ratio: N/A" << endl;
			}
			else {
			    cout << "Volatility Ratio (" << VOLATILITY_WINDOW << " days): " << volatilityRatio(chosen, VOLATILITY_WINDOW, endIndex) << endl;
			}
			cout << "******************" << endl;
			break;
		    case 0:
			isInd = false;
			break;
		}
	    } while (isInd);
	break;
	}
	case 2: 
	    cout << "******************" << endl;
	    cout << "Pick A New Stock: " << endl;
	    cout << "******************" << endl;
	    displayStocks(stocks);
	    stockIndex = getChoice(1, static_cast<int>(stocks.size()));
	    cout << "******************" << endl;
	    break;
	case 3:
	    // IMPLEMENT ANALYSIS SETTINGS;
	    // CONFIGURE DATES AND WINDOWS TO ANALYZE
	    break;
	case 4: 
	    isRunning = false;	    
	    break;
	}
    } while (isRunning); 
    return 0;
}
