#ifndef ZKEYLISTENER_H
#define ZKEYLISTENER_H

#include <Qt>
#include <iostream>

#include "zinit.h"

class ZKeyRecorder
{
public:
    ZKeyRecorder();
    void setKey(int key);
    void unsetKey(int key);
    int readkey();

private:
    unsigned int key;
};

#endif // ZKEYLISTENER_H
