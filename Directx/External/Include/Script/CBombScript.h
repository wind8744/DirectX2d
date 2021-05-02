#pragma once
#include <Engine\CScript.h>

// obj name : ��ź
// desc : ��ֹ� ����

enum class BOMB_STATE
{
    ONHEAD,     //�Ӹ���
    //THROW,      //����
    SLIDE,      //�̲�����
    EXPLODE,    //����
    NONE        
};


class CPlayerScript;

class CBombScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex;             //tex
    Ptr<CMaterial>          m_pMtrl;           //material
    CScript*                m_pScript;
    CPlayerScript*          m_pPlayerScript;
    BOMB_STATE              m_eState;

    float                   m_fAtime;
    float                   m_fSpeed;       //�ӵ�
    DIR                     m_eDir;         //�÷��̾� ���� ����
    Vec3                    m_vPos;         //ó�� ��ġ ����

private:
    void CheckState();
    void Move();

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBombScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombScript();
    ~CBombScript();
};
