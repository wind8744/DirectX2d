#include "pch.h"
#include "CBreakableStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CEventMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CBreakableStoneScript::CBreakableStoneScript()
	: CScript((int)SCRIPT_TYPE::BREAKABLESTONESCRIPT)
	, m_bIsCol(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
	, m_bIsBreak(false)
{
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"breakablestone");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CBreakableStoneScript::~CBreakableStoneScript()
{
}

void CBreakableStoneScript::awake()
{
	//플레이어 스크립트
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CBreakableStoneScript::update()
{
	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();

	//충돌상태이고 플레이어가 z키를 누르고있을때 
	if (m_bIsCol == true && _curstate == PLAYER_STATE::BREAK)
	{
		m_fAtime += fDT;
		if (m_fAtime > 1.f) //2초후 삭제;
		{
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::IDLE);
			m_pPlayerScript->SetPlayerIsOnCol(false);
			m_bIsBreak = true; //돌 깨짐

			//부셔지는 이펙트 + 본인 오브젝트 삭제
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);

		}	
	}

	//폭탄과 닿아 있을 때
	if (m_bIsCol == true && m_bIsBreak == true)
	{
		//부셔지는 이펙트 + 본인 오브젝트 삭제
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}
}

void CBreakableStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsCol = true;

}

void CBreakableStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsCol = false;
}

void CBreakableStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBreakableStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

