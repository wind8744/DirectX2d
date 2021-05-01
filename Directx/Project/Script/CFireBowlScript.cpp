#include "pch.h"
#include "CFireBowlScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CFireBowlScript::CFireBowlScript()
	: CScript((int)SCRIPT_TYPE::FIREBOWLSCRIPT)
	, m_pPlayerScript(nullptr)
	, m_pScript(nullptr)
	, m_fAtime(0.f)
	, m_fSpeed(350.f)
	, m_eState(FIRE_STATE::NONE)
	, m_vPos(0,0,400)
	,m_eDir(DIR::DOWN)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firebowl");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CFireBowlScript::~CFireBowlScript()
{
}

void CFireBowlScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//�÷��̾� ��ũ��Ʈ
	m_pScript = vecParent[2]->GetScript();
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CFireBowlScript::update()
{
	CheckState();
	Move();
}

void CFireBowlScript::CheckState()
{
	PLAYER_STATE _curstate = m_pPlayerScript->GetPlayerState();
	PLAYER_STATE _prevstate = m_pPlayerScript->GetPlayerPrevState();
	
	//�浹�����̰� �÷��̾ Item�����϶� , �Ӹ� ����
	if ((m_eState == FIRE_STATE::COL) && _curstate == PLAYER_STATE::ITEM)	m_eState = FIRE_STATE::HEAD;
	
	//�Ӹ� ���� �־��µ�, �÷��̾ ������ ��
	else if (m_eState == FIRE_STATE::HEAD && _curstate == PLAYER_STATE::IDLE)
	{
		//�Ӹ����� ������ ��ġ, ���� ���� ����
		m_fSpeed = 350.f;
		m_eDir = m_pPlayerScript->GetPlayerDir();
		m_vPos = m_pScript->Transform()->GetLocalPos();
		m_eState = FIRE_STATE::SLIDE;
	}
	
}
void CFireBowlScript::Move()
{
	Vec3 _vPlayerpos = m_pScript->Transform()->GetLocalPos();
	Vec3 _vPos = Transform()->GetLocalPos();

	if (m_eState == FIRE_STATE::HEAD)
	{
		_vPos.x = _vPlayerpos.x;
		_vPos.y = _vPlayerpos.y + 30;

		Transform()->SetLocalPos(_vPos);
	}
	else if (m_eState == FIRE_STATE::SLIDE)
	{
		switch (m_eDir)
		{
		case DIR::RIGHT:
			m_vPos.x += m_fSpeed*fDT;
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

		//������ ( �ӷ��� �ݴ��������)
		if (m_fSpeed > 0)
		{
			m_fSpeed -= 1.5;   //0.05
		}
		else if (m_fSpeed < 0)
		{
			m_fSpeed += 1.5;
		}


		m_fAtime += fDT;
		if (m_fAtime > 3.f) 
		{
			//�� �̲����� �� ���� ���·�
			m_eState = FIRE_STATE::NONE;
			m_fAtime = 0.f;
		}
		Transform()->SetLocalPos(m_vPos);
		
	}

}


void CFireBowlScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_eState = FIRE_STATE::COL;
}

void CFireBowlScript::OnCollisionExit(CGameObject* _pOther)
{
	if(m_eState == FIRE_STATE::COL) m_eState = FIRE_STATE::NONE;
}

void CFireBowlScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CFireBowlScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}
