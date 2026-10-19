#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

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

vector<day> historicalData(const string&);
stock loadStock(const string&);
void display(const day&);
void display(const vector<day>&);
void printStock(const stock&);

#endif
