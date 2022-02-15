#pragma once
#include <Engine\CScript.h>

// obj name : ��ź ��
// desc : ��ź ����

enum class FLOWER_STATE
{
    IDLE,
    COL,
    BOMB,
    HEAD,
    NONE,
    MAKEBOMB,
    EXP, //����
};

class CPlayerScript;
class CScene;

class CBombFlowerScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex1;             //tex ( ��ź + �� )
    Ptr<CTexture>           m_pTex2;             //tex ( �� )
    Ptr<CMaterial>          m_pMtrl;
    Ptr<CPrefab> m_bomb;
    Ptr<CPrefab> m_effect;

    CScene* m_pCurScene;

    FLOWER_STATE            m_eState;           //��ź�� ����
    bool                    m_IsOnCol;          //�浹��?
    float                   m_fAtime;           //��ź ����� �ð�
    bool m_bExp; //���� ������ �ٷ� ����

private:
    void CheckState();
    void Excute();

public:
    //void SetMakeBombState() { m_eState = FLOWER_STATE::MAKEBOMB; }
    FLOWER_STATE GetState() { return m_eState; }
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