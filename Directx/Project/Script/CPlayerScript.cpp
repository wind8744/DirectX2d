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
	, m_pPlayerTex(nullptr)
	, m_iTileX(0)
	, m_iTileY(0)
	, m_iMapCol(10)
	, m_iMapRow(10)
	, m_fPlayerSpeed(200.f)
	, m_iHP(100)
	, m_eCurState(PLAYER_STATE::IDLE)            //�÷��̾��� ���� ����
	, m_ePrevState(PLAYER_STATE::IDLE)           //���� ����
	, m_eCurDir(DIR::DOWN)              //���� ����
	, m_ePreDir(DIR::DOWN)              //���� ����
	, m_IsOnCol(false)
	, m_fAtime(0.f)
	, m_iItem(0)
{
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "HP", &m_iHP));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "Speed", &m_fPlayerSpeed));
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

	if (m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::PUSH || m_eCurState == PLAYER_STATE::ITEM)
	{
		if (KEY_HOLD(KEY_TYPE::KEY_LEFT))// && m_vecTileInfo[m_iTileY * m_iMapCol + (m_iTileX - 1)].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::LEFT) {} //������X
			else
			{
				vPos.x -= m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::LEFT;
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))// && m_vecTileInfo[m_iTileY * m_iMapCol + (m_iTileX+1)].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::RIGHT) {} //������X
			else
			{
				vPos.x += m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::RIGHT;
			}

		}
		if (KEY_HOLD(KEY_TYPE::KEY_UP))// && m_vecTileInfo[(m_iTileY - 1) * m_iMapCol + m_iTileX].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::UP) {} //������X
			else
			{
				vPos.y += m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::UP;
			}

		}
		if (KEY_HOLD(KEY_TYPE::KEY_DOWN))// && m_vecTileInfo[(m_iTileY + 1) * m_iMapCol + m_iTileX].IsBlock == false)
		{
			if (m_IsOnCol == true && m_ePreDir == DIR::DOWN) {} //������X
			else
			{
				vPos.y -= m_fPlayerSpeed * fDT;
				m_eCurState = PLAYER_STATE::MOVE;
				m_eCurDir = DIR::DOWN;
			}

		}
		//HOLD
		if (KEY_HOLD(KEY_TYPE::KEY_Z))//|| KEY_TAP(KEY_TYPE::KEY_Z))
		{
			//�浹�� ��ü ��ũ��Ʈ �̳Ѱ� �޾ƿ�
			if (m_pTarObj != nullptr)
			{
				const wstring& _str = m_pTarObj->GetName();
				if (_str == L"PushStone" || _str == L"PushSmallStone")	m_eCurState = PLAYER_STATE::PUSH; //�м� �ִ� ���� ��
				if (_str == L"BreakableStone" || _str == L"BreakableSmallStone") m_eCurState = PLAYER_STATE::BREAK; //�ν� �� �ִ� ���� ��
			}
		}
		//TAP
		if (KEY_TAP(KEY_TYPE::KEY_Z) && m_iItem == 0) //������ ���
		{
			//�浹�� ��ü ��ũ��Ʈ �̳Ѱ� �޾ƿ�
			if (m_pTarObj != nullptr)
			{
				const wstring& _str = m_pTarObj->GetName();
				if (_str == L"BombFlower") { m_iItem = 1; m_eCurState = PLAYER_STATE::ITEM; }
				if (_str == L"FireBowl") { m_iItem = 2; m_eCurState = PLAYER_STATE::ITEM; }
			}
		}
		else if (KEY_TAP(KEY_TYPE::KEY_Z) && m_iItem != 0) //������ ������
		{
			m_iItem = 0;
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}

	//�����̵� ���� : ���ǵ� ���� ��
	else if (m_eCurState == PLAYER_STATE::SLIDE && m_IsOnCol == false)
	{
		if (m_eCurDir == DIR::DOWN) vPos.y -= 800.f * fDT;
		else if (m_eCurDir == DIR::UP) vPos.y += 800.f * fDT;
		else if (m_eCurDir == DIR::RIGHT) vPos.x += 800.f * fDT;
		else if (m_eCurDir == DIR::LEFT) vPos.x -= 800.f * fDT;
	}
	//�극��ũ ���� : �� �μ� ��
	//else if (m_eCurState == PLAYER_STATE::BREAK) {}
	//ITEM ����
	//else if (m_eCurState == PLAYER_STATE::ITEM) {}

	Transform()->SetLocalPos(vPos);

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
	m_pTarObj = _pOther;
	m_pTarScript = _pOther->GetScript();

	//�ε��� ������Ʈ �̸� �޾ƿ�
	const wstring& _str = _pOther->GetName();
	if (_str == L"PushStone" || _str == L"StoneDoor" || _str == L"BreakableStone")
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
