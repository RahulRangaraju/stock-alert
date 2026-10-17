#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

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

bool theAlgorithm(const stock& stock){
	return true;
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

int main(){
    vector<string> names = {"NVDA", "AAPL", "MU", "MSFT", "IREN", "INTC"};
    vector<stock> stocks;
    for ( const string& name : names ){
	stocks.push_back(loadStock(name));
    }
    for (const stock& stock : stocks){
	cout << stock.ticker << endl;
	cout << stock.stockInfo.size() << endl;
	cout << latestClose(stock) << endl;
	cout << prevClose(stock) << endl;
	cout << getPercentChange(stock) << endl;
    }
    return 0;
}
