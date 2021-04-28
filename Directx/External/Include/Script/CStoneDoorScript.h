#pragma once
#include <Engine\CScript.h>


// obj name : 돌로된 문 (6.jpg)
// desc : 플레이어가 지나갈 수 없고 문이 열리면 지나갈 수 있다.

class CObjEventScript;

class CStoneDoorScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneDoorTex;        //tex
    Ptr<CMaterial>          m_pMtrl;                //material

    CScript*                m_pTarScript;           //임시
    CObjEventScript*        m_pEventScript;         //EventScript


public:
    virtual void awake();
    virtual void update();

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

