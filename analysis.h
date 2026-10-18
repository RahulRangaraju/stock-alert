#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "stock.h"

double latestClose(const stock&);
double prevClose(const stock&);
double getPercentChange(const stock&);
double avgClose(const stock&, int);
double stdDevClose(const stock&, int);
double getZScore(const stock&);
bool theAlgorithm(const stock&);

#endif 
