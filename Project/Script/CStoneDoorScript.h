#pragma once
#include <Engine\CScript.h>


// obj name : ���ε� �� (6.jpg)
// desc : �÷��̾ ������ �� ���� ���� ������ ������ �� �ִ�.

class CObjEventScript;

class CStoneDoorScript :
    public CScript
{
private:



    CObjEventScript* m_pEventScript;         //EventScript



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