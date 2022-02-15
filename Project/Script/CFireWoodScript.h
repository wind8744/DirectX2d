#pragma once
#include <Engine\CScript.h>

// obj name : ����
// desc : ���� ���� �� ����, ���� ������ �̺�Ʈ �߻�
class CObjEventScript;
class CPlayerScript;

class CFireWoodScript :
    public CScript
{
private:
    CObjEventScript* m_pEventScript;
    CGameObject* m_Child;

    bool                    m_bIsOnFire;
    bool                    m_bPlayAni;

    float                   m_test;

    float                   m_fOnTime;
    float                   m_fSetTime;  //������ �ð�

public:
    void SetFireTime(float _time) { m_fSetTime = _time; }

public:
    virtual void awake();
    virtual void update();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CFireWoodScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CFireWoodScript();
    ~CFireWoodScript();
};