#ifndef ZAVATAR_H
#define ZAVATAR_H

#include <QList>
#include <QString>

#include "zanimator.h"
#include "zobject.h"
#include "ZKeyRecorder.h"
#include "zmap.h"

class ZAvatar : public ZObject
{
public:
	ZAvatar(int x, int y, ZKeyRecorder *keyRecorder, ZMap *map);

	enum Action{
        STAND,
        WALK,
        ATTACK,
        HURT,
        DEAD
    };

	enum Position{
        DOWN,
        LEFT,
        UP,
        RIGHT
    };

	void update();
	QPixmap getImage();



private:

	Action actionCurrent;
	Position positionCurrent;
    Zanimator moveDown;
    Zanimator moveLeft;
    Zanimator moveUp;
    Zanimator moveRight;
	Zanimator attackDown;
	Zanimator attackLeft;
	Zanimator attackUp;
	Zanimator attackRight;

    int speed;

	ZKeyRecorder *keyRecorder;
	ZMap *map;



};

#endif // ZAVATAR_H
