#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QDesktopWidget>
#include <QtGlobal>
#include <QBrush>
#include <QRectF>
#include "controler.h"
#include "zinit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setOverrideCursor( QCursor( Qt::BlankCursor ) );



	QGraphicsScene scene;
	QRectF rec = QRectF(0, 0, a.desktop()->width()-2, a.desktop()->height()-2);
	scene.setSceneRect(rec);
	scene.setBackgroundBrush(QBrush(Qt::gray, Qt::SolidPattern));
	QPixmap zeldaPic = QPixmap();

	qDebug("whith:  %f ", scene.width());
	qDebug("height:  %f ", scene.height());



	/**for (int var = 0; var < 500; var+=10)
	{
		scene.addLine(QLineF(0,0,100+var,100));
	}**/

	if(zeldaPic.load(":/zelda/Princesse_Zelda.png", "png"))
	{
		scene.addPixmap(zeldaPic);
	}
	else
	{
		QGraphicsTextItem *text = scene.addText("fail");
		text->setPos(0,0);
	}


	QGraphicsView view(&scene);
	//view.setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
	view.setFixedSize(a.desktop()->width(), a.desktop()->height());
	view.setDragMode(QGraphicsView::NoDrag);
	view.setTransformationAnchor(QGraphicsView::NoAnchor);
	view.setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	view.setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	view.showFullScreen();

	qDebug("whith: %d", view.width());
	qDebug("height: %d", view.height());

	controler *c = new controler(&view);

    return a.exec();
}
