#pragma once
#include <Engine\CScript.h>

// obj name : ÆøÅº
// desc : Àå¾Ö¹° ÆøÆÄ

class CPlayerScript;

class CBombScript :
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
    CLONE(CBombScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombScript();
    ~CBombScript();
};
