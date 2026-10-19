#include <cmath>
#include "analysis.h"

using namespace std;

double latestClose(const stock& stock, int endIndex){
    if (endIndex < 0 || endIndex >= static_cast<int>(stock.stockInfo.size())){
        return -1;
    }
    if (stock.stockInfo.size() < 1){
	return -1;
    }
    double lastClosePrice;
    lastClosePrice = stock.stockInfo.at(endIndex).closePrice;
    return lastClosePrice;
}

double prevClose(const stock& stock, int endIndex){
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    if (stock.stockInfo.size() < 2){
	return -1;
    }
    double prevClosePrice;
    prevClosePrice = stock.stockInfo.at(endIndex - 1).closePrice;
    return prevClosePrice;
}

double latestOpen(const stock& stock, int endIndex){
    if (endIndex < 0 || endIndex >= static_cast<int>(stock.stockInfo.size())){
        return -1;
    }
    if (stock.stockInfo.size() < 1){
	return -1;
    }
    double lastOpenPrice;
    lastOpenPrice = stock.stockInfo.at(endIndex).openPrice;
    return lastOpenPrice;
}

double prevOpen(const stock& stock, int endIndex){
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    if (stock.stockInfo.size() < 2){
	return -1;
    }
    double prevOpenPrice;
    prevOpenPrice = stock.stockInfo.at(endIndex - 1).openPrice;
    return prevOpenPrice;
}

double openToCloseChange(const stock& stock, int endIndex){
    if (endIndex < 0 || endIndex >= static_cast<int>(stock.stockInfo.size())){
	return -1000;
    }
    double lastOpenPrice = latestOpen(stock, endIndex);
    if (lastOpenPrice == 0){
	return -1000;
    }
    double lastClosePrice = latestClose(stock, endIndex);
    double percentChange = ( lastClosePrice - lastOpenPrice ) / lastOpenPrice * 100;
    return percentChange;
}

double getPercentChange(const stock& stock, int endIndex){
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size())){
	return -1000;
    }
    double lastClosePrice = latestClose(stock, endIndex);
    double prevClosePrice = prevClose(stock, endIndex);
    if (prevClosePrice == 0){
	return -1000;
    }
    double percentChange = (lastClosePrice - prevClosePrice) / prevClosePrice * 100;
    return percentChange;
}

double avgClose(const stock& stock, int days, int endIndex){
    if (days < 1 || days > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size()) || days > endIndex + 1){
	return -1;
    }
    double total = 0;
    double avg;
    for (int i = 0; i < days; i++){
	total += stock.stockInfo.at(endIndex - i).closePrice;	
    }
    avg = total / days;
    return avg;
}

double avgVolume(const stock& stock, int days, int endIndex){
    if (days < 1 || days > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size()) || days > endIndex){
	return -1;
    }
    double volume;
    double total = 0;
    for (int i = 0; i < days; i++){
	total += static_cast<double>(stock.stockInfo.at(endIndex - (i + 1)).tradeVol);
    }
    volume = total / days; 
    return volume;
}

double volumeRatio(const stock& stock, int days, int endIndex){
    double ratio; 
    double avg = avgVolume(stock, days, endIndex);
    if (avg <= 0){
	return -1;
    }
    ratio = static_cast<double>(stock.stockInfo.at(endIndex).tradeVol) / avg;
    return ratio;
}

double stdDevClose(const stock& stock,  int days, int endIndex){
    if (days < 1 || days > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    if (endIndex < 1 || endIndex >= static_cast<int>(stock.stockInfo.size()) || days > endIndex + 1){
	return -1;
    }
    double total = 0;
    double average = avgClose(stock, days, endIndex);
    double stdDev;
    for (int i = 0; i < days; i++){
	double lastClose = stock.stockInfo.at(endIndex - i).closePrice;	
	double distance = lastClose - average;
	total += pow(distance,2);
    }
    stdDev = total / days;
    stdDev = sqrt(stdDev);
    return stdDev;
}

double getZScore(const stock& stock, int days, int endIndex){
    double zscore;
    double averageClose = avgClose(stock, days, endIndex);
    double stdDev = stdDevClose(stock, days, endIndex);
    if (averageClose == -1 || stdDev == -1 || stdDev == 0){
	return -1000;
    }
    zscore = (stock.stockInfo.at(endIndex).closePrice - averageClose) / stdDev;
    return zscore;
}

double drawdownFromHigh(const stock&, int, int){
    return -1;
}

double volatilityRatio(const stock&, int, int){
    return -1;
}

double gapPercent(const stock&, int){
    return -1;
}

double closeLocation(const stock&, int){
    return -1;
}

int downStreak(const stock&, int){
    return -1;
}

bool theAlgorithm(const stock& stock, int days, int endIndex){
    double zscore = getZScore(stock, days, endIndex);
    if (zscore == -1000){
	return false;
    }
    else if (zscore <= -2){
	return true;
    }
    return false;
}

