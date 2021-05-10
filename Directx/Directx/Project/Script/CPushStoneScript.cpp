#include "pch.h"
#include "CPushStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CTimeMgr.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"

CPushStoneScript::CPushStoneScript()
	: CScript((int)SCRIPT_TYPE::PUSHSTONESCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	Ptr<CTexture> pTex  = CResMgr::GetInst()->FindRes<CTexture>(L"pushstone");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CPushStoneScript::~CPushStoneScript()
{
}

void CPushStoneScript::awake()
{
	//플레이어 스크립트
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CPushStoneScript::update()
{

	Vec3 vPos = Transform()->GetLocalPos();

	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();
	DIR _curdir = m_pPlayerScript->GetPlayerDir();

	//충돌상태이고 플레이어가 z키를 누르고있을때 
	if (m_bIsPushed == true && _curstate == PLAYER_STATE::PUSH)
	{
		if (_curdir == DIR::RIGHT)
		{
			vPos.x += 150.f* fDT;
		}
		if (_curdir == DIR::LEFT)
		{
			vPos.x -= 150.f * fDT;
		}
		if (_curdir == DIR::DOWN)
		{
			vPos.y -= 150.f * fDT;
		}
		if (_curdir == DIR::UP)
		{
			vPos.y += 150.f * fDT;
		}
	}

	Transform()->SetLocalPos(vPos);

}

void CPushStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CPushStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
	//if (m_pEventScript != nullptr)
	//{
	//	m_pEventScript->SetTrigger(false);
	//}
}

void CPushStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CPushStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

