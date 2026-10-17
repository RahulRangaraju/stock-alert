#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct day {
    string date;
    double openPrice;
    double dailyHigh;
    double dailyLow;
    double closePrice;
    long long int tradeVol;
    string symbol;
};

struct stock {
    string ticker;
    vector<day> stockInfo;
};

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

void printStock(const stock& s){
    cout << "Ticker: " << s.ticker << endl;
    display(s.stockInfo.back());
}

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

double latestClose(const stock& stock){
    if (stock.stockInfo.size() < 1){
	return -1;
    }
    double lastClosePrice;
    lastClosePrice = stock.stockInfo.back().closePrice;
    return lastClosePrice;
}

double prevClose(const stock& stock){
    if (stock.stockInfo.size() < 2){
	return -1;
    }
    double prevClosePrice;
    prevClosePrice = stock.stockInfo.at(stock.stockInfo.size() - 2).closePrice;
    return prevClosePrice;
}

double getPercentChange(const stock& stock){
    double lastClosePrice = latestClose(stock);
    double prevClosePrice = prevClose(stock);
    if (lastClosePrice == -1 || prevClosePrice == -1){
	return -1000;
    }
    double percentChange = (lastClosePrice - prevClosePrice) / prevClosePrice * 100;
    return percentChange;
}

double avgClose(const stock& stock, int days){
    if (days < 1 || days > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    double total = 0;
    double avg;
    for (int i = 0; i < days; i++){
	total += stock.stockInfo.at(stock.stockInfo.size() - 1 - i).closePrice;	
    }
    avg = total / days;
    return avg;
}

double stdDevClose(const stock& stock,  int days){
    if (days < 1 || days > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    double total = 0;
    double average = avgClose(stock, days);
    double stdDev;
    for (int i = 0; i < days; i++){
	double lastClose = stock.stockInfo.at(stock.stockInfo.size() - 1 - i).closePrice;	
	double distance = lastClose - average;
	total += pow(distance,2);
    }
    stdDev = total / days;
    stdDev = sqrt(stdDev);
    return stdDev;
}

double getZScore(const stock& stock){
    int days = 20;
    double zscore;
    double averageClose = avgClose(stock, days);
    double lastClose = latestClose(stock);
    double stdDev = stdDevClose(stock, days);
    if (averageClose == -1 || stdDev == -1 || stdDev == 0){
	return -1000;
    }
    zscore = (lastClose - averageClose) / stdDev;
    return zscore;
}

bool theAlgorithm(const stock& stock){
    double zscore = getZScore(stock);
    if (zscore <= -2){
	return true;
    }
    return false;
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
