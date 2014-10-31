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

    vilain = new ZObject(Zanimator(addresses), 300,300);
    avatar = new ZObject(Zanimator(addresses), 0,0);

    map = QPixmap(":/map/map.jpg");
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
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
        QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
        a->setPos(this->avatar->getX(),this->avatar->getY());
    }
    else if (keyRecorder.readkey() & ZInit::down)
    {
        this->avatar->setPos(x,y+1);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
        QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
        a->setPos(this->avatar->getX(),this->avatar->getY());
    }
    else if (keyRecorder.readkey() & ZInit::right)
    {
        this->avatar->setPos(x+1,y);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
        QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
        a->setPos(this->avatar->getX(),this->avatar->getY());
    }
    else if (keyRecorder.readkey() & ZInit::left)
    {
        this->avatar->setPos(x-1,y);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
        QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
        a->setPos(this->avatar->getX(),this->avatar->getY());
    }
    else
    {
        QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
        a->setPos(this->avatar->getX(),this->avatar->getY());
    }

    QGraphicsPixmapItem *a = this->scene->addPixmap(this->vilain->getImage());
    a->setPos(this->vilain->getX(),this->vilain->getY());

    a = this->scene->addPixmap(this->map);
    a->setPos(0,0);

    this->view->viewport()->update();
}
