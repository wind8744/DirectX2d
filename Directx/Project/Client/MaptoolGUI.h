#pragma once
#include "GUI.h"
#include <Engine\CTexture.h>

class CMapScript;
class MaptoolGUI :
    public GUI
{
private:
    Ptr<CTexture> m_TileTex;
    CMapScript* m_Map;
    int         m_x;
    int        m_y;
    int        m_size;
    Vec2        m_SetIndex;
public:
    virtual void init();
    virtual void update();
    virtual void render();

public:
    MaptoolGUI();
    ~MaptoolGUI();

};

