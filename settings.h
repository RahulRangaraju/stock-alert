#ifndef SETTINGS_H
#define SETTINGS_H

struct AnalysisSettings {
    int zScoreWindow = 30;
    int volumeWindow = 30;
    int trendWindow = 30;
    int drawdownWindow = 30;
    int volatilityWindow = 14;
    int rsiWindow = 14;
};

void viewSettings(const AnalysisSettings&);

#endif

