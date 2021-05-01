#pragma once
#include <Engine\CScript.h>

// obj name : 장작
// desc : 불을 붙일 수 있음, 불이 붙으면 이벤트 발생

class CPlayerScript;

class CFireWoodScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex;       //tex
    Ptr<CMaterial>          m_pMtrl;           //material
    CPlayerScript*          m_pPlayerScript;
    bool                    m_bIsPushed;


public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CFireWoodScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CFireWoodScript();
    ~CFireWoodScript();
};
