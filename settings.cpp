#include "settings.h"
#include <iostream>

using namespace std;

void viewSettings(const AnalysisSettings& settings){
    cout << "********************************" << endl;
    cout << "ZScore Window Length: " << settings.zScoreWindow << endl;
    cout << "RSI Window Length: " << settings.rsiWindow << endl;
    cout << "Trend Ratio Window Length: " << settings.trendWindow << endl;
    cout << "Volume Ratio Window Length: " << settings.volumeWindow << endl;
    cout << "Drawdown Window Length: " << settings.drawdownWindow << endl;
    cout << "Volatility Ratio Window Length: " << settings.volatilityWindow << endl;
    cout << "********************************" << endl;
}

