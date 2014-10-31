#include "zview.h"

Zview::Zview(ZKeyRecorder &keyRecorder) : keyRecorder(keyRecorder)
{
    this->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    this->setDragMode(QGraphicsView::NoDrag);
    this->setTransformationAnchor(QGraphicsView::NoAnchor);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->setFixedSize(QApplication::desktop()->width(), QApplication::desktop()->height());
    this->showFullScreen();

}


void Zview::keyPressEvent(QKeyEvent *event)
{
    keyRecorder.setKey(event->key());
}

void Zview::keyReleaseEvent(QKeyEvent *event)
{
    keyRecorder.unsetKey(event->key());
}
