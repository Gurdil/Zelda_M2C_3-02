
#ifndef ZAVATAR_H
#define ZAVATAR_H

#include <stdlib.h>

#include "zanimator.h"
#include "zobject.h"

class ZAvatar : public ZObject
{
public:
    ZAvatar(int x, int y);
    ~ZAvatar();

    enum action{
        STAND,
        WALK,
        ATTACK,
        HURT,
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

    void moveAvatar();




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
