#pragma once
#include <Engine\CScript.h>

// obj name : 폭탄
// desc : 장애물 폭파

enum class BOMB_STATE
{
    ONHEAD,     //머리위
    //THROW,      //던짐
    SLIDE,      //미끄러짐
    EXPLODE,    //터짐
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
    float                   m_fSpeed;       //속도
    DIR                     m_eDir;         //플레이어 방향 저장
    Vec3                    m_vPos;         //처음 위치 저장

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
