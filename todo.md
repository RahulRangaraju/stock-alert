# TODO

## Next up
- [ ] Test Analysis Settings (set date, check indicators on an older date)
- [x] Current `downStreak(stock, endIndex)` (separate from longest)
- [x] `gapPercent`,
- [ ]  then `closeLocation`
## Indicators
- [x] z-score, volume ratio, longest downstreak
- [ ] gapPercent
- [ ] closeLocation
- [x] trendRatio (close / avgClose over TREND_WINDOW)
- [ ] drawdownFromHigh
- [ ] volatilityRatio
- [ ] RSI
- [ ] Add each to the Indicators menu

## Algorithm and backtest
- [ ] Vote-count theAlgorithm with named-constant thresholds
- [ ] Backtest loop: 1/5/10-day forward returns vs. all-days baseline
- [ ] Unit tests for analysis functions

## Cleanup
- [ ] Format numbers (2-3 decimals, reset `fixed` after)
- [ ] Show "As of <date>" on indicator output
- [ ] Remove commented-out code and redundant size() checks
- [ ] README (build/run steps, design decisions, limitations)

## Later (ideas)
- Class refactor (Indicator base class), export results JSON + hosted page, live data

## Conventions
- Sentinels: -1 for non-negative values, -1000 for values that can be negative
- Windows are named constants in main.cpp
- Never use data after endIndex (no lookahead)
