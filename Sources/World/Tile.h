#ifndef _TILE_H
#define _TILE_H

class Tile
{
public:
    Tile(int x, int y);
    ~Tile();

    void display();

    int getX() { return x; };
    int getY() { return y; };

private:
    int x, y;
};

#endif
