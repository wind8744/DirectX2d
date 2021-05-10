#include "pch.h"
#include "CSpeedUpScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>
#include <Engine\CCollider2D.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"

CSpeedUpScript::CSpeedUpScript()
	: CScript((int)SCRIPT_TYPE::SPEEDUPSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
	, m_fRotValue(1.58)
	, m_Dir(0)
	, m_PreDir(0)
{
	Ptr<CTexture> pTex   = CResMgr::GetInst()->FindRes<CTexture>(L"speedup");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());


	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "0123", &m_Dir));
}

CSpeedUpScript::~CSpeedUpScript()
{
}

void CSpeedUpScript::awake()
{
	//스크립트
	
	//발판 방향
	

}

void CSpeedUpScript::update()
{
	if (m_PreDir != m_Dir)
	{
		if (m_Dir == 1) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue));
		else if (m_Dir == 2) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 2));
		else if (m_Dir == 3) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 3));
		else Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 0));

	}
	if (m_bIsPushed == true && m_pPlayerScript != nullptr)
	{
		m_fAtime += DT;
		if (m_fAtime < 0.5f)
		{
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::SLIDE);
			if(m_Dir ==0)
			m_pPlayerScript->SetPlayerDir(DIR::DOWN); //왼쪽 발판일때 왼쪽으로 강제로 바꾸어줌
			else if (m_Dir == 1)
				m_pPlayerScript->SetPlayerDir(DIR::RIGHT);
			else if (m_Dir == 2)
				m_pPlayerScript->SetPlayerDir(DIR::UP);
			else if (m_Dir == 3)
				m_pPlayerScript->SetPlayerDir(DIR::LEFT);
		}
		else
		{
			m_bIsPushed = false;
			
			m_fAtime = 0.f;
			if(m_pPlayerScript->GetPlayerItem() == PLAYER_ITEM::NONE)
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::IDLE);
			else
				m_pPlayerScript->SetPlayerState(PLAYER_STATE::ITEM);
			m_pPlayerScript = nullptr;
		}
	}
	m_PreDir = m_Dir;
}

void CSpeedUpScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (nullptr != _pOther->GetScript(L"CPlayerScript"))
	{
		m_pPlayerScript = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
		Vec3 Pos = Transform()->GetLocalPos();
		
		m_bIsPushed = true;
	
		
		if (m_Dir ==0 || m_Dir == 3)
		{
			m_pPlayerScript->Transform()->SetLocalPosX(Pos.x);
		}
		else if (m_Dir == 1 || m_Dir == 4)
		{
			m_pPlayerScript->Transform()->SetLocalPosY(Pos.y);
		}
		
		
	}

}

void CSpeedUpScript::OnCollision(CGameObject* _pOther)
{
	//부딪힌 오브젝트 이름 받아옴
	
}

void CSpeedUpScript::OnCollisionExit(CGameObject* _pOther)
{

}

void CSpeedUpScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
	fwrite(&m_Dir, sizeof(int), 1, _pFile);
	fwrite(&m_fRotValue, sizeof(float), 1, _pFile);
}

void CSpeedUpScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
	fread(&m_Dir, sizeof(int), 1, _pFile);
	fread(&m_fRotValue, sizeof(float), 1, _pFile);
}

