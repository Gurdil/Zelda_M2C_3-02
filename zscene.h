#ifndef ZSCENE_H
#define ZSCENE_H

#include <QGraphicsScene>
#include <QRectF>
#include <QApplication>
#include <QDesktopWidget>

class ZScene : public QGraphicsScene
{
		Q_OBJECT
	public:
		explicit ZScene(QObject *parent = 0);

	signals:

	public slots:

};

#endif // ZSCENE_H
