#ifndef TOOLSET_H
#define TOOLSET_H

#include <QDebug>

class Toolset
{
public:
    enum ActiveToolset{
    moveMode, deleteMode, resizeMode
    };

    Toolset(ActiveToolset activeToolset = moveMode) : _activeToolset(activeToolset){}

//    Toolset();

    void changeToolset(ActiveToolset activeToolset);

//protected:

    ActiveToolset _activeToolset;

};

#endif // TOOLSET_H
