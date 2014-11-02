#include "zmap.h"

ZMap::ZMap(Zview *view, ZScene *scene, ZObject *avatar, QString *adress) : view(view), scene(scene), avatar(avatar)
{
	QString passMap = QApplication::applicationDirPath() + QString("/map.png");
	map = QPixmap(passMap);


	centerX = this->map.width()/2;
	centerY = this->map.height()/2;

	if (adress != NULL)
	{
		loadXML(*adress);
	}
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
			load(e.firstChild().childNodes(), this->decors, tilewidth, tileheight, width, height);
		}
		if(e.attribute("name") == "Obstacle")
		{
			load(e.firstChild().childNodes(), this->obstacles, tilewidth, tileheight, width, height);
		}
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


	paintList(decors);
	paintList(obstacles);

	QGraphicsPixmapItem *a = this->scene->addPixmap(this->avatar->getImage());
	a->setPos(view->viewport()->width()/2 + (avatar->getX() - centerX)
			  ,view->viewport()->height()/2+ (avatar->getY() - centerY));



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
