#pragma once
#include <Engine\CScript.h>

// obj name : ��ź
// desc : ��ֹ� ����

enum class BOMB_STATE
{
    ONHEAD,     //�Ӹ���
    //THROW,      //����
    SLIDE,      //�̲�����
    EXPLODE_READY,
    EXPLODE,    //����
    NONE
};


class CPlayerScript;

class CBombScript :
    public CScript
{
private:

    //
    CScript* m_pTarScript;
    Ptr<CPrefab> m_effect;
    //CPlayerScript*          m_pPlayerScript;
    bool m_IsCol;
    BOMB_STATE              m_eState;
    DIR                     m_eDir;         //�÷��̾� ���� ����
    Vec3                    m_vPos;         //ó�� ��ġ ����
    Vec3                    m_vStartPos;
    Vec2                    m_vSpeed; //�� , �� speed
    float                   m_fSpeed; //��,  �� speed
    float                   m_fAtime;
    float                   m_fAngle;
    float                   m_fPower;
    float                   m_fAdjSpeed;

private:
    void CheckState();
    void Move();

public:
    virtual void awake();
    virtual void update();


public:

    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);


public:
    CLONE(CBombScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombScript();
    ~CBombScript();
};