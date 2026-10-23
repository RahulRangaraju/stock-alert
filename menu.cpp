#include <iostream>
#include <limits>
#include <iomanip>
#include "menu.h"
#include "analysis.h"

using namespace std;

int getChoice(int low, int high){
    bool validChoice = false;
    int userChoice;
    do {
    cout << "Menu Option: ";
    cin >> userChoice;
    if (cin.fail()){
	cout << "Enter a valid choice: " << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (userChoice >= low && userChoice <= high){
	validChoice = true;	
    }
    } while (!validChoice);
    return userChoice;
}

int getSettingsChoice(int low, int high){
    bool validChoice = false;
    int userChoice;
    do {
    cout << "Window Length: ";
    cin >> userChoice;
    if (cin.fail()){
	cout << "Enter a valid choice: " << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (userChoice >= low && userChoice <= high){
	validChoice = true;	
    }
    } while (!validChoice);
    return userChoice;
}

void displayStocks(const vector<stock>& stocks){
int i = 0;
    for (const stock& stock : stocks){
	    cout << i + 1 << ". " << stock.ticker << endl;
	    i++;
    }
}

void displayPriceHistory(const stock& stock, int numDays, int endIndex){
    if (numDays > endIndex + 1){
	numDays = endIndex + 1;
    }
    cout << fixed << setprecision(2);
    for (int i = 0; i < numDays; i++){
	cout << "----------------" << endl;
	cout << "Date: " << stock.stockInfo.at(endIndex - i).date.substr(0, 10) << endl;
	cout << "----------------" << endl;
	cout << "Open: " << stock.stockInfo.at(endIndex - i).openPrice << endl;
	cout << "Close: " << stock.stockInfo.at(endIndex - i).closePrice << endl;
	cout << "Daily High: " << stock.stockInfo.at(endIndex - i).dailyHigh << endl;
	cout << "Daily Low: " << stock.stockInfo.at(endIndex - i).dailyLow << endl;
	cout << "Trade Volume: " << stock.stockInfo.at(endIndex - i).tradeVol << endl;
	if (getPercentChange(stock, endIndex - i) == -1000) {
	cout << "Change Since Last Close: " << "N/A" << endl;
} else {
	cout << "Change Since Last Close: " << getPercentChange(stock, endIndex - i) << "%" << endl;
    }
	cout << "Change Since Open: " << openToCloseChange(stock, endIndex - i) << "%" << endl;
    }
    cout << defaultfloat << setprecision(6);
}

void displayMenu(){
    cout << "1. Price History " << endl;
    cout << "2. Indicators" << endl;
    cout << "3. Change Stock" << endl;
    cout << "4. Analysis Settings" << endl;
    cout << "5. Quit" << endl;
    // implement settings option to modify all window settings
}

void priceHistoryMenu(){
    cout << "1. Search By Date " << endl;
    cout << "2. Search By Date Range " << endl;
    cout << "3. All Available Price History " << endl;
    cout << "4. Return To Main Menu " << endl;
}

void indicatorMenu(){
    cout << "1. View ZScore " << endl;
    cout << "2. Downstreaks " << endl;
    cout << "3. RSI" << endl;
    cout << "4. Trend Ratio " << endl;
    cout << "5. Volume Ratio " << endl;
    cout << "6. Gap Percent " << endl;
    cout << "7. Close Location " << endl;
    cout << "8. Drawdown From High " << endl;
    cout << "9. Volatility Ratio " << endl;
    cout << "0. Return To Main Menu " << endl;
}

void indicatorSettingsMenu(){
    cout << "1. Configure ZScore Window" << endl;
    cout << "2. Configure RSI Window" << endl;
    cout << "3. Configure Trend Ratio Window" << endl;
    cout << "4. Configure Volume Ratio Window" << endl;
    cout << "5. Drawdown From High " << endl;
    cout << "6. Volatility Ratio " << endl;
    cout << "0. Return To Main Menu " << endl;
}

void settingsMenu(){
    cout << "1. Use Default Values" << endl;
    cout << "2. Advanced - User Configured" << endl;
    cout << "3. View Current Settings" << endl;
    cout << "4. Save And Exit" << endl;
}

void runPriceHistory(const stock& chosen, int endIndex){
    const int HISTORY_MENU_CHOICES = 4;
    bool priceHistoryLoop = true;
    do {
	int totalInfo = static_cast<int>(chosen.stockInfo.size());
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
}

void  runIndicators(const stock& chosen, const AnalysisSettings& settings, int endIndex){
    const int INDICATOR_CHOICES = 9; 
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
		    cout << "ZScore: " << getZScore(chosen, settings.zScoreWindow, endIndex) << endl;
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
		    cout << "Longest Downstreak: " << longestDownStreak(chosen, endIndex) << endl;
		    cout << "Current Downstreak: " << currentDownStreak(chosen, endIndex) << endl;
		    cout << "******************" << endl;
		    break;
		case 3: 
		    cout << "******************" << endl;
		    if (relativeStrengthIndex(chosen, settings.rsiWindow, endIndex) == -1){
			cout << "RSI: N/A" << endl;
		    }
		    else {
			cout << "RSI (" << settings.rsiWindow << " days): " << relativeStrengthIndex(chosen, settings.rsiWindow, endIndex) << endl;
		    }
		    cout << "******************" << endl;
		    break;
		case 4:
		    cout << "******************" << endl;
		    cout << "Trend Ratio: " << trendRatio(chosen, settings.trendWindow, endIndex) << endl;
		    cout << "******************" << endl;
		    break;
		case 5: 
		    cout << "******************" << endl;
		    cout << "Average volume (last " << settings.volumeWindow << " days): " << fixed << setprecision(0) << avgVolume(chosen, settings.volumeWindow, endIndex) << endl;
		    cout << "Today's Volume: " << chosen.stockInfo.at(endIndex).tradeVol << endl;
		    cout << defaultfloat << setprecision(6);
		    cout << "Volume Ratio: " << volumeRatio(chosen, settings.volumeWindow, endIndex) << endl;
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
		    if (drawdownFromHigh(chosen, settings.drawdownWindow, endIndex) == -1000){
			cout << "Drawdown From High: N/A" << endl;
		    }	
		    else {
			cout << "Drawdown From High (" << settings.drawdownWindow << " days): " << drawdownFromHigh(chosen, settings.drawdownWindow, endIndex) << "%" << endl;
		    }
		    cout << "******************" << endl;
		    break;
		case 9:
		    cout << "******************" << endl;
		    if (volatilityRatio(chosen, settings.volatilityWindow, endIndex) == -1){
			cout << "Volatility Ratio: N/A" << endl;
		    }
		    else {
			cout << "Volatility Ratio (" << settings.volatilityWindow << " days): " << volatilityRatio(chosen, settings.volatilityWindow, endIndex) << endl;
		    }
		    cout << "******************" << endl;
		    break;
		case 0:
		    isInd = false;
		    break;
	    }
	} while (isInd);
}

void changeSettings(const stock& chosen, AnalysisSettings& settings){
    bool isSet = true;
    int totalInfo = static_cast<int>(chosen.stockInfo.size());
    const int SETTINGS_MENU = 4;
    const int SM_CHOICES = 6;
    do {
    settingsMenu();
    int settingsChoice = getChoice(0, SETTINGS_MENU);
	switch (settingsChoice){
	case 1:
	    settings = AnalysisSettings{};
		cout << "***************************" << endl;
		cout << "Using Default Window Values" << endl;
		cout << "***************************" << endl;
	    isSet = false;
	    break;
	case 2: {
	    bool inMenu = true;
	    do {
	    indicatorSettingsMenu();
	    int isChoice = getChoice(0, SM_CHOICES);
		switch (isChoice){
		    case 1:
			cout << "**************************" << endl;
			cout << "(Min: 2 | Max: " << totalInfo << ")" << endl;
			settings.zScoreWindow = getSettingsChoice(2, totalInfo);
			cout << "ZScore Window Length Saved" << endl;
			cout << "**************************" << endl;
			break;
		    case 2:
			cout << "***********************" << endl;
			cout << "(Min: 1 | Max: " << totalInfo - 1 << ")" << endl;
			settings.rsiWindow = getSettingsChoice(1, totalInfo - 1);
			cout << "RSI Window Length Saved" << endl;
			cout << "***********************" << endl;
			break;
		    case 3:
			cout << "*******************************" << endl;
			cout << "(Min: 1 | Max: " << totalInfo << ")" << endl;
			settings.trendWindow = getSettingsChoice(1, totalInfo);
			cout << "Trend Ratio Window Length Saved" << endl;
			cout << "*******************************" << endl;
			break;
		    case 4:
			cout << "********************************" << endl;
			cout << "(Min: 1 | Max: " << totalInfo - 1 << ")" << endl;
			settings.volumeWindow = getSettingsChoice(1, totalInfo - 1);
			cout << "Volume Ratio Window Length Saved" << endl;
			cout << "********************************" << endl;
			break;
		    case 5:
			cout << "****************************" << endl;
			cout << "(Min: 1 | Max: " << totalInfo << ")" << endl;
			settings.drawdownWindow = getSettingsChoice(1, totalInfo);
			cout << "Drawdown Window Length Saved" << endl;
			cout << "****************************" << endl;
			break;
		    case 6:
			cout << "************************************" << endl;
			cout << "(Min: 1 | Max: " << totalInfo - 1 << ")" << endl;
			settings.volatilityWindow = getSettingsChoice(1, totalInfo - 1);
			cout << "Volatility Ratio Window Length Saved" << endl;
			cout << "************************************" << endl;
			break;
		    case 0:
			inMenu = false;
			break;
		}
	    } while (inMenu);  
	    break;
	}
	case 3:
	    viewSettings(settings);
	    break;
	case 4:
	    cout << "**************" << endl;
	    cout << "Settings Saved" << endl;
	    cout << "**************" << endl;
	    isSet = false;
	    break;
	}
    } while (isSet);
}
    
int changeStock(const vector<stock>& stocks){
    cout << "******************" << endl;
    cout << "Pick A New Stock: " << endl;
    cout << "******************" << endl;
    displayStocks(stocks);
    int stockIndex = getChoice(1, static_cast<int>(stocks.size()));
    cout << "******************" << endl;
    return stockIndex;
}
