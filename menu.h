#ifndef MENU_H
#define MENU_H

#include <vector>
#include <iostream>
#include "stock.h"

void displayMenu();
void displayStocks(const vector<stock>&);
int getChoice(int, int);
int getSettingsChoice(int, int);
void displayPriceHistory(const stock&, int, int);
void priceHistoryMenu();
void indicatorMenu();
void settingsMenu();
void indicatorSettingsMenu();

#endif
