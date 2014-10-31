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


    QString passMap = QApplication::applicationDirPath() + QString("/map.png");
    map = QPixmap(passMap);


//    avatar = new ZObject(Zanimator(addresses), map.width()/2,map.height()/2);
//    vilain = new ZObject(Zanimator(addresses), avatar->getX()+300, avatar->getY()+300);

    avatar = new ZObject(Zanimator(addresses), map.width()/2,map.height()/2);
    addresses.clear();
    addresses.append(":/three/arbre.png");
    vilain = new ZObject(Zanimator(addresses), avatar->getX()+300, avatar->getY()+300);


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

    static int centerX = this->map.width()/2;
    static int centerY = this->map.height()/2;

    if (keyRecorder.readkey() & ZInit::up)
    {
        this->avatar->setPos(x, y-1);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
    }
    else if (keyRecorder.readkey() & ZInit::down)
    {
        this->avatar->setPos(x,y+1);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
    }
    else if (keyRecorder.readkey() & ZInit::right)
    {
        this->avatar->setPos(x+1,y);
        centerX++;
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
    }
    else if (keyRecorder.readkey() & ZInit::left)
    {
        this->avatar->setPos(x-1,y);
        if (this->avatar->collide(*(this->vilain), ZObject::rectangle))
        {
            this->avatar->setPos(x, y);
        }
    }


    QGraphicsPixmapItem *map = this->scene->addPixmap(this->map);

    QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
    QGraphicsPixmapItem *b = this->scene->addPixmap(this->vilain->getImage());




    map->setPos(-centerX + view->viewport()->width()/2, -centerY + view->viewport()->height()/2);
    a->setPos(view->viewport()->width()/2 + (avatar->getX() - centerX)
              ,view->viewport()->height()/2+ (avatar->getY() - centerY));
    b->setPos(view->viewport()->width()/2 + (vilain->getX() - centerX)
              ,view->viewport()->height()/2+ (vilain->getY() - centerY));

    this->view->viewport()->update();
}
