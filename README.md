# chess_flavour
This repository contains code for a game like chess with much less features and a few variations.

#COMPILATION

g++ -Wall main.cpp chess.cpp -o chess

This code includes 2 classes i.e. Spot (which basically resembles to each square in the chess board) and
Board which resembles the whole board.

Players and Pieces were used as enums

Tried to do input string processing to avoid input errors, however not checked thoroughly.

Tried to make this code shorter. Need to think a bit more on the design aspect. Focus was more into completion
of the task.

Left & Right for both players are assumed to be same. However Forward & Backward is taken differently.
For A forward means going up in row & for B forward is goinf down on row.

# TODO
Can create a computer opponet to play which might help a lot in debugging the code and finding unknown bugs.

Option to Save the game state will also help a lot to improve game quality.

A menu or help section is required  for much better user friendlyness
