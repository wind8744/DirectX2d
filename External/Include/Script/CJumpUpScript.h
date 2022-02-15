#pragma once
#include <Engine\CScript.h>

// obj name : ���� ��ư
// desc : �÷��̾ ������ Ư�� ���� (���� �����ٰų�) ����

class CPlayerScript;

class CJumpUpScript :
    public CScript
{
private:
    int                     m_Dir;
    int                     m_PreDir;
    bool                    m_bIsPushed;            //���ȴ°�?
    float                   m_fAtime;               //���ǵ� �����Ǵ� �ð�
    float                   m_fRotValue;            //90��
    bool                    m_bFlag; //test

public:
    bool GetIsPushed() { return m_bIsPushed; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CJumpUpScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CJumpUpScript();
    ~CJumpUpScript();
};
