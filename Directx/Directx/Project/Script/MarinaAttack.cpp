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

void CPlayerScript::MarinaAttack()
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
			}

		}
		else if (m_ISkillNum == 2)
		{
			if (m_CoolTime2 <= 0)
			{
				float n = Animator2D()->GetCurAnim()->GetAnimFrmRatio();
				if (0.5 < n)
				{
					pObject = m_Skill2->Instantiate();

					switch (m_AnimDir)
					{
					case DIR::UP:
					{
						Pos.y += 45.f;
						pObject->Transform()->SetLocalPos(Pos);


						CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
						CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
						hook->SetDir(DIR::UP);
					}
					break;
					case DIR::DOWN:
					{
						Pos.y -= 45.f;
						pObject->Transform()->SetLocalPos(Pos);
						CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
						CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
						hook->SetDir(DIR::DOWN);

					}
					break;
					case DIR::RIGHT:
					{
						Pos.x += 45.f;
						pObject->Transform()->SetLocalPos(Pos);

						CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
						CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
						hook->SetDir(DIR::RIGHT);

					}
					break;
					case DIR::LEFT:
					{
						Pos.x -= 45.f;
						pObject->Transform()->SetLocalPos(Pos);


						CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
						hook->SetDir(DIR::LEFT);

					}
					break;
					}
					CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
					Missile->SetTime(0.5f);
					tEvent even = {};
					even.eEvent = EVENT_TYPE::CREATE_OBJECT;
					even.lParam = (DWORD_PTR)pObject;
					//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
					even.wParam = (DWORD_PTR)30;
					CEventMgr::GetInst()->AddEvent(even);
					m_CoolTime2 = 8.f;
				}

			}
		}

	}

	if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
	{
		CGameObject* pObject = nullptr;
		Vec3 Pos = Transform()->GetLocalPos();
		if (m_CurrentCombo == 1)
		{
			pObject = m_Attack1->Instantiate();
			switch (m_AnimDir)
			{
			case DIR::UP:
			{
				Pos.y += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_UP1", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.66f);
			}
			break;
			case DIR::DOWN:
			{
				Pos.y -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_DOWN1", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.66f);
			}
			break;
			case DIR::RIGHT:
			{
				Pos.x += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT1", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.66f);
			}
			break;
			case DIR::LEFT:
			{
				Pos.x -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_LEFT1", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.66f);
			}
			break;
			}
		}
		else if (m_CurrentCombo == 2)
		{

			
			pObject = m_Attack1->Instantiate();

			switch (m_AnimDir)
			{
			case DIR::UP:
			{
				Pos.y += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_UP2", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);

			}
			break;
			case DIR::DOWN:
			{
				Pos.y -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_DOWN2", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::RIGHT:
			{
				Pos.x += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT2", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);

			}
			break;
			case DIR::LEFT:
			{
				Pos.x -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_LEFT2", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			}

		}
		else if (m_CurrentCombo == 3)
		{
			pObject = m_Attack1->Instantiate();

			switch (m_AnimDir)
			{
			case DIR::UP:
			{
				Pos.y += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_UP3", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::DOWN:
			{
				Pos.y -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 4.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_DOWN3", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::RIGHT:
			{
				Pos.x += 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT3", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::LEFT:
			{
				Pos.x -= 45.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
				pObject->Animator2D()->PlayAnimation(L"Attack_LEFT3", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			}

		}
		else if (m_CurrentCombo == 4)
		{
			pObject = m_Attack1->Instantiate();

			switch (m_AnimDir)
			{
			case DIR::UP:
			{
				//Pos.x += 64.f;
				Pos.y += 64.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 2.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.75f));
				pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, 16.f));
				pObject->Animator2D()->PlayAnimation(L"Attack_UP4", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::DOWN:
			{
				//Pos.x += 64.f;
				Pos.y -= 64.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(96.f * 4.f);
				pObject->Transform()->SetLocalScaleY(128.f * 2.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.75f));
				pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, -16.f));
				pObject->Animator2D()->PlayAnimation(L"Attack_DOWN4", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::RIGHT:
			{
				Pos.x += 64.f;
				Pos.y -= 10.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 2.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.75f, 0.2f));
				pObject->Collider2D()->SetvOffsetPos(Vec2(16.f, 10.f));
				pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT4", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			case DIR::LEFT:
			{
				Pos.x -= 64.f;
				Pos.y -= 10.f;
				pObject->Transform()->SetLocalPos(Pos);
				pObject->Transform()->SetLocalScaleX(128.f * 2.f);
				pObject->Transform()->SetLocalScaleY(96.f * 4.f);
				pObject->Collider2D()->SetvOffsetScale(Vec2(0.75f, 0.2f));
				pObject->Collider2D()->SetvOffsetPos(Vec2(-16.f, 10.f));
				pObject->Animator2D()->PlayAnimation(L"Attack_LEFT4", false);
				CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
				Missile->SetTime(0.3f);
			}
			break;
			}

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