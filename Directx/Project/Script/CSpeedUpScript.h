#pragma once
#include <Engine\CScript.h>

// obj name : ���ǵ� �� ����
// desc : �÷��̾ ������ ������

class CPlayerScript;

class CSpeedUpScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pRedButTex;           //��ư tex
    Ptr<CMaterial>          m_pMtrl;                //material
    CPlayerScript*          m_pPlayerScript;        //�÷��̾� ����
    DIR                     m_eSpeedDir;            //���� ����

    bool                    m_bIsPushed;            //���ȴ°�?
    float                   m_fAtime;               //���ǵ� �����Ǵ� �ð�

public:
    bool GetIsPushed() { return m_bIsPushed; }
    void PushDir(DIR _dir) { m_eSpeedDir = _dir; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CSpeedUpScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CSpeedUpScript();
    ~CSpeedUpScript();
};

