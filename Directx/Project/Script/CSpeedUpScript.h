#pragma once
#include <Engine\CScript.h>

// obj name : 스피드 업 발판
// desc : 플레이어가 밟으면 빨라짐

class CPlayerScript;

class CSpeedUpScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pRedButTex;           //버튼 tex
    Ptr<CMaterial>          m_pMtrl;                //material
    CPlayerScript*          m_pPlayerScript;        //플레이어 참조
    DIR                     m_eSpeedDir;            //발판 방향

    bool                    m_bIsPushed;            //눌렸는가?
    float                   m_fAtime;               //스피드 유지되는 시간

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

