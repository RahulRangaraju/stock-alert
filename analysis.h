#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "stock.h"

double latestClose(const stock&);
double prevClose(const stock&);
double getPercentChange(const stock&);
double avgClose(const stock&, int, int);
double stdDevClose(const stock&, int, int);
double getZScore(const stock&, int);
bool theAlgorithm(const stock&, int);

#endif 
