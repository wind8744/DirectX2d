#pragma once
#include "CShader.h"

class CGraphicsShader :
    public CShader
{
public:
    static vector<D3D11_INPUT_ELEMENT_DESC> g_vecLayoutDesc;
    static int g_iOffset;

private:
    ComPtr<ID3DBlob>			    m_vsBlob;
    ComPtr<ID3DBlob>			    m_hsBlob;
    ComPtr<ID3DBlob>			    m_dsBlob;
    ComPtr<ID3DBlob>			    m_gsBlob;
    ComPtr<ID3DBlob>			    m_psBlob;

    ComPtr<ID3D11VertexShader>      m_pVS;
    ComPtr<ID3D11HullShader>        m_pHS;
    ComPtr<ID3D11DomainShader>      m_pDS;
    ComPtr<ID3D11GeometryShader>    m_pGS;
    ComPtr<ID3D11PixelShader>       m_pPS;

    ComPtr<ID3D11InputLayout>       m_pLayout;
    BLEND_TYPE                      m_BlendType;
    DS_TYPE                         m_DSType;

    SHADER_POV                      m_ePOV;

public:
    static void AddInputLayout(const char* _pSemanticName, int _iSemanticIdx, DXGI_FORMAT _eFormat, bool _bInstancing);

    void CreateVertexShader(const wstring& _strRelativePath, const char* _strFuncName);
    //void CreateHullShader();
    //void CreateDomainShader();
    void CreateGeometryShader(const wstring& _strRelativePath, const char* _strFuncName);
    void CreatePixelShader(const wstring& _strRelativePath, const char* _strFuncName);

    GET_SET(BLEND_TYPE, BlendType);
    GET_SET(DS_TYPE, DSType);
    
    void UpdateData();

    SHADER_POV GetPOV() { return m_ePOV; }

public:
    CGraphicsShader();
    CGraphicsShader(SHADER_POV _ePOV);
    ~CGraphicsShader();
};

