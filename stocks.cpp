#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct stock {
    string ticker;
    double currentPrice;
    double lastPrice;
    double lastOpenPrice;
    double lastClosePrice;
    double dailyHigh;
    double dailyLow;
    long long int tradeVolume;
};

void printStock(const stock& s){
    cout << "Ticker: " << s.ticker << endl;
    cout << "Current Price: " << s.currentPrice << endl;
    cout << "Last Price: " << s.lastPrice << endl;
    cout << "Last Open: " << s.lastOpenPrice << endl;
    cout << "Last Close: " << s.lastClosePrice << endl;
    cout << "Daily High: " << s.dailyHigh << endl;
    cout << "Daily Low: " << s.dailyLow << endl;
    cout << "Trade Volume: " << s.tradeVolume << endl;
}

double getPercentChange(const stock& stock){
    double percentChange = 0;
    percentChange = ( stock.currentPrice - stock.lastPrice ) / stock.lastPrice * 100;
    return percentChange;
}

stock readStock(ifstream& inFile){
    stock s;
	inFile >> s.ticker >> s.currentPrice >> s.lastPrice >> s.lastOpenPrice >> s.lastClosePrice >> s.dailyHigh >> s.dailyLow >> s.tradeVolume;
    return s;
}

int main(){
    ifstream inFile("stocks.txt");
    if (!inFile.is_open()){
	cerr << "Error opening file!" << endl;
    }
    vector<stock> stockList;
    while (true){
	stock s = readStock(inFile);
	if (!inFile){
	    break;
	}
	stockList.push_back(s);
    }
    for (stock stock : stockList){
	printStock(stock);
	cout << "Percent Change: " << getPercentChange(stock) << endl;
    }
    return 0;
}
