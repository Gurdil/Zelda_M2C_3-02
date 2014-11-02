#ifndef ZMAP_H
#define ZMAP_H

#include "zobject.h"
#include "zscene.h"
#include "zview.h"

#include <QList>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QString>

#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QList>
#include <QPixmap>
#include <QRect>
#include <QDomNodeList>
#include <QtMath>
#include <QElapsedTimer>
#include <QImage>
#include <QRectF>
#include <QPainter>

class ZMap
{
public:
	ZMap(Zview *view, ZScene *scene, ZObject *avatar, QString *file = NULL);
    void paint();
    bool collid(ZObject &object);

private:
    QList<ZObject> decors;
	QList<QGraphicsItem *> decorsGraphic;
	QPixmap map;
    QList<ZObject> obstacles;
	QList<QGraphicsItem *> obstaclesGraphic;
	QList<ZObject> livings;
    ZScene *scene;
    ZObject *avatar;
    Zview *view;
    int centerX;
    int centerY;
	QList<QPixmap> listImage;
	int sizeX;
	int sizeY;
	QElapsedTimer myTimer;

    enum point{
        x,
        y
    };

    int transform(int a, point p);
	void paintList(const QList<ZObject> &list);
    bool collidList(ZObject &object, QList<ZObject> &list);
	void loadXML(QString &file);
	void load(QDomNodeList &nodes, QList<ZObject> &objects, int tilewidth, int tileheight, int width, int height);
	QPixmap loadPixmap(QDomNodeList &nodes, int tilewidth, int tileheight, int width, int height);
	void paintListBoosted(const QList<ZObject> &list, const QList<QGraphicsItem *> &listGraphic);
};

#endif // ZMAP_H
