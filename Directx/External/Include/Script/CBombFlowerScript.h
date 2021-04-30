#pragma once
#include <Engine\CScript.h>

// obj name : �μ� �� �ִ� ��( ū�� )
// desc : �÷��̾ �� �� ����, ������ �� ����

class CPlayerScript;

class CBombFlowerScript :
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
    CLONE(CBombFlowerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombFlowerScript();
    ~CBombFlowerScript();
};
