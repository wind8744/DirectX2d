#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    vector<CGameObject*>        m_vecParentObj; // �ֻ��� �θ� ������Ʈ
    vector<CGameObject*>        m_vecObject;    // ���̾� �Ҽ� ��� ������Ʈ
    int                         m_iLayerIndex;

public:
    void awake();
    void start();

    void update();
    void lateupdate();
    void finalupdate();

public:
    // _pObject : Layer �� �ԷµǴ� Object, _bMoveChild : �ڽ� ������Ʈ�� ���̾� �Ҽ��� ���� �������� ����
    void AddObject(CGameObject* _pObject, bool _bMoveChild);
    void ClearObject() { m_vecObject.clear(); }

    // Layer �� �Ҽӵ� �ֻ��� �θ������Ʈ ����� �����´�.
    const vector<CGameObject*>& GetParentObj() { return m_vecParentObj; }

    // Layer �� �Ҽӵ� ��� ������Ʈ ����� �����´�(finalupdate ���� ��ȿ)
    const vector<CGameObject*>& GetObjects() { return m_vecObject; }

private:
    void RegisterObject(CGameObject* _pObj){m_vecObject.push_back(_pObj);}

protected:
    CLONE_DISABLE(CLayer);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CLayer(int _iLayerIdx);
    ~CLayer();

    friend class CGameObject;
    friend class CScene;
};

