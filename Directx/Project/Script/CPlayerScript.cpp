#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPushStoneScript.h"
#include "CMissileScript.h"

CPlayerScript::CPlayerScript()
	: CScript((int)SCRIPT_TYPE::PLAYERSCRIPT)
	 ,m_pPlayerTex(nullptr)         
	 ,m_iTileX(0)               
	 ,m_iTileY(0)
	, m_iMapCol(10)
	, m_iMapRow(10)
	, m_fPlayerSpeed(200.f)
	, m_iHP(100)
	, m_eCurState(PLAYER_STATE::IDLE)            //�÷��̾��� ���� ����
	, m_ePrevState(PLAYER_STATE::IDLE)           //���� ����
	, m_eCurDir(DIR::DOWN)              //���� ����
	, m_ePreDir(DIR::DOWN)              //���� ����
	, m_IsOnCol(false)
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
	//�ӽ÷� Ÿ�� ���Ϳ� obj���� ����
	//int size = 10 * 10;
	//size_t sizet = (size_t)size;
	//m_vecTileInfo.resize(sizet);
	////�̴� �� ��ǥ
	//int _x = 0;
	//int _y = 2;
	//int z = _y * m_iMapCol + _x;
	////�̴� �� ����
	//tile_info _pushstone = {};
	//_pushstone.IsObj = true;
	//_pushstone.IsPush = true;
	//_pushstone.IsBlock = true;
	////�̴µ� ���� ����
	//m_vecTileInfo[z] = _pushstone;
	////��ư ��ǥ
	// _x = 3;
	// _y = 0;
	// z = _y * m_iMapCol + _x;
	////��ư ����
	// _pushstone = {};
	//_pushstone.IsObj = true;
	//_pushstone.IsPush = false;
	//_pushstone.IsBlock = false;
	////��ư ���� ����
	//m_vecTileInfo[z] = _pushstone;
	////���� ��ǥ
	//_x = 4;
	//_y = 4;
	//z = _y * m_iMapCol + _x;
	//_pushstone = {};
	//_pushstone.IsObj = true;
	//_pushstone.IsPush = false;
	//_pushstone.IsBlock = true;
	//m_vecTileInfo[z] = _pushstone;
}

void CPlayerScript::update()
{
	//���� Ÿ�� ��ġ ���
	UpdateTilePos();

	//Ű �Է� ����
	CheckState();

	//���� ���¿� �´� �ִϸ��̼� ���
	PlayAnimation();

	//�ٲ� ���� ����
	SetState();
	SetCurPlayerKey();

	//�ٲ� ���¿��� ������
	PlayerMove();

}


// �÷��̾��� ���� ��ǥ�� ���� Ÿ�� xy ���ϱ�
void CPlayerScript::UpdateTilePos()
{
	POINT vResolution;// = CCore::GetInst()->GetWndResolution(); //1600 900
	vResolution.x = 1600;
	vResolution.y = 900;

	Vec2 _vPos = { 0,0 }; //Ÿ��obj ��ǥ
	Vec3 _vPlayerPos = Transform()->GetLocalPos();
	int _Col = m_iMapCol;  // temp �� Ÿ�� ������
	int _Row = m_iMapRow;

	m_iTileX = (-1) * (_vPos.x + vResolution.x / 2 - (TileSize_X * _Col / 2) - (_vPlayerPos.x + TileSize_X / 2)) / TileSize_X + 12;// vMousePos.x / TILE_SIZE;
	m_iTileY = (_vPos.y + vResolution.y / 2 - (TileSize_Y * _Row / 2) - (_vPlayerPos.y)) / TileSize_Y + 3;
		//(_vPos.y + vResolution.y / 2 - (TileSize_Y * _Row / 2) - (_vPlayerPos.y)) / TileSize_Y ; //-

}

void CPlayerScript::CheckState()
{
	// Ű �Է¿� ���� �̵�
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalRot();

	//���� ���¸� ���� ���·� ������ ��
	m_ePrevState = m_eCurState; 
	m_ePreDir = m_eCurDir;

	if (m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::PUSH)
	{
		if (KEY_HOLD(KEY_TYPE::KEY_LEFT))// && m_vecTileInfo[m_iTileY * m_iMapCol + (m_iTileX - 1)].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::LEFT)
			{
				//������X
			}
			else
			{
				vPos.x -= m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::LEFT;
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))// && m_vecTileInfo[m_iTileY * m_iMapCol + (m_iTileX+1)].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::RIGHT)
			{
				//vPos.x -= 2;
			}
			else
			{
				vPos.x += m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::RIGHT;
			}

		}
		if (KEY_HOLD(KEY_TYPE::KEY_UP))// && m_vecTileInfo[(m_iTileY - 1) * m_iMapCol + m_iTileX].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::UP)
			{
				//vPos.y -= 2;
			}
			else
			{
				vPos.y += m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::UP;
			}

		}
		if (KEY_HOLD(KEY_TYPE::KEY_DOWN))// && m_vecTileInfo[(m_iTileY + 1) * m_iMapCol + m_iTileX].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::DOWN)
			{
				//vPos.y -= 2;
			}
			else
			{
				vPos.y -= m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::DOWN;
			}

		}
		if (KEY_HOLD(KEY_TYPE::KEY_Z))
		{
			m_eCurState = PLAYER_STATE::PUSH;
		}
		if (KEY_TAP(KEY_TYPE::KEY_Z))
		{

		}

	}

	//���ǵ� �������� �������� ��
	else if (m_eCurState == PLAYER_STATE::SLIDE && m_IsOnCol == false)
	{
		if (m_eCurDir == DIR::DOWN) vPos.y -= 800.f * fDT;
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
	const wstring& _str = _pOther->GetName();
	if (_str == L"PushStone" || _str == L"StoneDoor")
	{
		m_IsOnCol = true;
	}
}

void CPlayerScript::OnCollisionExit(CGameObject* _pOther)
{
	m_IsOnCol = false;
}

void CPlayerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CPlayerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}
