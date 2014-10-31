#ifndef ZOBJECT_H
#define ZOBJECT_H

#include <stdlib.h>

#include "zanimator.h"
#include "zinit.h"

class ZObject
{
public:
    ZObject(Zanimator animator,int x, int y);
    enum deth{
        innerCircle,
        outerCircle,
        rectangle,
        pixel
    };

    bool collide(ZObject object, deth level);

    int getX();
    int getY();
    void setPos(int x, int y);
    QPixmap getImage();

private:
    Zanimator animator;
    int x;
    int y;

    bool rectangleCollide(ZObject object);
    bool pixelCollide(ZObject object);

};

#endif // ZOBJECT_H
