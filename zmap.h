#ifndef ZMAP_H
#define ZMAP_H

#include "zobject.h"
#include "zscene.h"
#include "zview.h"

#include <QList>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class ZMap
{
public:
    ZMap(Zview *view, ZScene *scene, ZObject *avatar);
    void paint();
    bool collid(ZObject &object);

private:
    QList<ZObject> decors;
    QList<ZObject> obstacles;
    QList<ZObject> livings;
    QPixmap map;
    ZScene *scene;
    ZObject *avatar;
    Zview *view;
    int centerX;
    int centerY;

    enum point{
        x,
        y
    };

    int transform(int a, point p);
    void paintList(QList<ZObject> &list);
    bool collidList(ZObject &object, QList<ZObject> &list);
};

#endif // ZMAP_H
