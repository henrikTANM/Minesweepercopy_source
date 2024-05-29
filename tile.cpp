#include "tile.h"

Tile::Tile() {
    this->value = '-';
    this->revealed = false;
}

Tile::Tile(char value, bool revealed) {
    this->value = value;
    this->revealed = revealed;
}
