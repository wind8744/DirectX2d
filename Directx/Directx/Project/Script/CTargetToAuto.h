#pragma once
#include <Engine\CScript.h>
class CTargetToAuto :
    public CScript
{
private:
   // float   m_fTime;
    //float   m_fMaxTime; //지속시간

    float   m_fSpeed;

    //적이 없으니깐 우선 임시
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

