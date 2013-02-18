#ifndef _KEYBOARD_LISTENER_H
#define _KEYBOARD_LISTENER_H

class KeyboardListener
{
public:
    bool onKeyDown(unsigned char c)
    {
        return false;
    };
    bool onSpecialKeyDown(int key)
    {
        return false;
    };
};

#endif
