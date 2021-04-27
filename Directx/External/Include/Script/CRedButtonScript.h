#pragma once
#include <Engine\CScript.h>

// obj name : ���� ��ư
// desc : �÷��̾ ������ Ư�� ���� (���� �����ٰų�) ����

class CObjEventScript;

class CRedButtonScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pRedButTex;           //��ư tex
    Ptr<CMaterial>          m_pMtrl;                //material

    CObjEventScript*        m_pEventScript;         //EventScript
    bool                    m_bIsPushed;            //���ȴ°�?


public:
    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CRedButtonScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CRedButtonScript();
    ~CRedButtonScript();
};

