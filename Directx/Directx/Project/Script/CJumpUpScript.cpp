#include "pch.h"
#include "CJumpUpScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>
#include <Engine\CCollider2D.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"

CJumpUpScript::CJumpUpScript()
	: CScript((int)SCRIPT_TYPE::JUMPUPSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
	, m_fRotValue(1.58)
	, m_Dir(1)
	, m_PreDir(0)
	, m_bFlag(false)
{
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"jumpup");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"JumpUpMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "0123(dir)", &m_Dir));
}
CJumpUpScript::~CJumpUpScript() {}

void CJumpUpScript::awake() {}

void CJumpUpScript::update()
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
		m_fAtime += fDT;
		if (m_fAtime < 1.f)
		//if(m_bFlag == false)  //test
		{
			m_pPlayerScript->SetPlayerState(PLAYER_STATE::JUMP);

			if (m_Dir == 0)
				m_pPlayerScript->SetPlayerDir(DIR::DOWN); //왼쪽 발판일때 플레이어의 왼쪽으로 강제로 바꾸어줌
			else if (m_Dir == 1)
				m_pPlayerScript->SetPlayerDir(DIR::RIGHT);
			else if (m_Dir == 2)
				m_pPlayerScript->SetPlayerDir(DIR::UP);
			else if (m_Dir == 3)
				m_pPlayerScript->SetPlayerDir(DIR::LEFT);

			//m_bFlag = true;  //test
		}
		else // 시간이 지나면 발판상태 초기화
		{
			m_bIsPushed = false;
			m_fAtime = 0.f;
			m_pPlayerScript = nullptr;
		}
	}
	m_PreDir = m_Dir;
}

void CJumpUpScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (nullptr != _pOther->GetScript(L"CPlayerScript"))
	{
		m_pPlayerScript = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
	
		m_pPlayerScript->SetPlayerJumpSpeed(Vec2(550.f, 500.f));
		m_bIsPushed = true;
	}

}

void CJumpUpScript::OnCollision(CGameObject* _pOther)
{
	//부딪힌 오브젝트 이름 받아옴
	//m_bIsPushed = false;

}

void CJumpUpScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
	m_pPlayerScript = nullptr;
}

void CJumpUpScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
	fwrite(&m_Dir, sizeof(int), 1, _pFile);
	fwrite(&m_fRotValue, sizeof(float), 1, _pFile);
}

void CJumpUpScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
	fread(&m_Dir, sizeof(int), 1, _pFile);
	fread(&m_fRotValue, sizeof(float), 1, _pFile);
}

