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
* Mitigating Horizon Effect? What are important moves? System capture, player death, etc.?
* Game limited to 9 rounds
* Might want to have option for statistical avgs of combat (pass-fail) instead of chance
* Same as above for sector generation


## Possible games states
* 37 sectors hexes,
* 1 predetermined
* 2-5 starting locations
* We'll say 36 more-or-less random hexes

### each player can do actions:
* build, upgrade, research, explore, move, influence, colonize, diplomacy
* can build as minerals allow, 5 types of ships, orbital, monolith (if available)
* upgrade 2-3 ships
* explore single tile
* move 2-3 ships at a time
* explore and place then orient a tile so many ways
* research 1-2 (3?) things of whatever is available
* pass, then do limited reactions (upgrade, build, move)

## Plan of Attack
- Do nothing and pass
- Upkeep
- Colonize home system, do upkeep (no vp)
- Explore action, choose sector (ship/disc adjacent), choose location, and orientation (wormholes must align) tiles (no vp)
- Colonize non-combat discovered sectors (first vp)
- Build ships/orbitals/monoliths
- Combat (huge)
- Research tech (huge)
- Upgrade (huge)
- etc.

http://doc.qt.io/qt-5/cmake-manual.html

This guy is pretty cool - http://neverstopbuilding.com/minimax
