#pragma once
#include <Engine\CScript.h>
class CTargetToAuto :
    public CScript
{
private:
   // float   m_fTime;
    //float   m_fMaxTime; //���ӽð�

    float   m_fSpeed;

    //���� �����ϱ� �켱 �ӽ�
    DIR     m_DIR;
    
   // float   m_angle;


public:
    virtual void update();
    virtual void awake();
public:
    void SetDir(DIR _Dir) { m_DIR = _Dir; }
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
public:
    CLONE(CTargetToAuto);

public:
    CTargetToAuto();
    ~CTargetToAuto();
 
};

