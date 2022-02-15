#pragma once
#include <Engine\CScript.h>

// obj name : �μ� �� �ִ� ��( ū�� )
// desc : �÷��̾ �� �� ����, ������ �� ����

class CPlayerScript;
class CGameObject;
class CBreakableStoneScript :
    public CScript
{
private:
    bool                    m_bIsCol;          //�浹��?
    bool                    m_bIsBreak;        //�� �μ̴°�?
    bool m_delete; //����
    bool m_end;
    bool m_ani;

    float                   m_fAtime;
    Ptr<CPrefab>             m_effect;
    //CGameObject* m_pObject;

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