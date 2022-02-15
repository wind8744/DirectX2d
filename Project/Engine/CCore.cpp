#include "pch.h"
#include "CCore.h"

#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CResMgr.h"
#include "CRenderMgr.h"
#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include <Script\CScriptMgr.h>
#include "CConstBuffer.h"

CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptWndRes{}
{
}

CCore::~CCore()
{	
}

int CCore::init(HWND _hWnd, POINT _ptResolution, bool _bWindow)
{
	m_hWnd = _hWnd;
	m_ptWndRes = _ptResolution;

	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	//CResMgr::GetInst();

	if (FAILED(CDevice::GetInst()->init(m_hWnd, m_ptWndRes, _bWindow)))
	{
		return E_FAIL;
	}

	// ==============
	// Manager �ʱ�ȭ
	// ==============
	CPathMgr::init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	
	CSceneMgr::GetInst()->init();

	

	return S_OK;
}



void CCore::progress()
{
	// ======
	// Update
	// ======
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CRenderMgr::GetInst()->update();
	CSound::g_pFMOD->update();
	CSceneMgr::GetInst()->progress();
	CCollisionMgr::GetInst()->update();
	
	// ======
	// Render
	// ======
	// Ÿ�� Ŭ����
	CDevice::GetInst()->ClearTarget();
	CRenderMgr::GetInst()->render();	

	// Event ó��
	CEventMgr::GetInst()->update();
}

