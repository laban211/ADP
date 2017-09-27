#include "toolset.h"

void *Toolset::changeToolset(const ActiveToolset &activeToolset)
{
    if(activeToolset == moveMode){
             this->_activeToolset = activeToolset;
         }

    else if(activeToolset == resizeMode){
             this->_activeToolset = activeToolset;
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
