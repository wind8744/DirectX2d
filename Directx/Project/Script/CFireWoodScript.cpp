#include "pch.h"
#include "CFireWoodScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CFireWoodScript::CFireWoodScript()
	: CScript((int)SCRIPT_TYPE::FIREWOODSCRIPT)
	, m_pPlayerScript(nullptr)
	, m_pEventScript(nullptr)
	, m_bPlayAni(false)
	, m_OnTime(0.f)
	, m_Time(0.f)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firewood");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CFireWoodScript::~CFireWoodScript()
{
}

void CFireWoodScript::awake()
{

	//플레이어 스크립트
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
	m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
	m_Child = CSceneMgr::GetInst()->FindObjectByName(L"FireWoodChild");

}

void CFireWoodScript::update()
{

	if (m_pEventScript->GetTrigger())
	{
		//int a = 100;
		//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a); //쉐이더에 값 전달
		if (!m_bPlayAni)
		{
			m_Child->Animator2D()->PlayAnimation(L"BURN", true);
			m_bPlayAni = true;
		}
		if (m_OnTime > 0.f)
		{

			if (m_Time > m_OnTime)
			{
				m_pEventScript->SetTrigger(false);
				m_Time = 0;
			}
			m_Time += fDT;

		}

	}


}

void CFireWoodScript::OnCollisionEnter(CGameObject* _pOther)
{
	//부딪힌 오브젝트 이름 받아옴
	const wstring& _str = _pOther->GetName();
	if (_str == L"FireBowl")m_pEventScript->SetTrigger(true);
	if (_str == L"Player")
	{
		UINT _itemnum = m_pPlayerScript->GetPlayerItemNum();
		if (_itemnum == 2)m_pEventScript->SetTrigger(true);
	}
}

void CFireWoodScript::OnCollisionExit(CGameObject* _pOther)
{
	//m_IsOnCol = false;
}

void CFireWoodScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CFireWoodScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

