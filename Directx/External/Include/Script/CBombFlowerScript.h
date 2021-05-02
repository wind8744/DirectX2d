#pragma once
#include <Engine\CScript.h>

// obj name : ��ź ��
// desc : ��ź ����

enum class FLOWER_STATE
{
    IDLE,
    COL,
    MAKEBOMB,
    HEAD,
    NONE
};

class CPlayerScript;
class CScene;

class CBombFlowerScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex1;             //tex ( ��ź + �� )
    Ptr<CTexture>           m_pTex2;             //tex ( �� )
    Ptr<CMaterial>          m_pMtrl;           //material
    CPlayerScript*          m_pPlayerScript;
    CScript*                m_pScript;
    CScene*                 m_pCurScene;

    FLOWER_STATE            m_eState;           //��ź�� ����
    bool                    m_IsOnCol;          //�浹��?


private:
    void CheckState();
    void Excute();
    //bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBombFlowerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombFlowerScript();
    ~CBombFlowerScript();
};
