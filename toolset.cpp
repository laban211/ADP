#include "toolset.h"

void *Toolset::changeToolset(const ActiveToolset &activeToolset)
{
    if(activeToolset == moveMode){
             this->_activeToolset = activeToolset;
        qDebug() << _activeToolset;

         }

    else if(activeToolset == resizeMode){
             this->_activeToolset = activeToolset;
        qDebug() << _activeToolset;

         }

    else if(activeToolset == colorFillMode){
             this->_activeToolset = activeToolset;
        qDebug() << _activeToolset;
        qDebug() << isColorFill();
         }

    else if(activeToolset == pipettMode){
             this->_activeToolset = activeToolset;
        qDebug() << _activeToolset;

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
bool Toolset::isColorFill()
{
    return (this->_activeToolset == colorFillMode);
}

bool Toolset::isPipett()
{
    return (this->_activeToolset == pipettMode);
}


Toolset::~Toolset()
{
    delete this;
}
