#include "zobject.h"

ZObject::ZObject(Zanimator animator, int x, int y) : animator(animator), x(x), y(y)
{
}

bool ZObject::collide(ZObject object, deth level)
{
    switch (level)
    {
    case innerCircle:
        return true;
        break;
    case outerCircle:
        return true;
        break;
    case rectangle:
        return this->rectangleCollide(object);
        break;
    case pixel:
        return this->pixelCollide(object);
        break;
    }
}

void ZObject::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void ZObject::setOffset(int x, int y)
{
    this->offsetX = x;
    this->offsetY = y;
}

QPixmap ZObject::getImage()
{
    return animator.next();
}

bool ZObject::rectangleCollide(ZObject object)
{
    int x1 = this->x ;
    int x2 = object.x;
    int y1 = this->y ;
    int y2 = object.y;
    int w1 = this->animator.current().width();
    int w2 = object.animator.current().width();
    int h1 = this->animator.current().height();
    int h2 = object.animator.current().height();


    // recouvrement axe horizontal
    bool hoverlap = (x1<x2+w2) && (x2<x1+w1);

    // recouvrement axe vertical
    bool voverlap = (y1<y2+h2) && (y2<y1+h1);

    // recouvrement final
    bool overlap = hoverlap && voverlap;

    return overlap;
}

bool ZObject::pixelCollide(ZObject object)
{
//    QPixmap image = this->anim->current();
//    QImage imagePix = image.mask().toImage();


//    bool exit = false;
//    for (int xx = 0; xx < imagePix.height(); ++xx)
//    {
//        for (int yy = 0; yy < imagePix.width(); ++yy)
//        {
//            if (!qRed(imagePix.pixel(xx,yy))) // 255 = no image, 0 = image
//            {
//                exit = true;
//            }
//        }
//        if(exit)
//        {
//            break;
//        }
//    }


    return true;
}

int ZObject::getX()
{
    return x;
}

int ZObject::getY()
{
    return y;
}
