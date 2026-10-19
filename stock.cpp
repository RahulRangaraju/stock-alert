#include <iostream>
#include <fstream>
#include <sstream>
#include "stock.h"

using namespace std;

vector<day> historicalData(const string& filename){
    vector<day> historicData;
    ifstream inFile(filename);
    if (!inFile.is_open()){
	cerr << "Error opening " << filename << "!" << endl;
    return historicData;
    }
    string line;
    getline(inFile, line);

    while (getline(inFile, line)){
	if (line.empty()){
	    continue;
	}
	stringstream ss(line);
	string date;
	string ignore1;
	string ignore2;
	string ignore3;
	string openPrice;
	string dailyHigh;
	string dailyLow;
	string closePrice;
	string tradeVol;
	string symbol;
	getline(ss, date, ',');
	getline(ss, ignore1, ',');
	getline(ss, ignore2, ',');
	getline(ss, ignore3, ',');
	getline(ss, openPrice, ',');
	getline(ss, dailyHigh, ',');
	getline(ss, dailyLow, ',');
	getline(ss, closePrice, ',');
	getline(ss, tradeVol, ',');
	getline(ss, symbol);
	day day;
	day.date = date;
	day.openPrice = stod(openPrice);
	day.dailyHigh = stod(dailyHigh);
	day.dailyLow = stod(dailyLow);
	day.closePrice = stod(closePrice);
	day.tradeVol = stoll(tradeVol);
	day.symbol = symbol;
	historicData.push_back(day);
    }
    
    return historicData;
}

stock loadStock(const string& stockName){
    stock s1;
    s1.ticker = stockName;
    s1.stockInfo = historicalData("data/" + stockName + ".csv");
    return s1;
}

void display(const day& day){
    cout << "Date: " << day.date.substr(0,10) << endl;
    cout << "Open: " << day.openPrice << endl;
    cout << "High: " << day.dailyHigh << endl;
    cout << "Low: " << day.dailyLow << endl;
    cout << "Close: " << day.closePrice << endl;
    cout << "Trade Volume: " << day.tradeVol << endl;
}

void display(const vector<day>& vec){
    for (const day& day : vec){
	display(day);
    }
}

void printStock(const stock& stock){
    cout << "Ticker: " << stock.ticker << endl;
    display(stock.stockInfo.back());
}


