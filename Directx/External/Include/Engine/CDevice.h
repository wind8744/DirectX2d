#pragma once

#include "CSingleton.h"

#include "CTexture.h"

class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice);
private:
	ComPtr<ID3D11Device>			m_pDevice;		// GUP memory ���� �� ��ü ���� �뵵
	ComPtr<ID3D11DeviceContext>		m_pContext;		// GPU �� �̿��� ������ ���� ��� ����
	ComPtr<IDXGISwapChain>			m_pSwapChain;	// �������� Ÿ�� �ؽ��� ����, back, front ���� ����

	Ptr<CTexture>					m_pRTTex;
	Ptr<CTexture>					m_pDSTex;
	
	D3D11_VIEWPORT					m_tViewPort;
	ComPtr<ID3D11SamplerState>		m_pSamplerState;

	HWND							m_hOutputWindowHwnd;
	POINT							m_ptBufferResolution;
	bool							m_bWindow;

	ComPtr<ID3D11SamplerState>		m_arrSam[2];

	CConstBuffer*					m_arrCB[(UINT)CB_TYPE::END];

	ComPtr<ID3D11BlendState>		m_arrBS[(UINT)BLEND_TYPE::END];
	ComPtr<ID3D11DepthStencilState> m_arrDSS[(UINT)DS_TYPE::END];


public:
	int init(HWND _hWnd, POINT _ptResolution, bool _bWindow);

public:
	ComPtr<ID3D11Device> GetDevice() { return m_pDevice; }
	ComPtr<ID3D11DeviceContext> GetContext() { return m_pContext; }

	const CConstBuffer* GetCB(CB_TYPE _eType) { return m_arrCB[(UINT)_eType]; }
	POINT GetBufferResolution() { return m_ptBufferResolution; }

	ComPtr<ID3D11BlendState> GetBlendState(BLEND_TYPE _eType) { return m_arrBS[(UINT)_eType]; }
	ComPtr<ID3D11DepthStencilState> GetDepthStencilState(DS_TYPE _eType) { return m_arrDSS[(UINT)_eType]; }

	void Present() { m_pSwapChain->Present(0, 0); }
	void ClearTarget();

	Ptr<CTexture> GetRenderTargetTex() { return m_pRTTex; }

private:
	int CreateSwapChain();
	int CreateView();
	void CreateViewPort();	
	void CreateConstBuffer();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateDepthStencilState();
};

