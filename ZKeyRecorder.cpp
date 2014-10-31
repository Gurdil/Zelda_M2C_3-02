#include "ZKeyRecorder.h"

ZKeyRecorder::ZKeyRecorder()
{
    key =0;
}

void ZKeyRecorder::setKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        this->key |= ZInit::up;
        break;
    case Qt::Key_Down:
        this->key |= ZInit::down;
        break;
    case Qt::Key_Right:
        this->key |= ZInit::right;
        break;
    case Qt::Key_Left:
        this->key |= ZInit::left;
        break;
    }
}

void ZKeyRecorder::unsetKey(int key)
{
    switch (key)
    {
    case Qt::Key_Up:
        this->key &= ~ZInit::up;
        break;
    case Qt::Key_Down:
        this->key &= ~ZInit::down;
        break;
    case Qt::Key_Right:
        this->key &= ~ZInit::right;
        break;
    case Qt::Key_Left:
        this->key &= ~ZInit::left;
        break;
    }
}

int ZKeyRecorder::readkey()
{
    return key;
}
