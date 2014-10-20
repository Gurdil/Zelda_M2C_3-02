#include "controler.h"

controler::controler(QGraphicsView *view, QObject *parent) :
	QObject(parent)
{
	this->view = view;
	this->var = 0;
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateCaption()));
	timer->start(ZInit::getFrameRate());
	hop = true;
	scene = new ZScene();
	this->view->setScene(scene);


}

void controler::updateCaption()
{

	QList<QString> addresses = QList<QString>();
	addresses.append(":/BadGuy/cyclope1.png");
	addresses.append(":/BadGuy/cyclope2.png");
	addresses.append(":/BadGuy/cyclope3.png");
	addresses.append(":/BadGuy/cyclope4.png");
	static Zanimator *anim = new Zanimator(addresses);

	ZScene *newScene = new ZScene();
	static int x = 1000;

	if (hop)
	{
		QGraphicsPixmapItem *a = newScene->addPixmap(anim->next());
		a->setPos(x,0);
		x--;
		//hop = !hop;
	}
	else
	{
		hop = !hop;
	}

	this->view->setScene(newScene);
	delete this->scene;
	this->scene = newScene;
}
