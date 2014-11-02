#include "controler.h"

ZControler* ZControler::m_instance=0;

ZControler* ZControler::getInstance()
{
    if(m_instance == 0)
    {
        return new ZControler();
    }
    return m_instance;
}


ZControler::ZControler(QObject *parent) :
    QObject(parent)
{
    keyRecorder = ZKeyRecorder();
    this->view = new Zview(keyRecorder);
	this->var = 0;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
    timer->start(ZInit::frameRate);
	hop = true;
	scene = new ZScene();
	this->view->setScene(scene);


    QList<QString> addresses = QList<QString>();
    addresses.append(":/BadGuy/cyclope1.png");
    addresses.append(":/BadGuy/cyclope2.png");
    addresses.append(":/BadGuy/cyclope3.png");
    addresses.append(":/BadGuy/cyclope4.png");
    //Zanimator anim = Zanimator(addresses);

    avatar = new ZObject(Zanimator(addresses), 0, 0);
    vilain = new ZObject(Zanimator(addresses), avatar->getX()+300, avatar->getY()+300);

	QString adress = QString(":/maptry/maptry.tmx");
	map = new ZMap(view,scene,avatar, &adress);
}

ZKeyRecorder ZControler::getKeyRecorder()
{
    return keyRecorder;
}

void ZControler::updateCaption()
{
    this->scene->clear();

    int x = this->avatar->getX();
    int y = this->avatar->getY();

    if (keyRecorder.readkey() & ZInit::up)
    {
        this->avatar->setPos(x, y-1);
        if (map->collid(*avatar))
        {
            this->avatar->setPos(x, y);
        }
        else
        {
            y--;
        }

    }
    if (keyRecorder.readkey() & ZInit::down)
    {
        this->avatar->setPos(x,y+1);
        if (map->collid(*avatar))
        {
            this->avatar->setPos(x, y);
        }
        else
        {
            y++;
        }
    }
    if (keyRecorder.readkey() & ZInit::right)
    {
        this->avatar->setPos(x+1,y);
        if (map->collid(*avatar))
        {
            this->avatar->setPos(x, y);
        }
        else
        {
            x++;
        }
    }
    if (keyRecorder.readkey() & ZInit::left)
    {
        this->avatar->setPos(x-1,y);
        if (map->collid(*avatar))
        {
            this->avatar->setPos(x, y);
        }
        else
        {
            x--;
        }
    }


    map->paint();

    this->view->viewport()->update();
}
