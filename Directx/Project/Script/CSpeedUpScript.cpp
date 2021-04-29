#include "pch.h"
#include "CSpeedUpScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"

CSpeedUpScript::CSpeedUpScript()
	: CScript((int)SCRIPT_TYPE::SPEEDUPSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
{
	m_pRedButTex = CResMgr::GetInst()->FindRes<CTexture>(L"speedup");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pRedButTex.Get());
}

CSpeedUpScript::~CSpeedUpScript()
{
}

void CSpeedUpScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CSpeedUpScript::update()
{
	if (m_bIsPushed == true)
	{
		m_fAtime += DT;
		if (m_fAtime < 0.5f)
		{
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::SLIDE);
			m_pPlayerScript->SetPlayerDir(DIR::DOWN); //왼쪽 발판일때 왼쪽으로 강제로 바꾸어줌
		}
		else
		{
			m_bIsPushed = false;
			m_fAtime = 0.f;
			//m_pPlayerScript->SetStopPlayerState(PLAYER_STATE::STOP);
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::IDLE);
		}
	}
	
}

void CSpeedUpScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;
}

void CSpeedUpScript::OnCollisionExit(CGameObject* _pOther)
{
	//m_bIsPushed = false;
	//충돌이 끝나면 플레이어 상태를 처음으로 다시 되돌려 줌
	//m_pPlayerScript->SetPlayerState(PLAYER_STATE::NONE);
	//m_pPlayerScript->SetPlayerKey(KEY_TYPE::KEY_DOWN); //왼쪽 발판일때 왼쪽으로 강제로 바꾸어줌
}

void CSpeedUpScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CSpeedUpScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

