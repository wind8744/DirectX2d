
#pragma once
#include <Engine\CScript.h>

// obj name : 전기 타워 (자식)
// desc : 

class CPlayerScript;
class CElecBlockScript;

class CElecChildScript :
    public CScript
{
private:
    CScript*                m_pTarScript;
    CPlayerScript*          m_pPlayerScript;

    //vector<CElecBlockScript*> m_vecElec;        
    vector<CScript*>          m_vecScript;

    float                   m_fMinDir;
    bool                    m_bIsCol;

public:


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CElecChildScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecChildScript();
    ~CElecChildScript();
};
