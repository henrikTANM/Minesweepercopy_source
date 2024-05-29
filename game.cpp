#include "game.h"
#include "tile.h"
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <QDebug>

using namespace std;

Game::Game(int rows, int cols, int mines) {
    this->rows = rows;
    this->cols = cols;
    this->mines = mines;
    this->board = generateBoard();
    this->running = true;
}

Tile** Game::generateBoard() {
    Tile** board = new Tile*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new Tile[cols];
        /*
        for (int j = 0; j < cols; j++) {
            board[i][j] = '-';
        }
        */
    }

    srand(time(NULL)|clock());

    for (int b = 0; b < mines; b++) {
        while(true) {
            int randX = rand() % (rows);
            int randY = rand() % (cols);
            Tile *randLoc = &board[randX][randY];
            if (randLoc->value != 'x') {
                randLoc->value = 'x';
                break;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile *current = &board[i][j];
            if (current->value != 'x') {
                vector<tuple<int, int>> neighbours = getNeighbours(i, j);
                int value = 0;
                for (tuple<int, int> tu : neighbours) {
                    if (board[get<0>(tu)][get<1>(tu)].value == 'x') { value++; }
                }
                current->value = '0' + value;
                //qDebug() << current->value;
            }
        }
    }
    return board;
}

bool Game::checkLoc(Tile *tile) {
    return tile->value == 'x';
}

vector<tuple<int, int>> Game::getNeighbours(int i, int j) {
    vector<tuple<int, int>> *neighbours = new vector<tuple<int, int>>;

    if (i + 1 < rows) {
        neighbours->push_back(tuple(i+1, j));
        if (j + 1 < cols) { neighbours->push_back(tuple(i+1, j+1)); }
        if (j - 1 >= 0) { neighbours->push_back(tuple(i+1, j-1)); }
    }
    if (i - 1 >= 0) {
        neighbours->push_back(tuple(i-1, j));
        if (j + 1 < cols) { neighbours->push_back(tuple(i-1, j+1)); }
        if (j - 1 >= 0) { neighbours->push_back(tuple(i-1, j-1)); }
    }
    if (j + 1 < cols) { neighbours->push_back(tuple(i, j+1)); }
    if (j - 1 >= 0) { neighbours->push_back(tuple(i, j-1)); }

    return *neighbours;
}

tuple<vector<tuple<int, int>>, bool> Game::reveal(int i, int j) {
    vector<tuple<int, int>> newRevealedTiles;
    if (board[i][j].revealed == false) {
        board[i][j].revealed = true;
        if (board[i][j].value == '0') {
            newRevealedTiles = revealNeighbours(i, j);
        }
        if (board[i][j].value == 'x') {
            return tuple(revealAll(), true);
        }
        newRevealedTiles.push_back(tuple(i, j));
    }
    return tuple(newRevealedTiles, true);
}

vector<tuple<int, int>> Game::revealNeighbours(int i, int j) {
    vector<tuple<int, int>> newRevealedTiles;
    vector<tuple<int, int>> neighbours = getNeighbours(i, j);
    for (tuple<int, int> tu : neighbours) {
        tuple<vector<tuple<int, int>>, bool> revealedTiles = reveal(get<0>(tu), get<1>(tu));
        for (tuple<int, int> revealedTile : get<0>(revealedTiles)) {
            newRevealedTiles.push_back(revealedTile);
        }
    }
    return newRevealedTiles;
}

vector<tuple<int, int>> Game::revealAll() {
    vector<tuple<int, int>> allRevealedTiles;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j].revealed = true;
            allRevealedTiles.push_back(tuple(i, j));
        }
    }
    return allRevealedTiles;
}

bool Game::checkAllRevealed() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QDebug dbg(QtDebugMsg);
            dbg << board[i][j].revealed;
            if (!board[i][j].revealed & (board[i][j].value != 'x')) { return false; };
        }
    }
    return true;
}

void Game::printBoard() {
    QDebug dbg(QtDebugMsg);
    for (int i = 0; i < rows; ++i) {
        dbg << "\n";
        for (int j = 0; j < cols; ++j) {
            if (board[i][j].revealed) { dbg << board[i][j].value; }
            else { dbg << '-'; }
        }
        dbg << " ";
        for (int j = 0; j < cols; ++j) {
            dbg << board[i][j].value;
        }
    }
}
