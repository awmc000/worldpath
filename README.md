# Core Idea
A game for the Nintendo DS that has the player make paths 
between countries on the world map. Uses a graph of 
countries and breadth first search (BFS).

Inspired by [Travle](https://imois.in/games/travle/) by 
Oisin Carroll.

Thanks to [larsenml](https://larsenml.net) for help fixing bugs
in the early stages of development.
# How to Play
- At the beginning of a round, you are assigned a starting
country and a destination country.
- Hit "B" to check your assignment and your current path
at any time.
- Use the D-pad to navigate the alphabetically organized
pages of countries.
- Use "A" to select a country and add it to the path.
- You need to add the starting country to your path,
and remember the ending country when you are done.
- Hit "Y" at any time to see the countries which border
the most recently added country.
  - Eg. if you just selected USA, you would get a list
with Canada and Mexico.

# How to Build
On a Linux system (tested on Arch), you can build and play
the game by running these commands:
```sh
cd assets
./convert.sh
cd ..
make
desmume worldpath.nds
```
# Technologies and libraries used
- C programming language
- GNU compiler collection
- LibNDS and NightFoxLib for interfacing with the Nintendo DS 
- LibCheck for unit testing 
# Features
- Graph logic: construction, adjacency, pathfinding.
- Countries of the world graph and basic game logic working.
- Implemented as text based game with visuals (dots on the map).
# Rights Information
Worldpath is a homebrew geography game for the Nintendo DS.
Copyright (C) 2024 Alex McColm

This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program. If not, see https://www.gnu.org/licenses/.
