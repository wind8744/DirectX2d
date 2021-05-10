#pragma once
#include <Engine\CScript.h>

// obj name : �μ� �� �ִ� ��( ū�� )
// desc : �÷��̾ �� �� ����, ������ �� ����

class CPlayerScript;

class CBreakableStoneScript :
    public CScript
{
private:
    
    CPlayerScript*          m_pPlayerScript;
    
    bool                    m_bIsCol;          //�浹��?
    bool                    m_bIsBreak;        //�� �μ̴°�?
    
    float                   m_fAtime;


public:
    bool GetIsBreak() { return m_bIsBreak; }
    void SetIsBreak(bool _break) { m_bIsBreak = _break; }

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
