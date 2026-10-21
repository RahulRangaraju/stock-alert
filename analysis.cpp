#include <cmath>
#include <string>
#include <algorithm>
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

int findDateIndex(const stock& stock, const string& date){
    for (int i = 0; i < static_cast<int>(stock.stockInfo.size()); i++){
	if (date == stock.stockInfo.at(i).date.substr(0, 10)){
	    return i;
	}	
    }
    return -1;
}

double drawdownFromHigh(const stock& stock, int days, int endIndex){
    if (days > endIndex + 1 || endIndex < 0 || endIndex > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1000;
    } 
    double rangeHigh = stock.stockInfo.at(endIndex).dailyHigh;
    double todayClose = stock.stockInfo.at(endIndex).closePrice;
    for (int i = 0; i < days; i++){
	if (stock.stockInfo.at(endIndex - i).dailyHigh > rangeHigh){
	rangeHigh = stock.stockInfo.at(endIndex - i).dailyHigh;
	}
    }
    double drawdown = ( todayClose - rangeHigh ) / rangeHigh * 100;
    return drawdown;
}

double trueRange(const stock& stock, int endIndex){
    if (endIndex < 1 || endIndex > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1;
    }
    double high = stock.stockInfo.at(endIndex).dailyHigh;
    double low = stock.stockInfo.at(endIndex).dailyLow;
    double prevClose = stock.stockInfo.at(endIndex - 1).closePrice;
    double range1 = high - low;
    double range2 = abs(high - prevClose);
    double range3 = abs(low - prevClose);
    double realRange = max({range1,range2,range3});
    return realRange;
}

double volatilityRatio(const stock& stock, int days, int endIndex){
    if (endIndex - days < 0 || days < 1 || endIndex > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1;
    }
    double todayRange = trueRange(stock, endIndex);
    double averageRange = 0;
    for (int i = 0; i < days; i++){
	averageRange += trueRange(stock, endIndex - i);
    }
    averageRange /= days;
    if (averageRange == 0){
	return -1;
    }
    return todayRange / averageRange;
}

double gapPercent(const stock& stock, int endIndex){
    if (endIndex < 1 || endIndex > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1000;
    }
    double percent;
    double todaysOpen = stock.stockInfo.at(endIndex).openPrice;
    double yesterdaysClose = stock.stockInfo.at(endIndex - 1).closePrice;
    percent = ( todaysOpen - yesterdaysClose ) / yesterdaysClose * 100;
    return percent;
}

double closeLocation(const stock& stock, int endIndex){
    if (endIndex < 0 || endIndex > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1;
    }
    double high = static_cast<double>(stock.stockInfo.at(endIndex).dailyHigh);
    double low = static_cast<double>(stock.stockInfo.at(endIndex).dailyLow);
    double range = high - low;
    if (range <= 0){
	return -1;
    }
    double distFromLow = static_cast<double>(stock.stockInfo.at(endIndex).closePrice) - low;
    double location = distFromLow / range;
    return location;
}

int longestDownStreak(const stock& stock, int endIndex){
    int count = 0;
    int longestStreak = 0;
    if (endIndex < 1 || endIndex > static_cast<int>(stock.stockInfo.size())){
	return -1;
    }
    for (int i = 0; i + 1 <= endIndex; i++){
	if (stock.stockInfo.at(i).closePrice > stock.stockInfo.at(i + 1).closePrice){
	    count++;
	}
	else {
	    if (count > longestStreak){
		longestStreak = count;
	    }
	    count = 0;
	}
    }
    return longestStreak;
}

int currentDownStreak(const stock& stock, int endIndex){
    int count = 0;
    int i = endIndex;
    int j = i - 1;
    if (i < 0 || j < 0 || i > static_cast<int>(stock.stockInfo.size()) - 1){
	return -1;
    }
    if (endIndex < 1){
	return 0;
    }
    while (j >= 0 && stock.stockInfo.at(i).closePrice < stock.stockInfo.at(j).closePrice){
	count++;
	i--;
	j--;
    }
    return count;
}

double trendRatio(const stock& stock, int days, int endIndex){
    if (endIndex < 0 || endIndex >= static_cast<int>(stock.stockInfo.size()) || days > endIndex + 1){
	return -1;
    }
    double ratio;
    double total = 0;
    double closeRecentDay = stock.stockInfo.at(endIndex).closePrice;
    for (int i = 0; i < days; i++){
	total += stock.stockInfo.at(endIndex - i).closePrice;
    }
    double average = total / days;
    ratio = closeRecentDay / average;
    return ratio;
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

