#include <cmath>
#include "analysis.h"

using namespace std;

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
    int days = 200;
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
    if (zscore == -1000){
	return false;
    }
    else if (zscore <= -2){
	return true;
    }
    return false;
}


