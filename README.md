# Core Idea
A game for the Nintendo DS that has the player make paths between countries on the world map. Uses graph theory and breadth first search.
A reimplementation of [Travle](https://imois.in/games/travle/) by Oisin Carroll.
# Technologies and libraries used
- C programming language
- GNU compiler collection
- (will use) LibNDS, part of devkitpro
- LibCheck for unit testing 
# Wishlist
- Graph with the countries of the world as vertices and their land borders as vertices.
- Functions to check adjacency and compute paths between them with A*.
- Game loop:
  - Game selects two random countries that are on the same landmass.
  - Prompts user to enter country names to construct a path.
  - Game computes a route to compare player’s performance to: a lower score is better.
- Player can upload and download scores to and from an internet leaderboard.
- Scores are stored in a PostgreSQL database.
- Simple, satisfactory 2d world map.
- Player can zoom in/out and pan on the world map.
# License
**TBD**
