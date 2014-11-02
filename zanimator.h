#ifndef ZANIMATOR_H
#define ZANIMATOR_H

#include <QString>
#include <QList>
#include <QPixmap>
#include "zinit.h"

class Zanimator
{
	public:
		Zanimator(QList<QString> addresses);
		Zanimator(QList<QPixmap> pictures);
		Zanimator(QPixmap picture);
		Zanimator(){}
		~Zanimator();
		QPixmap begin();
		QPixmap next();
        QPixmap current();
	private:
		int index;
		int vitesse;
		int time_lap;
		QList<QPixmap> pictures;
};

#endif // ZANIMATOR_H
