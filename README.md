# Tic-Tac-Toe
C++ Tic-tac-toe project made for [COMP.CS.110-course](https://sis-tuni.funidata.fi/student/courseunit/otm-e878d5ba-a064-4064-9b30-71b4042dceea/brochure) in autumn 2021.

[Main.cpp](main.cpp) contains the game logic for tic-tac-toe. The game is played in console as seen below ([Play online](https://onlinegdb.com/k0DUm2bmH)).

![](https://i.imgur.com/49N5n1d.gif)

The game is started by 'X' and it asks for it's coordinates. When coordinates are given, the board is printed again with the added mark. Then the game asks coordinates for '0'. This continues until 'q' is given or either player has a line full of it's own marks horizontally, vertically or diagonally. 

The gameboard can be also expanded when given coordinates +1 or -1 out of bounds of the current board:

![](https://i.imgur.com/1zq7mtL.gif)
