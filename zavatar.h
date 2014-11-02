
#ifndef ZAVATAR_H
#define ZAVATAR_H

#include <stdlib.h>

#include "zobject.h"

class ZAvatar : public ZObject
{
public:

    enum action{
        STAND,
        WALK,
        ATTACK,
        DEAD
    };

    enum currentPos{
        DOWN,
        LEFT,
        UP,
        RIGHT
    };


    //bool collide(ZObject object, deth level);

    int getX();
    int getY();
    int setPos(int x,int y);

    moveAvatar();




private:
    Zanimator moveDown;
    Zanimator moveLeft;
    Zanimator moveUp;
    Zanimator moveRight;
    Zanimator attack;

    int x;
    int y;
   // int centerX;
   // int centerY;

    int speed;




};

#endif // ZAVATAR_H
