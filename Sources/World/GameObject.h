#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

class GameObject
{
public:
	GameObject() {};
    virtual ~GameObject() {};

    int getX() { return x; };
    int getY() { return y; };
    void setX(int x) { this->x = x; };
    void setY(int y) { this->y = y; };

private:
    int x, y;
};

#endif
