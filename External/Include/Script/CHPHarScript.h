#pragma once
#include <Engine\CScript.h>

class CObjState;
class CHPHarScript :
    public CScript
{

private:

    CObjState* m_ParentsState;

    CGameObject* m_HpBarRed;
    CGameObject* m_HpBarGreen;
    CGameObject* m_HpBarSkyblue;
    float      m_Hpratio;
    float      m_Coolratio;

    bool       m_Player; //true �÷��̾� false ����

public:
    virtual void update();
    virtual void awake();

public:
    GET_SET(bool, Player);
public:
    CLONE(CHPHarScript);

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
public:
    CHPHarScript();
    ~CHPHarScript();

};

