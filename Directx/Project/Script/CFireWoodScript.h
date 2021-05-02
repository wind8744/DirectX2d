#pragma once
#include <Engine\CScript.h>

// obj name : ����
// desc : ���� ���� �� ����, ���� ������ �̺�Ʈ �߻�
class CObjEventScript;
class CPlayerScript;
class CFireWoodScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex;               //tex
    Ptr<CMaterial>          m_pMtrl;             //material

    CPlayerScript* m_pPlayerScript;

    CObjEventScript* m_pEventScript;
    CGameObject* m_Child;

    bool                    m_bPlayAni;

    float                   m_OnTime;
    float                   m_Time;

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CFireWoodScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CFireWoodScript();
    ~CFireWoodScript();
};
