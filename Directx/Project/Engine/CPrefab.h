#pragma once
#include "CRes.h"

class CGameObject;

class CPrefab :
    public CRes
{
private:
    CGameObject*    m_pProtoObj;
    Vec3            m_OffSet;

public:
    CGameObject*    Instantiate();

public:
    CGameObject* GetGameObject() { return m_pProtoObj; }
    void         SetOffSet(Vec3 _OffSet) { m_OffSet = _OffSet; }
    Vec3         GetOffSet() { return m_OffSet; }
public:
    virtual void Save(const wstring& _strRelativePath);

private:
    virtual void Load(const wstring& _strFilePath);

public:
    CPrefab();
    CPrefab(CGameObject* _pProto);
    ~CPrefab();
};

