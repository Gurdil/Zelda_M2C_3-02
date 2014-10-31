#include "zanimator.h"

Zanimator::Zanimator(QList<QString> addresses)
{
	index = 0;
	time_lap = 0;
    vitesse = 100;
    pictures = QList<QPixmap>();
	QString address;

	foreach (address, addresses)
	{
        pictures.append(QPixmap(address));
	}
}

Zanimator::~Zanimator()
{

}

QPixmap Zanimator::begin()
{
	index = 0;
    return pictures.at(index);
}

QPixmap Zanimator::next()
{
    time_lap += ZInit::frameRate;
	if(time_lap> vitesse)
	{
		time_lap = 0;
		index++;
        if (index>=pictures.length())
		{
			index = 0;
		}
	}

    return pictures.at(index);
}

QPixmap Zanimator::current()
{
    return pictures.at(index);
}
