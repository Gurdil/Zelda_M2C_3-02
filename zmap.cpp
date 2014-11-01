#include "zmap.h"

ZMap::ZMap(Zview *view, ZScene *scene, ZObject *avatar) : view(view), scene(scene), avatar(avatar)
{
    QString passMap = QApplication::applicationDirPath() + QString("/map.png");
    map = QPixmap(passMap);


    QList<QString> addresses = QList<QString>();
    addresses.append(":/three/arbre.png");
    obstacles.append(ZObject(Zanimator(addresses), 300,300));

    centerX = this->map.width()/2;
    centerY = this->map.height()/2;
}

void ZMap::paint()
{

    int avatarX = transform(avatar->getX(), point::x);
    int avatarY =transform(avatar->getY(), point::y);

    if (avatarX > (3*view->viewport()->width()/4))
    {
        centerX = avatar->getX() - view->viewport()->width()/4;
    }
    else if (avatarX < (view->viewport()->width()/4))
    {
        centerX = avatar->getX() + view->viewport()->width()/4;
    }

    if (avatarY > (3*view->viewport()->height()/4))
    {
        centerY = avatar->getY() - view->viewport()->height()/4;
    }
    else if (avatarY < (view->viewport()->height()/4))
    {
        centerY = avatar->getY() - view->viewport()->height()/4;
    }


    QGraphicsPixmapItem *map = this->scene->addPixmap(this->map);
    map->setPos(-centerX + view->viewport()->width()/2, -centerY + view->viewport()->height()/2);

    QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
    a->setPos(view->viewport()->width()/2 + (avatar->getX() - centerX)
              ,view->viewport()->height()/2+ (avatar->getY() - centerY));

    paintList(decors);
    paintList(obstacles);

}

bool ZMap::collid(ZObject &object)
{
    return (collidList(object, livings) | collidList(object, obstacles));
}

bool ZMap::collidList(ZObject &object, QList<ZObject> &list)
{
    foreach (ZObject objectList, list)
    {
        if (object.collide(objectList, ZObject::rectangle))
        {
            return true;
        }
    }
    return false;
}

int ZMap::transform(int a, point p)
{
    switch (p)
    {
    case point::x:
        return view->viewport()->width()/2 + (a - centerX);
        break;
    case point::y:
        return view->viewport()->height()/2+ (a - centerY);
        break;
    }
}

void ZMap::paintList(QList<ZObject> &list)
{

    foreach (ZObject object, list)
    {
        QGraphicsPixmapItem *a = this->scene->addPixmap(object.getImage());
        a->setPos(transform(object.getX(), point::x)
                  ,transform(object.getY(), point::y));
    }
}
