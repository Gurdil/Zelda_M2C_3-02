#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QBitmap>
#include <QColor>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QElapsedTimer>

#include "zscene.h"
#include "zview.h"
#include "zinit.h"
#include "zanimator.h"
#include "ZKeyRecorder.h"
#include "zobject.h"
#include "zmap.h"

class ZControler : public QObject
{
        Q_OBJECT
    public:
        static ZControler* getInstance();
        ZKeyRecorder getKeyRecorder();

	signals:

	public slots:
		void updateCaption();

    protected:
        ZKeyRecorder keyRecorder;
        Zview *view;
		ZScene *scene;
		Zanimator *a;
		int var;
        bool hop;
        ZObject *avatar;
        ZObject *vilain;
        static ZControler* m_instance;
        ZMap *map;
		QElapsedTimer timerChrono;
		QTimer *timer;


        explicit ZControler(QObject *parent = 0);

};

#endif // CONTROLER_H
