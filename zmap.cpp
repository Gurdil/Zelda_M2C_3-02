#include "zmap.h"

ZMap::ZMap(Zview *view, ZScene *scene, QString *adress) : view(view), scene(scene)
{
	centerX = this->map.width()/2;
	centerY = this->map.height()/2;

	if (adress != NULL)
	{
		loadXML(*adress);
	}
	centerX = this->map.width()/2;
	centerY = this->map.height()/2;
}

int ZMap::getWith()
{
	return this->map.width();
}

int ZMap::getHeight()
{
	return this->map.height();
}

void ZMap::addLiving(ZObject *obj)
{
	livings.append(obj);
}

void ZMap::loadXML(QString &adress)
{
	QDomDocument doc("mydocument");
	QFile file(adress);
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "File" << ":/maptry/maptry.tmx" << "not find";
		return ;
	}
	if (!doc.setContent(&file))
	{
		qDebug() << "File" << ":/maptry/maptry.tmx" << "parsing error";
		file.close();
		return ;
	}
	file.close();

	QDomElement docElem = doc.documentElement();

	qDebug() << docElem.attribute("tilewidth");

	QDomNodeList list = docElem.elementsByTagName("tileset");

	int tilewidth, tileheight;
	int width, height;

	tilewidth = docElem.attribute("tilewidth").toInt();
	tileheight = docElem.attribute("tileheight").toInt();
	width = docElem.attribute("width").toInt();
	height = docElem.attribute("height").toInt();

	sizeX = width*tilewidth;
	sizeY = height*tileheight;

	for (int i = 0; i < list.length(); ++i)
	{
		int tilewidth, tileheight;
		int width, height;
		int line = 1, column = 1;
		int id;


		QDomElement e = list.at(i).toElement();

		id = e.attribute("firstgid").toInt();
		tilewidth = e.attribute("tilewidth").toInt();
		tileheight = e.attribute("tileheight").toInt();

		e = e.firstChild().toElement();
		QPixmap pix = QPixmap( QFileInfo(adress).absolutePath() + "/" + e.attribute("source"));
		width = e.attribute("width").toInt();
		height = e.attribute("height").toInt();

		if (width > tilewidth)
		{
			column = width/tilewidth;
		}
		if ( height > tileheight)
		{
			line = height/tileheight;
		}

		for (int j = 0; j < line; ++j)
		{
			for (int i = 0; i < column; ++i)
			{
				listImage.append(pix.copy(QRect(i * tilewidth, j * tileheight, tilewidth, tileheight)));
				id++;
			}
		}
	}

	list = docElem.elementsByTagName("layer");
	for (int i = 0; i < list.length(); ++i)
	{
		QDomElement e = list.at(i).toElement();
		if(e.attribute("name") == "Decors")
		{
            map = this->loadPixmap(e.firstChild().childNodes(), tilewidth, tileheight, width, height);
		}
		if(e.attribute("name") == "Obstacle")
		{
			QDomNodeList nodeList = e.firstChild().childNodes();
			obstacle = loadPixmap(nodeList, tilewidth, tileheight, width, height);
			load(nodeList, this->obstacles, tilewidth, tileheight, width, height);
		}
	}

	for (int i = 0; i < decors.length(); ++i)
	{
		ZObject obj = decors.at(i);
		QPixmap pix = obj.getImage();
		QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(pix);
		decorsGraphic.append(pixItem);
		this->scene->addItem(pixItem);
	}

	for (int i = 0; i < obstacles.length(); ++i)
	{
		ZObject obj = obstacles.at(i);
		QPixmap pix = obj.getImage();
		QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(pix);
		obstaclesGraphic.append(pixItem);
		this->scene->addItem(pixItem);
	}
}

void ZMap::load(QDomNodeList &nodes, QList<ZObject> &objects, int tilewidth, int tileheight, int width, int height)
{

	for (int i = 0; i < nodes.length(); ++i)
	{
		int x = i % width;
		int y = qFloor(i/height);

		QDomElement e = nodes.at(i).toElement();
		int id = e.attribute("gid").toInt();
		if(id == 0)
		{
			continue;
		}
		objects.append(ZObject(Zanimator(listImage.at(id-1)), x*tilewidth,y*tileheight));
	}
}

QPixmap ZMap::loadPixmap(QDomNodeList nodes, int tilewidth, int tileheight, int width, int height)
{

	QImage img( width*tilewidth, height*tileheight , QImage::Format_ARGB32);
	img.fill(Qt::transparent);
	QPainter p(&img);

	for (int i = 0; i < nodes.length(); ++i)
	{
		int x = i % width;
		int y = qFloor(i/height);

		QDomElement e = nodes.at(i).toElement();
		int id = e.attribute("gid").toInt();
		if(id == 0)
		{
			continue;
		}

		QRectF target(x*tilewidth,y*tileheight, tilewidth, tileheight);
		QRectF source(0.0, 0.0, tilewidth, tileheight);

		p.drawImage(target, listImage.at(id-1).toImage(), source);
	}

	return QPixmap::fromImage(img);
}

void ZMap::setAvatar(ZObject *obj)
{
     avatar = obj;
}

void ZMap::paint()
{
	this->scene->clear();

    int avatarX = transform(avatar->getX(), ZMap::x);
    int avatarY =transform(avatar->getY(), ZMap::y);

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
        centerY = avatar->getY() + view->viewport()->height()/4;
    }





	QGraphicsPixmapItem *a = this->scene->addPixmap(map);
	a->setPos(view->viewport()->width()/2  - centerX
			  ,view->viewport()->height()/2 - centerY);


	a = this->scene->addPixmap(obstacle);
	a->setPos(view->viewport()->width()/2  - centerX
				,view->viewport()->height()/2 - centerY);


	paintList(livings);



}

bool ZMap::collid(ZObject &object)
{
	return (collidList(object, obstacles));
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

int ZMap::transform(int a, ZMap::point p)
{
	switch (p)
	{
        case ZMap::x:
			return view->viewport()->width()/2 + (a - centerX);
			break;
        case ZMap::y:
			return view->viewport()->height()/2+ (a - centerY);
			break;
	}
}

void ZMap::paintList(const QList<ZObject> &list)
{

	foreach (ZObject object, list)
	{
		QGraphicsPixmapItem *a = this->scene->addPixmap(object.getImage());
        a->setPos(transform(object.getX(), ZMap::x)
                  ,transform(object.getY(), ZMap::y));
	}

}

void ZMap::paintList(QList<ZObject*> list)
{

	foreach (ZObject *object, list)
	{
		QGraphicsPixmapItem *a = this->scene->addPixmap(object->getImage());
        a->setPos(transform(object->getX(), ZMap::x)
                  ,transform(object->getY(), ZMap::y));
	}

}

void ZMap::paintListBoosted(const QList<ZObject> &list, const QList<QGraphicsItem *> &listGraphic)
{
	for (int i = 0; i < list.length(); ++i)
	{
		QGraphicsItem *a = listGraphic.at(i);
		ZObject b = list.at(i);
        a->setPos(transform(b.getX(), ZMap ::x)
                  ,transform(b.getY(), ZMap::y));
	}
}


void ZMap::update()
{
	foreach (ZObject *object, livings)
	{
		object->update();
	}
}
