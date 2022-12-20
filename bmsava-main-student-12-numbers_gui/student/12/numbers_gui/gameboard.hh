/* Module: GameBoard / File: gameboard.hh
 * Includes the data and functionality of the gameboard.
 */


#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "numbertile.hh"
#include <vector>
#include <random>

const int SIZE = 4;
const int PRINT_WIDTH = 5;
const int NEW_VALUE = 2;
const int DEFAULT_GOAL = 2048;

const Coords UP = {-1, 0};
const Coords DOWN = {1, 0};
const Coords LEFT = {0, -1};
const Coords RIGHT = {0, 1};
const Coords DEFAULT_DIR = {0,0};

class GameBoard
{
public:
    // Constructor
    GameBoard();

    // Destructor
    ~GameBoard();

    // Initializes the gameboard with nullptrs.
    void init_empty();

    // Initializes the random number generator and fills the gameboard
    // with random numbers.
    void fill(int& seed);

    // Draws a new location (coordinates) from the random number generator and
    // puts the NEW_VALUE on that location, unless check_if_empty is true and
    // the gameboard is full.
    void new_value(bool check_if_empty = true);

    // Returns true, if all the tiles in the game board are occupied,
    // otherwise returns false.
    bool is_full() const;

    // Prints the game board.
    void print() const;

    // Moves the number tiles in the gameboard, if possible (by calling
    // move method for each number tile).
    // Finally, resets turn of all number tiles.
    bool move(Coords dir, int goal);

    // Sets the values of tiles back to 0 (empty) when the game is reseted.
    void reset();

    // Returns the element (number tile) in the given coordinates.
    NumberTile* get_item(Coords coords);

private:
    // Internal structure of the game board
    std::vector<std::vector<NumberTile*>> board_;

    // Random number generator and distribution,
    // they work better, if they are attributes of a class.
    std::default_random_engine randomEng_;
    std::uniform_int_distribution<int> distribution_;
};

#endif // GAMEBOARD_HH
