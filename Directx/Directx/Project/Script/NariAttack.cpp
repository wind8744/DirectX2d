#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CTransform.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CEventMgr.h>

#include "CBreakableStoneScript.h"
#include "CPushStoneScript.h"
#include "CBreakableSmallStoneScript.h"
#include "CFireBowlScript.h"
#include "CBombFlowerScript.h"
#include "CMissileScript.h"
#include "CPlayerPosSetScript.h"
#include "CTargetToAuto.h"

void CPlayerScript::NariAttack()
{
	if (m_eCurState == PLAYER_STATE::SKILL)
	{
		CGameObject* pObject = nullptr;
		Vec3 Pos = Transform()->GetLocalPos();

		if (m_CoolTime <= 0)
		{
			m_CoolTime = 8.f;

			//UP
			pObject = m_Skill1->Instantiate();

			Pos.y += 45.f;
			pObject->Transform()->SetLocalPos(Pos);

			CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::UP);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, 20.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			tEvent even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//DOWN
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.y -= 45.f;
			Pos.x -= 10.f;

			pObject->Transform()->SetLocalPos(Pos);

			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::DOWN);
			pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, -20.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//RIGHT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.x += 45.f;
			Pos.y -= 10.f;
			pObject->Transform()->SetLocalPos(Pos);
			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::RIGHT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(20.f, 10.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));


			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);


			//LEFT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.x -= 45.f;

			pObject->Transform()->SetLocalPos(Pos);
			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::LEFT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, -10.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//UPLEFT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.y += 30.f;
			Pos.x -= 30.f;
			pObject->Transform()->SetLocalPos(Pos);

			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::UPLEFT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, 10.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));


			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//UPRIGHT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.y += 30.f;
			Pos.x += 30.f;
			pObject->Transform()->SetLocalPos(Pos);

			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::UPRIGHT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, 30.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//DOWNLEFT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.y -= 30.f;
			Pos.x -= 30.f;
			pObject->Transform()->SetLocalPos(Pos);

			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::DOWNLEFT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, -30.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);

			//DOWNRIGHT
			pObject = m_Skill1->Instantiate();
			Pos = Transform()->GetLocalPos();
			Pos.y -= 30.f;
			Pos.x += 30.f;
			pObject->Transform()->SetLocalPos(Pos);

			hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::DOWNRIGHT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(25.f, -20.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

			even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);
		}
	}
	if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
	{
		CGameObject* pObject = nullptr;
		Vec3 Pos = Transform()->GetLocalPos();

		srand((unsigned int)time(NULL));
		int n = rand() % 10;
		if (n < 3)
			pObject = m_Attack2->Instantiate();
		else
			pObject = m_Attack1->Instantiate();
		switch (m_AnimDir)
		{
		case DIR::UP:
		{
			Pos.y += 45.f;
			pObject->Transform()->SetLocalPos(Pos);

			CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::UP);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, 20.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			Missile->SetTime(2.f);
		}
		break;
		case DIR::DOWN:
		{
			Pos.y -= 45.f;
			pObject->Transform()->SetLocalPos(Pos);

			CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::DOWN);
			pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, -20.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			Missile->SetTime(2.f);
		}
		break;
		case DIR::RIGHT:
		{
			Pos.x += 45.f;
			pObject->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::RIGHT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(20.f, 10.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			Missile->SetTime(2.f);
		}
		break;
		case DIR::LEFT:
		{
			Pos.x -= 45.f;
			Pos.y += 10.f;
			pObject->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::LEFT);
			pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, -10.f));
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			Missile->SetTime(2.f);
		}
		break;
		}
		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)pObject;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)30;
		CEventMgr::GetInst()->AddEvent(even);

		m_PreCombo = m_CurrentCombo;
	}
}