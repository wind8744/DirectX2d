#include "pch.h"
#include "CBombFlowerScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine/CEventMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CCollider2D.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CBombScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombFlowerScript::CBombFlowerScript()
	: CScript((int)SCRIPT_TYPE::BOMBFLOWERSCRIPT)
	, m_eState(FLOWER_STATE::IDLE)
	, m_IsOnCol(false)
	, m_pPlayerScript(nullptr)
	, m_fAtime(0.f)
{
	m_pTex1 = CResMgr::GetInst()->FindRes<CTexture>(L"bombflower");
	m_pTex2 = CResMgr::GetInst()->FindRes<CTexture>(L"flower");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex1.Get());
}

CBombFlowerScript::~CBombFlowerScript()
{
}

void CBombFlowerScript::awake()
{
	//스크립트
	CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");

	m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CBombFlowerScript::update()
{
	CheckState();
	Excute();
}


void CBombFlowerScript::CheckState()
{
	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();
	PLAYER_STATE _prevstate = m_pPlayerScript->GetPlayerPrevState();

	//충돌상태이면서, 플레이어가 아이템 상태일때
	if (m_eState == FLOWER_STATE::COL && _curstate == PLAYER_STATE::ITEM && m_pPlayerScript->GetPlayerItem() == PLAYER_ITEM::BOMB) m_eState = FLOWER_STATE::BOMB;

	//머리 위에 있었는데, 플레이어가 놓았을 때
	else if (m_eState == FLOWER_STATE::HEAD && _curstate == PLAYER_STATE::IDLE)
	{
		//아무것도 없는 상태
		m_eState = FLOWER_STATE::NONE;
	}

}

void CBombFlowerScript::Excute()
{
	if (m_eState == FLOWER_STATE::BOMB)
	{
		// 폭탄 없는 꽃으로 이미지 변경
		m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex2.Get());
		
		// 플레이어 머리 위에 폭탄 생성
		Vec3 _PlayerPos = m_pPlayerScript->Transform()->GetLocalPos();
		
		// ===============
		// Bomb (폭탄)
		// ===============
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"Bomb"); /////
		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CCollider2D);
		pObj->AddComponent(new CBombScript); ////
		pObj->Transform()->SetLocalPos(_PlayerPos);
		pObj->Transform()->SetLocalScale(Vec3(40, 50, 1.f));
		pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
		pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl"));/////
		pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

		//폭탄 오브젝트 생성 이벤트 추가
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
		_temp.lParam = (DWORD_PTR)pObj;
		CEventMgr::GetInst()->AddEvent(_temp);

		//만든 후 head 상태로
		m_eState = FLOWER_STATE::HEAD;
	}
	else if (m_eState == FLOWER_STATE::NONE)
	{
		//3초후 폭탄 생성
		m_fAtime += fDT;
		if (m_fAtime >= 3.f)
		{
			m_eState = FLOWER_STATE::MAKEBOMB;
			m_fAtime = 0.f;
		}
	}
	else if (m_eState == FLOWER_STATE::MAKEBOMB)
	{
		//폭탄 다시 생성 후 idle (처음) 상태로
		m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex1.Get());
		m_eState = FLOWER_STATE::IDLE;
	}
}


void CBombFlowerScript::OnCollisionEnter(CGameObject* _pOther)
{
	//부딪힌 오브젝트 이름 받아옴
	if (nullptr != _pOther->GetScript(L"CPlayerScript"))
	{
		//idle상태일때만 
		if(m_eState == FLOWER_STATE::IDLE ) m_eState = FLOWER_STATE::COL;
	}

}

void CBombFlowerScript::OnCollisionExit(CGameObject* _pOther)
{
	//m_bIsPushed = false;
}

void CBombFlowerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBombFlowerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

