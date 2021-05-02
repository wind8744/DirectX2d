#include "pch.h"
#include "CBombScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine/CEventMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombScript::CBombScript()
	: CScript((int)SCRIPT_TYPE::BOMBSCRIPT)
	, m_pScript(nullptr)
	, m_pPlayerScript(nullptr)
	, m_eState(BOMB_STATE::ONHEAD)
	, m_fSpeed(350.f)
	, m_eDir(DIR::DOWN)
	, m_fAtime(0.f)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"bomb");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CBombScript::~CBombScript() {}
void CBombScript::awake()
{
	//스크립트
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
	m_pScript = PlayerObject->GetScript(L"CPlayerScript");
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CBombScript::update()
{
	CheckState();
	Move();
}

void CBombScript::CheckState()
{
	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();

	//머리 위에 있었는데, 플레이어가 놓았을 때
	if (m_eState == BOMB_STATE::ONHEAD && _curstate == PLAYER_STATE::IDLE)
	{
		//머리에서 던질때 위치, 방향 상태 저장
		m_fSpeed = 350.f;
		m_eDir = m_pPlayerScript->GetPlayerDir();
		m_vPos = m_pScript->Transform()->GetLocalPos();
		m_eState = BOMB_STATE::SLIDE;
	}
	else if (m_eState == BOMB_STATE::EXPLODE)
	{
		m_eState = BOMB_STATE::NONE;

		//부셔지는 이펙트 + 본인 오브젝트 삭제
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);

		m_pPlayerScript->SetPlayerState(PLAYER_STATE::IDLE);
	}
}

void CBombScript::Move()
{
	Vec3 _vPlayerpos = m_pScript->Transform()->GetLocalPos();
	Vec3 _vPos = Transform()->GetLocalPos();

	if (m_eState == BOMB_STATE::ONHEAD)
	{
		_vPos.x = _vPlayerpos.x;
		_vPos.y = _vPlayerpos.y + 30;

		Transform()->SetLocalPos(_vPos);
	}

	else if (m_eState == BOMB_STATE::SLIDE)
	{
		switch (m_eDir)
		{
		case DIR::RIGHT:
			m_vPos.x += m_fSpeed * fDT;
			break;

		case DIR::LEFT:
			m_vPos.x -= m_fSpeed * fDT;
			break;

		case DIR::DOWN:
			m_vPos.y -= m_fSpeed * fDT;
			break;

		case DIR::UP:
			m_vPos.y += m_fSpeed * fDT;
			break;
		}

		//마찰력
		if (m_fSpeed > 0)
		{
			m_fSpeed -= 1.5;   //0.05
		}
		else if (m_fSpeed < 0)
		{
			m_fSpeed += 1.5;
		}

		Transform()->SetLocalPos(m_vPos);

		m_fAtime += fDT;
		if (m_fAtime > 3.f)
		{
			m_fAtime = 0.f;
			//다 미끄러진 후 폭발
			m_eState = BOMB_STATE::EXPLODE;

		}
		
	}
}


void CBombScript::OnCollisionEnter(CGameObject* _pOther)
{

}

void CBombScript::OnCollisionExit(CGameObject* _pOther)
{

}

void CBombScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBombScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

