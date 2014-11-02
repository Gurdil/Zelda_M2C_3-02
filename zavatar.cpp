#include "zavatar.h"


ZAvatar::ZAvatar(int x, int y, ZKeyRecorder *keyRecorder, ZMap *map)
{
	this->x = x;
	this->y = y;
	this->keyRecorder = keyRecorder;
	this->map = map;
	speed = 10;
	actionCurrent = Action::STAND;
	positionCurrent = Position::DOWN;

	QList<QString> list = QList<QString>();

	list.append(":/avatar/walkD1.png");
	list.append(":/avatar/walkD2.png");
	list.append(":/avatar/walkD3.png");
	list.append(":/avatar/walkD4.png");
	list.append(":/avatar/walkD5.png");
	list.append(":/avatar/walkD6.png");
	list.append(":/avatar/walkD7.png");
	list.append(":/avatar/walkD8.png");
	list.append(":/avatar/walkD9.png");
	list.append(":/avatar/walkD10.png");


	this->moveDown = Zanimator(list);


	list.clear();

	list.append(":/avatar/walkL1.png");
	list.append(":/avatar/walkL2.png");
	list.append(":/avatar/walkL3.png");
	list.append(":/avatar/walkL4.png");
	list.append(":/avatar/walkL5.png");
	list.append(":/avatar/walkL6.png");
	list.append(":/avatar/walkL7.png");
	list.append(":/avatar/walkL8.png");
	list.append(":/avatar/walkL9.png");
	list.append(":/avatar/walkL10.png");

	this->moveLeft = Zanimator(list);



	list.clear();

	list.append(":/avatar/walkR1.png");
	list.append(":/avatar/walkR2.png");
	list.append(":/avatar/walkR3.png");
	list.append(":/avatar/walkR4.png");
	list.append(":/avatar/walkR5.png");
	list.append(":/avatar/walkR6.png");
	list.append(":/avatar/walkR7.png");
	list.append(":/avatar/walkR8.png");
	list.append(":/avatar/walkR9.png");
	list.append(":/avatar/walkR10.png");

	this->moveRight = Zanimator(list);

	list.clear();

	list.append(":/avatar/walkU1.png");
	list.append(":/avatar/walkU2.png");
	list.append(":/avatar/walkU3.png");
	list.append(":/avatar/walkU4.png");
	list.append(":/avatar/walkU5.png");
	list.append(":/avatar/walkU6.png");
	list.append(":/avatar/walkU7.png");
	list.append(":/avatar/walkU8.png");
	list.append(":/avatar/walkU9.png");
	list.append(":/avatar/walkU10.png");

	this->moveUp = Zanimator(list);


	this->animator = moveDown;
}


void ZAvatar::update()
{
	int x = this->x;
	int y = this->y;


	if (keyRecorder->readkey() & ZInit::up)
	{
		this->setPos(x, y-1);
		if (map->collid(*this))
		{
			this->setPos(x, y);
		}
		else
		{
			if ((positionCurrent != Position::UP) )
			{
				positionCurrent = Position::UP;
				actionCurrent = Action::WALK;
				animator = moveUp;
			}
			y--;
		}

	}
	if (keyRecorder->readkey() & ZInit::down)
	{
		this->setPos(x,y+1);
		if (map->collid(*this))
		{
			this->setPos(x, y);
		}
		else
		{
			if ((positionCurrent != Position::DOWN))
			{
				positionCurrent = Position::DOWN;
				actionCurrent = Action::WALK;
				animator = moveDown;
			}
			y++;
		}
	}
	if (keyRecorder->readkey() & ZInit::right)
	{
		this->setPos(x+1,y);
		if (map->collid(*this))
		{
			this->setPos(x, y);
		}
		else
		{
			if ((positionCurrent != Position::RIGHT))
			{
				positionCurrent = Position::RIGHT;
				actionCurrent = Action::WALK;
				animator = moveRight;
			}
			x++;
		}
	}
	if (keyRecorder->readkey() & ZInit::left)
	{
		this->setPos(x-1,y);
		if (map->collid(*this))
		{
			this->setPos(x, y);
		}
		else
		{
			if ((positionCurrent != Position::LEFT))
			{
				positionCurrent = Position::LEFT;
				actionCurrent = Action::WALK;
				animator = moveLeft;
			}
			x--;
		}
	}
}

QPixmap ZAvatar::getImage()
{
	if(actionCurrent == Action::STAND)
	{
		return this->animator.begin();
	}
	else
	{
		return this->animator.next();
	}
}
