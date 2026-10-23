#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>
#include "stock.h"
#include "settings.h"

void displayMenu();
void displayStocks(const vector<stock>&);
int getChoice(int, int);
int getSettingsChoice(int, int);
void displayPriceHistory(const stock&, int, int);
void priceHistoryMenu();
void indicatorMenu();
void settingsMenu();
void indicatorSettingsMenu();
void runPriceHistory(const stock&, int);
void runIndicators(const stock&, const AnalysisSettings&, int);
void changeSettings(const stock&, AnalysisSettings&);
int changeStock(const vector<stock>& stocks);

#endif
