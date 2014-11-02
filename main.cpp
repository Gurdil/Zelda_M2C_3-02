#include <QApplication>
#include <iostream>

#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QList>
#include <QPixmap>
#include <QRect>


#include "controler.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QString adress = ":/maptry/maptry.tmx";

	QDomDocument doc("mydocument");
	QFile file(adress);
	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "File" << ":/maptry/maptry.tmx" << "not find";
		return 1;
	}
	if (!doc.setContent(&file))
	{
		qDebug() << "File" << ":/maptry/maptry.tmx" << "parsing error";
		file.close();
		return 1;
	}
	file.close();

	QList<QPixmap *> listImage;

	QDomElement docElem = doc.documentElement();

	qDebug() << docElem.attribute("tilewidth");

	QDomNodeList list = docElem.elementsByTagName("tileset");



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
			line = width/tilewidth;
		}
		if ( height > tileheight)
		{
			column = height/tileheight;
		}

		for (int i = 0; i < column; ++i)
		{
			for (int j = 0; j < line; ++j)
			{
				listImage.insert(id, &pix.copy(QRect(i * tilewidth, j * tileheight, tilewidth, tileheight)));
				id++;
			}
		}
	}

	qDebug() << "";
	qDebug() << "";



	list = docElem.elementsByTagName("layer");
	for (int i = 0; i < list.length(); ++i)
	{
		QDomElement e = list.at(i).toElement();
		qDebug() << e.tagName() << e.attribute("name");
	}


	QDomElement e = list.at(0).toElement();
	e = e.firstChild().toElement();
	qDebug() << e.tagName();
	list = e.childNodes();

	for (int i = 0; i < list.length(); ++i)
	{
		QDomElement e = list.at(i).toElement();
		//qDebug() << e.tagName() << e.attribute("gid").toInt();
	}










	a.setOverrideCursor(QCursor(Qt::BlankCursor ));

	ZControler *c = ZControler::getInstance();

	return a.exec();

	std::cout << "Never view" << std::endl;
}
