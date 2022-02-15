#pragma once
#include "CRes.h"

#include <DirectXTex\DirectXTex.h>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex.lib")
#endif

class CTexture :
    public CRes
{
private:
    ScratchImage                        m_Image;    // SystemMem �� �ε�� ������ 
    ComPtr<ID3D11Texture2D>             m_pTex2D;   // GPU �� �ε��� �ؽ��� �������̽�
    
    ComPtr<ID3D11RenderTargetView>      m_pRTV;     // ����Ÿ�� �뵵 ������ View
    ComPtr<ID3D11DepthStencilView>      m_pDSV;     // ���� ���ٽ� �뵵 ������ View
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;     // ���̴� ���ҽ� ��(���ҽ� ���ε� �뵵)
    ComPtr<ID3D11UnorderedAccessView>   m_pUAV;     // RWTexture(register u) ���ε�



    D3D11_TEXTURE2D_DESC                m_tDesc;    // GPU Texture2D ����

public:
    int Create(UINT _iWidth, UINT _iHeight, UINT _eFlag , DXGI_FORMAT _eFormat);
    int Create(ComPtr<ID3D11Texture2D> _pTex2D);

    virtual void Save(const wstring& _strRelativePath);
    virtual void Load(const wstring& _strFilePath);

    void UpdateData(UINT _iRegisterNum, UINT _iPipelineStage);
    void UpdateDataRW(UINT _iRegisterNum);

    static void Clear(UINT _iRegisterNum, UINT _iPipelineStage);
    static void ClearRW(UINT _iRegisterNum);

    UINT Width() {return m_tDesc.Width; }
    UINT Height() { return m_tDesc.Height; }

    ComPtr<ID3D11Texture2D> GetTex2D() { return m_pTex2D; }
    ComPtr<ID3D11RenderTargetView> GetRTV() { return m_pRTV; }
    ComPtr<ID3D11DepthStencilView> GetDSV() { return m_pDSV; }
    ComPtr<ID3D11ShaderResourceView> GetSRV() { return m_pSRV; }
    ComPtr<ID3D11UnorderedAccessView> GetUAV() { return m_pUAV; }


public:
    CTexture();
    ~CTexture();
};

