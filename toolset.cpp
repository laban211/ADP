#include "toolset.h"

void Toolset::changeToolset(ActiveToolset activeToolset)
{
    //You can also use a switch-case here

    if(activeToolset == ActiveToolset::moveMode){
        qDebug()<<"MoveMode active!";
        this->_activeToolset = activeToolset;
    }

    else if(activeToolset == ActiveToolset::resizeMode){
        qDebug()<<"ResizeMode active!";
        this->_activeToolset = activeToolset;
    }

    else if(activeToolset == ActiveToolset::colorFill){
        qDebug()<<"ColorFill active!";
        this->_activeToolset = activeToolset;
    }

}
