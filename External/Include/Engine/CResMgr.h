#pragma once
#include "CSingleton.h"

#include "CPathMgr.h"

#include "Ptr.h"
#include "CMesh.h"
#include "CGraphicsShader.h"
#include "CComputeShader.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CPrefab.h"
#include "CSound.h"

class CResMgr
    : public CSingleton<CResMgr>
{
    SINGLE(CResMgr);
private:
    map<wstring, CRes*>      m_mapRes[(UINT)RES_TYPE::END];

    vector<CRes*>         m_vecCloneRes[(UINT)RES_TYPE::END];

    bool               m_bEvent; // Resource �� ���Ӱ� �߰� �ǰų� �����Ǵ� ��츦 �����ϴ� �뵵

public:
    void init();

    void ClearCloneRes();
    bool HasEvnOcrd()
    {
        bool bReturn = m_bEvent;
        m_bEvent = false;
        return bReturn;
    }

public:
    Ptr<CTexture> CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, UINT _eBindFlag, DXGI_FORMAT _eFormat);
    Ptr<CTexture> CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D);

    template<typename T>
    Ptr<T> Load(const wstring& _strKey, const wstring& _strRelativePath);

    template<typename T>
    void AddRes(const wstring& _strKey, Ptr<T> _pRes);

    template<typename T>
    void AddCloneRes(Ptr<T> _pCloneRes);

    template<typename T>
    Ptr<T> FindRes(const wstring& _strKey);

    const map<wstring, CRes*>& GetRes(RES_TYPE _eType) { return m_mapRes[(UINT)_eType]; }

   

private:
    void CreateDefaultMesh();
    void CreateDefaultShader();
    void CreateComputeShader();
    void CreateDefaultMaterial();
    void InitSound();
};

template<typename T>
RES_TYPE GetResType()
{
    const type_info& info = typeid(T);

    if (typeid(CMesh).hash_code() == info.hash_code())
        return RES_TYPE::MESH;
    else if (typeid(CGraphicsShader).hash_code() == info.hash_code()
        || typeid(CComputeShader).hash_code() == info.hash_code())
        return RES_TYPE::SHADER;
    else if (typeid(CTexture).hash_code() == info.hash_code())
        return RES_TYPE::TEXTURE;
    else if (typeid(CMaterial).hash_code() == info.hash_code())
        return RES_TYPE::MATERIAL;
    else if (typeid(CPrefab).hash_code() == info.hash_code())
        return RES_TYPE::PREFAB;
    else if (typeid(CSound).hash_code() == info.hash_code())
        return RES_TYPE::SOUND;
    else
        return RES_TYPE::END;

}


template<typename T>
inline Ptr<T> CResMgr::Load(const wstring& _strKey, const wstring& _strRelativePath)
{
    RES_TYPE eType = GetResType<T>();

    CRes* pRes = FindRes<T>(_strKey).Get();
    assert(!pRes);

    wstring strFilePath = CPathMgr::GetResPath();
    strFilePath += _strRelativePath;

    pRes = new T;
    pRes->Load(strFilePath);

    pRes->SetKey(_strKey);
    pRes->SetRelativePath(_strRelativePath);

    m_mapRes[(UINT)eType].insert(make_pair(_strKey, pRes));
    m_bEvent = true;

    return (T*)pRes;
}

template<typename T>
inline void CResMgr::AddRes(const wstring& _strKey, Ptr<T> _pRes)
{
    RES_TYPE type = GetResType<T>();

    // �ߺ�Ű �˻�
    // �̹� ������ Ű�� ���ҽ��� ��ϵǾ��ִ°�� assert
    assert(nullptr == FindRes<T>(_strKey));

    _pRes->SetKey(_strKey);
    m_mapRes[(UINT)type].insert(make_pair(_strKey, _pRes.Get()));
    m_bEvent = true;

}

template<typename T>
inline void CResMgr::AddCloneRes(Ptr<T> _pCloneRes)
{
    RES_TYPE type = GetResType<T>();
    m_vecCloneRes[(UINT)type].push_back(_pCloneRes.Get());
}

template<typename T>
inline Ptr<T> CResMgr::FindRes(const wstring& _strKey)
{
    RES_TYPE type = GetResType<T>();

    map<wstring, CRes*>::iterator iter = m_mapRes[(UINT)type].find(_strKey);

    // Ű�� �ش��ϴ� ���ҽ��� ���� ���
    if (iter == m_mapRes[(UINT)type].end())
        return nullptr;

    return (T*)iter->second;
}



