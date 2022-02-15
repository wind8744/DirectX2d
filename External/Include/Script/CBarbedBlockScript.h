#pragma once
#include <Engine\CScript.h>

// obj name : ���õ�ģ ��ֹ�
// desc : �÷��̾��� ü���� ����

class CPlayerScript;

class CBarbedBlockScript :
    public CScript
{
private:
    float                   m_fDir;                   //dir
    float                   m_fSpeed;
    float                   m_fRange;
    Vec2                    m_vStartPos;

    bool                    m_bCol;            //���ȴ°�?


public:
    // bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBarbedBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CBarbedBlockScript();
    ~CBarbedBlockScript();
};