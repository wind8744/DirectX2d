#include "pch.h"
#include "Temp.h"

#include "CCore.h"
#include "CDevice.h"

#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CMesh.h"
#include "CShader.h"
#include "CConstBuffer.h"

#include "CResMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CCamera.h"

CGameObject*	g_pObject = nullptr;
CGameObject*	g_pCamObj = nullptr;


void TempInit()
{
	
}

void TempUpdate()
{
	Vec3 vPos = g_pObject->Transform()->GetLocalPos();
	Vec3 vRot = g_pObject->Transform()->GetLocalRot();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT) == KEY_STATE::HOLD)
	{		
		vPos.x -= CTimeMgr::GetInst()->GetfDT() * 1.f;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += CTimeMgr::GetInst()->GetfDT() * 1.f;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W) == KEY_STATE::HOLD)
	{
		vRot.y += CTimeMgr::GetInst()->GetfDT() * 1.f;
	}

	g_pObject->Transform()->SetLocalPos(vPos);
	g_pObject->Transform()->SetLocalRot(vRot);

	g_pCamObj->Camera()->finalupdate();
	g_pObject->Transform()->finalupdate();
}

void TempRender()
{
	// Ÿ�� Ŭ����
	CDevice::GetInst()->ClearTarget();

	// ���� ������ ����	
	g_pObject->MeshRender()->render();

	CDevice::GetInst()->Present();
}

void TempRelease()
{	
	delete g_pObject;
	delete g_pCamObj;
}

// ������Ʈ 2�� �����
// �ϳ��� �ٸ� ������Ʈ �ֺ��� ���� ����