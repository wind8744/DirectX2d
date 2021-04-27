#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE       m_eProjType;    
    Vec2            m_vScale;   // 직교투영 범위 배율

    Matrix          m_matView;
    Matrix          m_matProj;

    float           m_fFOV;

    UINT            m_iLayerCheck;

    vector<CGameObject*>    m_vecForward;
    vector<CGameObject*>    m_vecParticle;
    vector<CGameObject*>    m_vecPostEffect;

public:
    virtual void update();
    virtual void finalupdate();

public:
    void SetProjType(PROJ_TYPE _eType) { m_eProjType = _eType; }
    void SetScale(Vec2 _vScale) {m_vScale = _vScale;}
    void SetLayerCheck(UINT _iLayerIdx, bool _bAdd);
    void SetLayerAllCheck() { m_iLayerCheck = 0xffffffff; }

public:
    void SortObject();
    void render_forward();
    void render_posteffect();

public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
    CLONE(CCamera);

public:
    CCamera();
    ~CCamera();
};

