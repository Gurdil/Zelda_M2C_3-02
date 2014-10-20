#include "zscene.h"

ZScene::ZScene(QObject *parent) :
	QGraphicsScene(parent)
{
	QRectF rec = QRectF(0, 0, QApplication::desktop()->width()-2,
						QApplication::desktop()->height()-2);
	this->setSceneRect(rec);
	this->setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
}
