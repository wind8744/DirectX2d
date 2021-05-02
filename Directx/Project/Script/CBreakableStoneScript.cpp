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
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBreakableStoneScript::CBreakableStoneScript()
	: CScript((int)SCRIPT_TYPE::BREAKABLESTONESCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
{
	m_pStoneTex = CResMgr::GetInst()->FindRes<CTexture>(L"breakablestone");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pStoneTex.Get());
}

CBreakableStoneScript::~CBreakableStoneScript()
{
}

void CBreakableStoneScript::awake()
{
	//�÷��̾� ��ũ��Ʈ
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CBreakableStoneScript::update()
{
	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();

	//�浹�����̰� �÷��̾ zŰ�� ������������ 
	if (m_bIsPushed == true && _curstate == PLAYER_STATE::BREAK)
	{
		m_fAtime += fDT;
		if (m_fAtime > 2.f) //2���� ����;
		{
			m_fAtime = 0.f;
			//�μ����� ����Ʈ + ���� ������Ʈ ����
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);

			m_pPlayerScript->SetPlayerState(PLAYER_STATE::IDLE);
		}	
	}
}

void CBreakableStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CBreakableStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CBreakableStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBreakableStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

