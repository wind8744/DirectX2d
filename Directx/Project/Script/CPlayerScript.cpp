#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: CScript((int)SCRIPT_TYPE::PLAYERSCRIPT)
{
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "Int Data", &m_iData));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "float Data", &m_fData));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::VEC2, "Vec2 Data", &m_v2Data));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::VEC4, "Vec4 Data", &m_v4Data));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::PREFAB, "Missile", &m_pMissilePrefab));
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::awake()
{
	m_pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"Missile");
}

void CPlayerScript::update()
{
	// 키 입력에 따른 이동
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalRot();

	if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
	{
		vPos.x -= 200.f * fDT;
	}

	if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
	{
		vPos.x += 200.f * fDT;
	}

	if (KEY_HOLD(KEY_TYPE::KEY_UP))
	{
		vPos.y += 200.f * fDT;
	}

	if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
	{
		vPos.y -= 200.f * fDT;
	}


	if (KEY_HOLD(KEY_TYPE::KEY_Z))
	{
		vRot.z += fDT * XM_PI;
	}

	if (KEY_TAP(KEY_TYPE::SPACE))
	{
		CreateMissile();
	}


	Transform()->SetLocalPos(vPos);
	Transform()->SetLocalRot(vRot);
}

void CPlayerScript::CreateMissile()
{
	Vec3 vStartPos = Transform()->GetWorldPos();
	vStartPos.y += Transform()->GetWorldScale().y / 2.f;

	Instantiate(m_pMissilePrefab, vStartPos);	
}

void CPlayerScript::OnCollisionEnter(CGameObject* _pOther)
{
	
}

void CPlayerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);


}

void CPlayerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);


}
