#include "pch.h"
#include "CTargetToAuto.h"

#include <Engine\CTimeMgr.h>
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>

CTargetToAuto::CTargetToAuto():CScript((int)SCRIPT_TYPE::TARGETTOAUTO)
	,m_fSpeed(0.f)
	, m_DIR(DIR::NONE)
{
}

CTargetToAuto::~CTargetToAuto()
{
}

void CTargetToAuto::awake()
{
	switch (m_DIR)
	{
	case DIR::UP:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 3.f));
	}
		break;
	case DIR::DOWN:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 1.f));
	}
		break;
	case DIR::RIGHT:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 2.f));
	}
		break;
	case DIR::LEFT:
	{

	}
		break;
	case DIR::UPRIGHT:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 2.5f));
	}
		break;
	case DIR::UPLEFT:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 3.5f));
	}
		break;
	case DIR::DOWNRIGHT:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 1.5f));
	}
		break;
	case DIR::DOWNLEFT:
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 0.5f));
	}
		break;
	}
}

void CTargetToAuto::update()
{
	if (GetGameObject()->IsDead())
		return;

	//test (타겟 : 마우스포즈)
	/*POINT a = CKeyMgr::GetInst()->GetPrevMousePos();
	a.x = a.x - 800;
	a.y = -a.y + 450;
	//test~


	Vec3 vPos = Transform()->GetLocalPos();
	Vec2 tarpos = Vec2((float)a.x, (float)a.y);

	Vec2 dir = tarpos - vPos;
	dir.Normalize();

	vPos.x += fDT * dir.x * m_fSpeed;
	vPos.y += fDT * dir.y * m_fSpeed;

	m_angle = -atan2f(dir.y, dir.x);	//접선의 기울기

	Transform()->SetLocalRot(Vec3(0, 0, 4.7f - m_angle));
	Transform()->SetLocalPos(vPos);

	

	m_fTime += fDT;

	if (m_fMaxTime < m_fTime)
	{
		m_fTime = 0;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);

	}
	*/
	Vec3 vPos = Transform()->GetLocalPos();
	switch (m_DIR)
	{
	case DIR::UP:
	{
		vPos.y += fDT * m_fSpeed;
	}
	break;
	case DIR::DOWN:
	{
		vPos.y -= fDT * m_fSpeed;
	}
	break;
	case DIR::RIGHT:
	{
		vPos.x += fDT * m_fSpeed;
	}
	break;
	case DIR::LEFT:
	{
		vPos.x -= fDT * m_fSpeed;
	}
	break;
	case DIR::UPRIGHT:
	{
		vPos.x += fDT * m_fSpeed/2;
		vPos.y += fDT * m_fSpeed/2;
	}
	break;
	case DIR::UPLEFT:
	{
		vPos.x -= fDT * m_fSpeed / 2;
		vPos.y += fDT * m_fSpeed / 2;
	}
	break;
	case DIR::DOWNRIGHT:
	{
		vPos.x += fDT * m_fSpeed / 2;
		vPos.y -= fDT * m_fSpeed / 2;
	}
	break;
	case DIR::DOWNLEFT:
	{
		vPos.x -= fDT * m_fSpeed / 2;
		vPos.y -= fDT * m_fSpeed / 2;
	}
	break;
	}
	Transform()->SetLocalPos(vPos);
}
