#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>
#include "zscene.h"
#include "zinit.h"
#include "zanimator.h"

class controler : public QObject
{
		Q_OBJECT
	public:
		explicit controler(QGraphicsView *view, QObject *parent = 0);

	signals:

	public slots:
		void updateCaption();

	private:
		QGraphicsView *view;
		ZScene *scene;
		Zanimator *a;
		int var;
		bool hop;

};

#endif // CONTROLER_H
