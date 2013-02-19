#ifndef _TILE_H
#define _TILE_H

class Tile
{
public:
    Tile(int x, int y) { this->x = x; this->y = y; };
    ~Tile() {};

    int getX() { return x; };
    int getY() { return y; };

private:
    int x, y;
};

#endif
