#include "pch.h"
#include "CDropMissileScript.h"
#include "CInvaderScript.h"
#include "CPlayerPosSetScript.h"
#include "CPlayerScript.h"

#include <Engine\CTimeMgr.h>
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>

#include <Engine/CSceneMgr.h>

CDropMissileScript::CDropMissileScript()
	:CScript((int)SCRIPT_TYPE::DROPMISSILESCRIPT)
	, m_speed(100.f)
	, m_atime(0.f)
	, m_maxtime(3.f)
	, m_start(false)
	, m_offsety(300.f)
{
}

CDropMissileScript::~CDropMissileScript()
{
}

void CDropMissileScript::awake()
{
	m_startpos = Transform()->GetLocalPos();
}

void CDropMissileScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	if (!m_start)
	{
		m_startposy = m_startpos.y;
		m_startpos.y += m_offsety;
		m_start = true;
	}
	//Vec3 vPos = m_startpos;//Transform()->GetLocalPos();

	m_atime += fDT;

	if (m_atime > m_maxtime)
	{
		m_atime = 0.f;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}

	//������ ����Ʈ�� �÷��̾� y���� ������
	if (m_startpos.y <= m_startposy + 50.f)
	{
		m_atime = 0.f;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);

	}


	////�װ� �ƴϸ� ��� ������
	m_startpos.y -= fDT * m_speed;

	//�߷�
	//m_vSpeed.y -= 800 * fDT;

	Transform()->SetLocalPos(m_startpos);
}
