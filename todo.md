# TODO

## Next up
- [x] Set real window defaults in main.cpp (placeholders are at max)
- [ ] Show window length in ZScore, Trend Ratio, and Volume Ratio output (like RSI)
- [ ] Add N/A sentinel checks for ZScore (-1000) and Trend Ratio (-1) in the menu
- [ ] Indicators menu: Show All / Search by date / Search by date range
- [ ] One `displayIndicators(chosen, endIndex)` used by all three
- [ ] Show "As of <date>" on indicator output

## Indicators
- [x] z-score, volume ratio
- [x] longest + current downstreak
- [x] trendRatio, gapPercent, closeLocation
- [x] drawdownFromHigh, volatilityRatio, RSI
- [x] All added to the Indicators menu

## Algorithm and backtest
- [ ] Vote-count theAlgorithm with named-constant thresholds
- [ ] Backtest loop: 1/5/10-day forward returns vs. all-days baseline
- [ ] Unit tests for analysis functions
- [ ] README (build/run steps, design decisions, limitations)

## Cleanup
- [ ] Format numbers (2-3 decimals, reset `fixed` after)
- [ ] Remove commented-out code, unused variables, redundant size() checks
- [ ] Remove old Analysis Settings option once date search works

## Later (ideas)
- Class refactor (Indicator base class; adding an indicator touches 4 files)
- Export results JSON + hosted page, live data
- CLI / ClaudeFrontEnd branches, SSH key setup, make repo public

## Conventions
- Sentinels: -1 for non-negative values, -1000 for values that can be negative
- Windows are named constants in main.cpp
- Never use data after endIndex (no lookahead)
- Never squash commits; stage files by name
