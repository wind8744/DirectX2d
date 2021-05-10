#pragma once
#include "CComponent.h"


class CLight2D :
    public CComponent
{
private:
    tLight2DInfo    m_info;

public:
    virtual void finalupdate();

public:
    const tLight2DInfo& GetInfo() { return m_info; }
    void SetLightType(LIGHT_TYPE _eType){m_info.eType = _eType;}
    void SetAmbient(Vec3 _vAmb) { m_info.color.vAmb = _vAmb; }
    void SetRange(float _fRange) { m_info.fRange = _fRange; }


public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
    CLONE(CLight2D);

public:
    CLight2D();
    ~CLight2D();
};

