#pragma once
#include <Engine\CScript.h>

class CRedButtonScript :
    public CScript
{
private:
    Ptr<CTexture>       m_pRedButTex;
    bool                m_bIsPushed;


    //int                 m_iData;
    //float               m_fData;
    //Vec2                m_v2Data;
    //Vec4                m_v4Data;


public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CRedButtonScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CRedButtonScript();
    ~CRedButtonScript();
};

