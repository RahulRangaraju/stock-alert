#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "stock.h"

double latestClose(const stock&, int);
double prevClose(const stock&, int);
double latestOpen(const stock&, int);
double prevOpen(const stock&, int);
double openToCloseChange(const stock&, int);
double getPercentChange(const stock&, int);
double avgClose(const stock&, int, int);
double stdDevClose(const stock&, int, int);
double getZScore(const stock&, int, int);
bool theAlgorithm(const stock&, int, int);
double avgVolume(const stock&, int, int);
double volumeRatio(const stock&, int, int);

#endif 
