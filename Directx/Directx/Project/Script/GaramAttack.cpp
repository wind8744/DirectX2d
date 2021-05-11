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
void CPlayerScript::GaramAttack()
{
	if (m_eCurState == PLAYER_STATE::SKILL)
	{
		CGameObject* pObject = nullptr;
		Vec3 Pos = Transform()->GetLocalPos();

		if (m_ISkillNum == 1)
		{
			if (m_CoolTime <= 0)
			{
				pObject = m_Skill1->Instantiate();
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
				pObject->Animator2D()->PlayAnimation(L"Skill", false);
				m_CoolTime = 8.f;

				CPlayerPosSetScript* PlayerPosSetScript = (CPlayerPosSetScript*)pObject->GetScript(L"CPlayerPosSetScript");
				PlayerPosSetScript->SetTarget(GetGameObject());
				tEvent even = {};
				even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				even.lParam = (DWORD_PTR)pObject;
				//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
				even.wParam = (DWORD_PTR)30;
				CEventMgr::GetInst()->AddEvent(even);


				//DOWN
				//pObject = m_Skill2->Instantiate();
				//Pos = Transform()->GetLocalPos();
				//Pos.y -= 45.f;
				//Pos.x -= 10.f;

				//pObject->Transform()->SetLocalPos(Pos);

				//CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
				//hook->SetDir(DIR::DOWN);
				//pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, -20.f));
				//pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

				//even = {};
				//even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				//even.lParam = (DWORD_PTR)pObject;
				////even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
				//even.wParam = (DWORD_PTR)30;
				//CEventMgr::GetInst()->AddEvent(even);


			}
		}
	}

	if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
	{

		CGameObject* pObject = nullptr;
		Vec3 Pos = Transform()->GetLocalPos();
		CGameObject* pObject2 = m_Attack2->Instantiate();
		pObject = m_Attack1->Instantiate();
		switch (m_AnimDir)
		{
		case DIR::UP:
		{
			Pos.y += 20.f;
			pObject->Transform()->SetLocalPos(Pos);

			pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
			pObject->Animator2D()->PlayAnimation(L"Attack_UP1", false);
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");

			
			Pos = Transform()->GetLocalPos();
			Pos.y += 20.f;
			pObject2->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::UP);

			

		}
		break;
		case DIR::DOWN:
		{
			Pos.y -= 20.f;
			pObject->Transform()->SetLocalPos(Pos);
			
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
			pObject->Animator2D()->PlayAnimation(L"Attack_DOWN1", false);
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			

			
			Pos = Transform()->GetLocalPos();
			Pos.y -= 20.f;
			pObject2->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::DOWN);

	


		}
		break;
		case DIR::RIGHT:
		{
			Pos.x += 20.f;
			pObject->Transform()->SetLocalPos(Pos);
			
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
			pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT1", false);
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			

		
			Pos = Transform()->GetLocalPos();
			Pos.x += 20.f;
			pObject2->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::RIGHT);

		


		}
		break;
		case DIR::LEFT:
		{
			Pos.x -= 20.f;
			pObject->Transform()->SetLocalPos(Pos);
			
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
			pObject->Animator2D()->PlayAnimation(L"Attack_LEFT1", false);
			CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
			

			
			Pos = Transform()->GetLocalPos();
			Pos.x -= 20.f;
			pObject2->Transform()->SetLocalPos(Pos);
			CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
			hook->SetDir(DIR::LEFT);


		}
		break;
		}
		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)pObject;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)30;
		CEventMgr::GetInst()->AddEvent(even);

		even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)pObject2;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)30;
		CEventMgr::GetInst()->AddEvent(even);
		m_PreCombo = m_CurrentCombo;

	}
}
