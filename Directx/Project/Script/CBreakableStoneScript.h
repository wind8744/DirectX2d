#pragma once
#include <Engine\CScript.h>

// obj name : 부술 수 있는 돌( 큰돌 )
// desc : 플레이어가 깰 수 있음, 지나갈 수 없음

class CPlayerScript;

class CBreakableStoneScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneTex;       //tex
    Ptr<CMaterial>          m_pMtrl;           //material
    CPlayerScript*          m_pPlayerScript;
    bool                    m_bIsPushed;

    float                   m_fAtime;


public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBreakableStoneScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBreakableStoneScript();
    ~CBreakableStoneScript();
};
