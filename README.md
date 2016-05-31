# Eclipsed

CMake
C++11-ish

## Overall goals
1. Game simulation 2-6 players
1. Gather statistics on best races, strategies for each race, etc.

## Data Model/Flow:
JSON Races, Ships, etc.? Will better allow for add-ons
JSON Game initial state

## TODO
1. Assigning value to actions before a round ends (where actual VP might be earned) to distinguish good actions from bad ones. I'm guessing all actions are equal until the round ends.
1. ~--All heap allocated stuff leaks, no deletes.--~
1. Limit players to one race from each side of player board
1. Alpha–beta pruning -- going to need this as there are many really stupid moves in this game
1. AI Players min/max, humanize to min/max +/- 10%, etc.
1. Adjustable AI look-ahead
1. Giant hashmap of gamestates to avoid dupes? (Dynamic programming)

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

### Search Cost
All possible player actions:
* build up to 6 or so things limited by m
* upgrade 2/6 or 3/6 ships with x number of upgrades available
* research R techs with s science
* exp 1/3 rings, with various placement around the map
* move 2/3 units anywhere possible on map
* influence x number of colones for I influence
* colonize 1-3 (decolonize as well)
* form diplomacy with x players (as boards permit)

1st approx. at 270,000,000 possible moves per action
Looks like you aren't going to be able to simulate more than a few moves, space limited?

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
1. Do nothing and pass
1. Upkeep
1. Colonize home system, do upkeep (no vp)
1. Explore action, choose sector (ship/disc adjacent), choose location, and orientation (wormholes must align) tiles (no vp)
1. Colonize non-combat discovered sectors (first vp)
1. Build ships/orbitals/monoliths
1. Combat (huge)
1. Research tech (huge)
1. Upgrade (huge)
1. etc.

http://doc.qt.io/qt-5/cmake-manual.html

This guy is pretty cool - http://neverstopbuilding.com/minimax
