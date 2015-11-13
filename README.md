# Eclipsed

CMake
C++11-ish

## Overall goals
1. Game simulation 2-6 players
2. Gather statistics on best races, strategies for each race, etc.

## Data Model/Flow:
JSON Races, Ships, etc.? Will better allow for add-ons
JSON Game initial state

## TODO
1. Limit players to one race from each side of player board
2. Alpha–beta pruning -- going to need this as there are many really stupid moves in this game
3. AI Players min/max, humanize to min/max +/- 10%, etc.
4. Adjustable AI look-ahead

## Notes
Mitigating Horizon Effect? What are important moves? System capture, player death, etc.?
Game limited to 9 rounds

http://doc.qt.io/qt-5/cmake-manual.html

This guy is pretty cool - http://neverstopbuilding.com/minimax
