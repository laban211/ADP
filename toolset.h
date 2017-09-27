#ifndef TOOLSET_H
#define TOOLSET_H

#include <QDebug>

class Toolset
{
public:
    enum ActiveToolset{
    moveMode, deleteMode, resizeMode
    };

    Toolset(ActiveToolset activeToolset = resizeMode) : _activeToolset(activeToolset){}

    void *changeToolset(const ActiveToolset &activeToolset);

    bool isMove();

    bool isResize();

    ~Toolset();



//protected:

    ActiveToolset _activeToolset;

};

#endif // TOOLSET_H
