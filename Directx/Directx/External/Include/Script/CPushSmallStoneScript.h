#pragma once
#include <Engine\CScript.h>

// obj name : 미는 돌 (작은 돌)
// desc : 플레이어가 밀 수 있음

class CPushSmallStoneScript :
    public CScript
{
private:
    Ptr<CTexture>       m_pSmallStoneTex;
    bool                m_bIsPushed;

public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CPushSmallStoneScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CPushSmallStoneScript();
    ~CPushSmallStoneScript();
};

