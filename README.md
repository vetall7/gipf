# GIPF Game Solver

## Introduction

This project consists of two parts:

1. **Generalized Game Engine:** The first part implements a generalized version of the GIPF game engine. Generalization introduces a list of parameters (denoted as L) describing the game, allowing for easy modification of its characteristics such as board size, the number of pieces required for a specific combination triggering certain effects, etc.

2. **Game Solver:** The second part implements a program that solves the GIPF game or certain states of the game for different values of the parameters in list L. The solving algorithm primarily employs the minimax algorithm (or its variation, negamax) along with alpha-beta pruning.

GIPF is a deterministic two-player game without random elements or hidden information, adhering to a zero-sum principle without draws. The official rules of the game can be found [here]([official_rules_link](https://www.riograndegames.com/wp-content/uploads/2013/02/GIPF-Rules.pdf)). 

## Generalized Game Engine

In the generalized version of the GIPF game engine, the following parameters are introduced:

- **S (Board Size):** The number of hexagonal board fields on each side of the board.
- **K (Pieces for Collection):** The number of player pieces that trigger the collection of pieces.
- **GW (White Player Pieces):** The number of pieces belonging to the white player.
- **GB (Black Player Pieces):** The number of pieces belonging to the black player.

### Functions:

- **LOAD_GAME_BOARD:** Loads the game board state along with the game parameters.
- **PRINT_GAME_BOARD:** Prints the current state of the board.
- **DO_MOVE \<xN - yM\>:** Performs the given move for the active player on the current board.
- **PRINT_GAME_STATE:** Prints the current game state.
- **GEN_ALL_POS_MOV:** Prints a list of all possible moves leading to unique board states.
- **GEN_ALL_POS_MOV_EXT:** Prints a list of all possible moves, but only one winning move if available.
- **GEN_ALL_POS_MOV_NUM:** Prints the number of all possible moves.
- **GEN_ALL_POS_MOV_EXT_NUM:** Prints the number of all possible moves, but only one winning move if available.
- **WINNING_SEQUENCE_EXIST \<N\>:** Answers whether there exists a winning sequence of moves of length less than or equal to N for any player.
- **SOLVE_GAME_STATE:** Determines which player has a winning strategy for the given game state.
