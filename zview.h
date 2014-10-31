#ifndef ZVIEW_H
#define ZVIEW_H

#include <QGraphicsView>
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>

#include "ZKeyRecorder.h"

class Zview : public QGraphicsView
{
public:
    Zview(ZKeyRecorder &keyRecorder);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    ZKeyRecorder &keyRecorder;

};

#endif // ZVIEW_H
