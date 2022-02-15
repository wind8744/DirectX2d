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
    Vec2    m_Target;
    Vec2    m_TargetDir;
    Vec2    m_ColliderPos;
public:
    virtual void update();
    virtual void awake();
public:
    void SetDir(DIR _Dir) { m_DIR = _Dir; }
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    void SetTarget(Vec2 _Target) { m_Target = _Target; }
    void SetCoSetPos(Vec2 _Pos) { m_ColliderPos = _Pos; }

    Vec2 GetTargeDir() { return m_TargetDir; }
public:
    CLONE(CTargetToAuto);

public:
    CTargetToAuto();
    ~CTargetToAuto();
 
};

