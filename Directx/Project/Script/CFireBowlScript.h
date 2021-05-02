#pragma once
#include <Engine\CScript.h>

// obj name : 화로
// desc : 장작에 불을 붙임

class CPlayerScript;

enum class FIRE_STATE
{
    COL,
    HEAD,
    SLIDE,
    END,
    NONE
};

class CFireBowlScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex;               //tex
    Ptr<CMaterial>          m_pMtrl;              //material
    CPlayerScript*          m_pPlayerScript;
    CScript*                m_pScript;

    FIRE_STATE              m_eState;
    Vec3                    m_vPos;
    DIR                     m_eDir;

    float                   m_fAtime;
    Vec2                    m_vSpeed;
    float                   m_fAngle;
    float                   m_fPower;
    //float                   m_fSpeed;

public:
    virtual void awake();
    virtual void update();

private:
    void CheckState();
    void Move();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CFireBowlScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CFireBowlScript();
    ~CFireBowlScript();
};
