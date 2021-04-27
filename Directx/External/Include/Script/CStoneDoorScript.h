#pragma once
#include <Engine\CScript.h>

class CStoneDoorScript :
    public CScript
{
private:
    CScript*        m_pTarScript; //юс╫ц



public:
    virtual void awake();
    virtual void update();

private:
    //void CreateMissile();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

public:
    CLONE(CStoneDoorScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CStoneDoorScript();
    ~CStoneDoorScript();
};

