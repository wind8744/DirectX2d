#pragma once
#include <Engine\CScript.h>

class CPlayerScript :
    public CScript
{
private:
    Ptr<CPrefab>        m_pMissilePrefab;
    int                 m_iData;
    int                 m_fData;
    Vec2                m_v2Data;
    Vec4                m_v4Data;



public:
    virtual void awake();
    virtual void update();

private:
    void CreateMissile();    

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

public:
    CLONE(CPlayerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CPlayerScript();
    ~CPlayerScript();
};

