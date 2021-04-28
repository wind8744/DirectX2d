#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: CScript((int)SCRIPT_TYPE::PLAYERSCRIPT)
	 ,m_pPlayerTex(nullptr)         
	 ,m_PlayerState(PLAYER_STATE::IDLE)
	 ,m_iTileX(0)               
	 ,m_iTileY(0)               
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

	//temp
	//임시로 타일 벡터에 obj정보 넣음
	int size = 10 * 10;
	size_t sizet = (size_t)size;
	m_vecTileInfo.resize(sizet);
	//int z = _y * m_iCol + _x;
	//m_vecTileInfo[z]

}

void CPlayerScript::update()
{
	//현재 타일 위치 계산
	UpdateTilePos();

	//키 입력 받음
	InputKey();

	//현재 상태에 맞는 애니메이션 재생
	PlayAnimation();

	//바뀐 상태 저장
	SetState();
	SetCurPlayerKey();

	//바뀐 상태에서 움직임
	PlayerMove();

}


// 플레이어의 현재 좌표에 대한 타일 xy 구하기
void CPlayerScript::UpdateTilePos()
{
	POINT vResolution;// = CCore::GetInst()->GetWndResolution(); //1600 900
	vResolution.x = 1600;
	vResolution.y = 900;

	Vec2 _vPos = { 0,0 }; //타일obj 좌표
	Vec3 _vPlayerPos = Transform()->GetLocalPos();
	int _Col = 10;  // temp 맵 타일 사이즈
	int _Row = 10;

	m_iTileX = (-1) * (_vPos.x + vResolution.x / 2 - (TileSize_X * _Col / 2) - (_vPlayerPos.x + TileSize_X / 2)) / TileSize_X + 12;// vMousePos.x / TILE_SIZE;
	m_iTileY = (_vPos.y + vResolution.y / 2 - (TileSize_Y * _Row / 2) - (_vPlayerPos.y)) / TileSize_Y + 3;
		//(_vPos.y + vResolution.y / 2 - (TileSize_Y * _Row / 2) - (_vPlayerPos.y)) / TileSize_Y ; //-

}

void CPlayerScript::InputKey()
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
	//if (KEY_HOLD(KEY_TYPE::KEY_Z))
	//{
	//	vRot.z += fDT * XM_PI;
	//}
	//if (KEY_TAP(KEY_TYPE::SPACE))
	//{
	//	CreateMissile();
	//}
	Transform()->SetLocalPos(vPos);
	Transform()->SetLocalRot(vRot);
}

void CPlayerScript::CreateMissile()
{
	Vec3 vStartPos = Transform()->GetWorldPos();
	vStartPos.y += Transform()->GetWorldScale().y / 2.f;

	Instantiate(m_pMissilePrefab, vStartPos);
}

void CPlayerScript::PlayAnimation()
{
}

void CPlayerScript::SetState()
{
}

void CPlayerScript::SetCurPlayerKey()
{
}

void CPlayerScript::PlayerMove()
{
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
