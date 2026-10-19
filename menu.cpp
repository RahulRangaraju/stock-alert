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
	cout << "Enter a valid choice: ";
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
	cout << "________________" << endl;
	cout << "Date: " << stock.stockInfo.at(endIndex - i).date.substr(0, 10) << endl;
	cout << "________________" << endl;
	cout << "Open: " << stock.stockInfo.at(endIndex - i).openPrice << endl;
	cout << "Close: " << stock.stockInfo.at(endIndex - i).closePrice << endl;
	cout << "Daily High: " << stock.stockInfo.at(endIndex - i).dailyHigh << endl;
	cout << "Daily Low: " << stock.stockInfo.at(endIndex - i).dailyLow << endl;
	cout << "Trade Volume: " << stock.stockInfo.at(endIndex - i).tradeVol << endl;
    }
    cout << defaultfloat << setprecision(6);
}

void displayMenu(){
    cout << "1. Price History: " << endl;
    cout << "2. Percent Change (1 day): " << endl;
    cout << "3. ZScore / Alert: " << endl;
    cout << "4. Trade Volume and Volume Ratio: " << endl;
    cout << "5. Change Stock" << endl;
    cout << "6. Quit" << endl;
    // implement settings option to modify all window settings
}

void priceHistoryMenu(){
    cout << "1. Search By Date: " << endl;
    cout << "2. Search By Date Range: " << endl;
    cout << "3. Exit: " << endl;
}

