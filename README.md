# Core Idea
A game for the Nintendo DS that has the player make paths 
between countries on the world map. Uses a graph of 
countries and breadth first search (BFS).

Inspired by [Travle](https://imois.in/games/travle/) by 
Oisin Carroll.
# How to Play
# How to Build
```sh
cd assets
./convert.sh
cd ..
make
desmume graph.nds
```
# Technologies and libraries used
- C programming language
- GNU compiler collection
- LibNDS and NightFoxLib for interfacing with the Nintendo DS 
- LibCheck for unit testing 
# Features
- Graph C module working: construction, adjacency, pathfinding.
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
