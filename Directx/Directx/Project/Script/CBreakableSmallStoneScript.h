#pragma once
#include <Engine\CScript.h>

// obj name : �μ� �� �ִ� ��( ������ )
// desc : �÷��̾ �� �� ����, ������ �� ����

class CPlayerScript;

class CBreakableSmallStoneScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneTex;       //tex
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
    CLONE(CBreakableSmallStoneScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBreakableSmallStoneScript();
    ~CBreakableSmallStoneScript();
};
