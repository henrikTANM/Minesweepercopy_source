#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile();
    Tile(char, bool);

    char value;
    bool revealed;
};

#endif // TILE_H
