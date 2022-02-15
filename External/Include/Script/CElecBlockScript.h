
#pragma once
#include <Engine\CScript.h>

// obj name : ���� ���(�� �� ����)
// desc : ���� ���� ��

class CPlayerScript;
class CObjEventScript;
class CElecBlockScript :
    public CScript
{
private:
    CScript* m_pTarScript;
    //CPlayerScript*          m_pPlayerScript;
    CObjEventScript*        m_pEventScript;
    bool                    m_bIsLinked;        //����Ǿ�����?
    bool                    m_bIsPushed;        //�̴����ΰ�?
    bool                    m_bIsCol;           //�浹���ΰ�?

    CGameObject* m_Child;
    DIR                     m_pushdir;

    //bool m_stop;
    CDIR                m_eColliderDir;

public:
    bool GetIsPushed() { return m_bIsPushed; }
    bool GetIsLinked() { return m_bIsLinked; }
    void SetIsLinked(bool _link) { m_bIsLinked = _link; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);

public:
    CLONE(CElecBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecBlockScript();
    ~CElecBlockScript();
};