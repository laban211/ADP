#ifndef TOOLSET_H
#define TOOLSET_H

class Toolset
{
public:
    enum ActiveToolset{
    moveMode, deleteMode, resizeMode, colorFillMode, pipettMode
    };

    Toolset(ActiveToolset activeToolset = moveMode) : _activeToolset(activeToolset){}

    void *changeToolset(const ActiveToolset &activeToolset);

    bool isMove();
    bool isResize();
    bool isColorFill();
    bool isPipett();

    ActiveToolset _activeToolset;

};

#endif // TOOLSET_H
