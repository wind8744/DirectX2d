#pragma once
#include <Engine\CScript.h>

// obj name : �̴� �� (���� ��)
// desc : �÷��̾ �� �� ����
class CPlayerScript;
class CPushSmallStoneScript :
    public CScript
{
private:
    CGameObject* m_Child;
    bool                    m_bIsPushed;
    DIR                     m_pushdir;
    bool m_stop;
    bool m_bAni;

    CDIR                m_eColliderDir;


public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:

    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
public:
    CLONE(CPushSmallStoneScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CPushSmallStoneScript();
    ~CPushSmallStoneScript();
};