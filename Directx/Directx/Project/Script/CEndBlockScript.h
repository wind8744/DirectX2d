#pragma once
#include <Engine\CScript.h>

// obj name : 마무리 돌
// desc : 끝에 깨는 돌

class CPlayerScript;

class CEndBlockScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneTex;       //tex
    Ptr<CMaterial>          m_pMtrl;           //material
    CScript*                m_pTarScript;
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
    CLONE(CEndBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CEndBlockScript();
    ~CEndBlockScript();
};
