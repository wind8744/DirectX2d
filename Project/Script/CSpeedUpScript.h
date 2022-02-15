#pragma once
#include <Engine\CScript.h>

// obj name : ���ǵ� �� ����
// desc : �÷��̾ ������ ������

class CPlayerScript;

class CSpeedUpScript :
    public CScript
{
private:
    bool                    m_bCol;                 //�浹���ΰ�?
    int                     m_Dir;
    int                     m_PreDir;
    bool                    m_bIsSlide;            //�̲������°�?
     
    float                   m_fRotValue;           //90��
    bool                    m_bOneTime;             //�ѹ���

public:
    //bool GetIsPushed() { return m_bIsPushed; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CSpeedUpScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CSpeedUpScript();
    ~CSpeedUpScript();
};
