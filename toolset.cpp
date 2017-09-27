#include "toolset.h"

void *Toolset::changeToolset(const ActiveToolset &activeToolset)
{
    if(activeToolset == moveMode){
        qDebug()<<"MoveMode active!";
        this->_activeToolset = activeToolset;
        qDebug()<<_activeToolset;
    }

    else if(activeToolset == resizeMode){
        qDebug()<<"ResizeMode active!";
        this->_activeToolset = activeToolset;
        qDebug()<<_activeToolset;
    }
}

bool Toolset::isMove()
{

    return (this->_activeToolset == moveMode);
}

bool Toolset::isResize()
{
    return (this->_activeToolset == resizeMode);
}

Toolset::~Toolset()
{
    delete this;
}
