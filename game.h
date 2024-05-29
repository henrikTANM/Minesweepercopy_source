#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include <vector>
#include <tuple>

using namespace std;

class Game
{
public:
    Game(int, int, int);
    Tile** board;
    int rows;
    int cols;
    int mines;
    bool running;

    void printBoard();
    vector<tuple<int, int>> getNeighbours(int, int);
    tuple<vector<tuple<int, int>>, bool> reveal(int, int);
    vector<tuple<int, int>> revealNeighbours(int, int);
    vector<tuple<int, int>> revealAll();
    bool checkAllRevealed();

private:

    Tile** generateBoard();
    bool checkLoc(Tile *);
};

#endif // GAME_H
