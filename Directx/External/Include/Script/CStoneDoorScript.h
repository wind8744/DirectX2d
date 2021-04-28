#pragma once
#include <Engine\CScript.h>


// obj name : ���ε� �� (6.jpg)
// desc : �÷��̾ ������ �� ���� ���� ������ ������ �� �ִ�.

class CObjEventScript;

class CStoneDoorScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneDoorTex;        //tex
    Ptr<CMaterial>          m_pMtrl;                //material

    CScript*                m_pTarScript;           //�ӽ�
    CObjEventScript*        m_pEventScript;         //EventScript


public:
    virtual void awake();
    virtual void update();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

public:
    CLONE(CStoneDoorScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CStoneDoorScript();
    ~CStoneDoorScript();
};

