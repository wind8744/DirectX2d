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


CPlayerScript::CPlayerScript()
	: CScript((int)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_fPlayerSpeed(150.f)
	, m_iHP(100)
	, m_eCurState(PLAYER_STATE::IDLE)            //�÷��̾��� ���� ����
	, m_ePrevState(PLAYER_STATE::IDLE)           //���� ����
	, m_eCurDir(DIR::DOWN)              //���� ����
	, m_ePreDir(DIR::DOWN)
	, m_AnimDir(DIR::DOWN) //���� ����
	, m_PreAinmDir(DIR::DOWN)
	, m_bIsOnCol(false)
	, m_fAtime(0.f)
	, m_eItem(PLAYER_ITEM::NONE)
	, m_vJumpSpeed(550.f, 500.f)
	, m_fJumpSpeed(500.f)
	, m_fAngle(15.f)
	, m_vStartPos(0.f, 0.f, 0.f)
	, m_Character(Character::MARINA)
	, m_Attack1(nullptr)
	, m_Attack2(nullptr)
	, m_Attack3(nullptr)
	, m_Attack4(nullptr)
	, m_Skill1(nullptr)
	, m_Skill2(nullptr)
	, m_LinkSkill(nullptr)
	, m_IsAttacking(false)
	, m_CanNextCombo(false)
	, m_PreCombo(0)
	, m_CurrentCombo(0)
	, m_MaxCombo(4)
	, m_IsComboInputOn(false)
	, m_fMaxtime(0.5f)
	, m_ISkillNum(0)
	, m_CoolTime(0.f)
	, m_CoolTime2(0.f)
{
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "HP", &m_iHP));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "Speed", &m_fPlayerSpeed));

	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "m_vStartPos.y", &m_vStartPos.y));  //test

	m_eColliderDir.b_DOWN = false;
	m_eColliderDir.b_LEFT = false;
	m_eColliderDir.b_RIGHT = false;
	m_eColliderDir.b_UP = false;
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::awake()
{
	switch (m_Character)
	{
	case Character::NARI:
	{
		m_MaxCombo = 1;
		m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack1");
		m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack2");
		m_Skill1 = CResMgr::GetInst()->FindRes<CPrefab>(L"NariSkill1");
	}
		break;
	case Character::MARINA:
	{
		m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"MarinaAttack");
		m_Skill1 = CResMgr::GetInst()->FindRes<CPrefab>(L"MarinaSkill1");
		m_Skill2 = CResMgr::GetInst()->FindRes<CPrefab>(L"MarinaSkill2");
		m_MaxCombo = 4;
	}
		break;
	case Character::EVA:
	{
		m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttack1");
		m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttack2");
		//m_Attack3 = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttack3");
		//m_Skill = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaSkill1");
		m_MaxCombo = 3;
	}
		break;
	case Character::GARAM:
	{
		m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"GaramAttack1");
		m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"GaramAttack2");
		m_Skill1 = CResMgr::GetInst()->FindRes<CPrefab>(L"GaramSkill1"); 
		//m_Skill2 = CResMgr::GetInst()->FindRes<CPrefab>(L"GaramSkill2");
		m_MaxCombo = 1;
	}
		break;
	}
	
}

void CPlayerScript::update()
{

	//Ű �Է� ����
	CheckState();

	//���� ���¿� �´� �ִϸ��̼� ���
	PlayAnimation();

	
	//�ٲ� ���¿��� ������
	PlayerAction();

	
	
	
	switch (m_Character)
	{
	case Character::NARI:
		NariAttack();
		break;
	case Character::MARINA:
		MarinaAttack();
		break;
	case Character::GARAM:
		GaramAttack();
		break;
	case Character::EVA:
		EvaAttack();
		break;
	}

	

	if (m_CoolTime > 0) //���� ������ ����
	{
		m_CoolTime -= fDT;
	}
	if (m_CoolTime2 > 0) //���� ������ ����
	{
		m_CoolTime2 -= fDT;
	}
}


void CPlayerScript::CheckState()
{
	// Ű �Է¿� ���� �̵�
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vRot = Transform()->GetLocalRot();

	//���� ���¸� ���� ���·� ������ ��
	m_ePrevState = m_eCurState;
	m_ePreDir = m_eCurDir;
	m_PreAinmDir = m_AnimDir;



	if (Animator2D()->GetCurAnim()->IsFinish() && m_eCurState == PLAYER_STATE::ATTACK)
	{
		if (m_CurrentCombo == m_MaxCombo)
		{
			AttackEndComboState();
		}
		else if (m_IsComboInputOn)
		{
			AttackStartComboState();
		}
		else if (!m_IsComboInputOn)
		{
			m_fAtime += fDT;
			if (m_fMaxtime < m_fAtime)
			{
				AttackEndComboState();
				m_fAtime = 0.f;
			}
		}

	}
	Vec3 a = Vec3(0.f, 0.f, 0.f);
	
	if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN || 
		m_eCurState == PLAYER_STATE::PUSH || m_eCurState == PLAYER_STATE::ITEM || m_eCurState == PLAYER_STATE::ITEMIDLE ||
		m_eCurState == PLAYER_STATE::ATTACK 
		)
	{
		if (KEY_HOLD(KEY_TYPE::KEY_LEFT))
		{
			if (KEY_HOLD(KEY_TYPE::SPACE) &&( m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;	
			}
			else if(m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::LEFT;
			if (m_eCurState == PLAYER_STATE::ATTACK)
			{
				if(m_CurrentCombo != m_PreCombo)
					m_AnimDir = DIR::LEFT;
			}
			else
			{
				m_AnimDir = DIR::LEFT;
			}
			
		}
		if (KEY_HOLD(KEY_TYPE::KEY_RIGHT))
		{
			
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::RIGHT;
			if (m_eCurState == PLAYER_STATE::ATTACK)
			{
				if (m_CurrentCombo != m_PreCombo)
					m_AnimDir = DIR::RIGHT;
			}
			else
			{
				m_AnimDir = DIR::RIGHT;
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_UP))
		{
			
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::UP;
			if (m_eCurState == PLAYER_STATE::ATTACK)
			{
				if (m_CurrentCombo != m_PreCombo)
					m_AnimDir = DIR::UP;
			}
			else
			{
				m_AnimDir = DIR::UP;
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_DOWN))
		{
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
				m_eCurDir = DIR::DOWN;
				if (m_eCurState == PLAYER_STATE::ATTACK)
				{
					if (m_CurrentCombo != m_PreCombo)
						m_AnimDir = DIR::DOWN;
				}
				else
				{
					m_AnimDir = DIR::DOWN;
				}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_DOWN) && KEY_HOLD(KEY_TYPE::KEY_LEFT))
		{
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::DOWNLEFT;
			if (m_AnimDir == DIR::DOWNRIGHT || m_AnimDir == DIR::UPLEFT || m_AnimDir == DIR::UPRIGHT)
			{
				if (m_eCurState == PLAYER_STATE::ATTACK)
				{
					if (m_CurrentCombo != m_PreCombo)
						m_AnimDir = DIR::DOWN;
				}
				else
				{
					m_AnimDir = DIR::DOWN;
				}
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_DOWN) && KEY_HOLD(KEY_TYPE::KEY_RIGHT))
		{
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::DOWNRIGHT;
			if (m_AnimDir == DIR::DOWNLEFT || m_AnimDir == DIR::UPLEFT || m_AnimDir == DIR::UPRIGHT)
			{
				if (m_eCurState == PLAYER_STATE::ATTACK)
				{
					if (m_CurrentCombo != m_PreCombo)
						m_AnimDir = DIR::DOWN;
				}
				else
				{
					m_AnimDir = DIR::DOWN;
				}
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_UP) && KEY_HOLD(KEY_TYPE::KEY_LEFT))
		{
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if (m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::UPLEFT;
			if (m_AnimDir == DIR::DOWNRIGHT || m_AnimDir == DIR::DOWNLEFT || m_AnimDir == DIR::UPRIGHT)
			{
				if (m_eCurState == PLAYER_STATE::ATTACK)
				{
					if (m_CurrentCombo != m_PreCombo)
						m_AnimDir = DIR::UP;
				}
				else
				{
					m_AnimDir = DIR::UP;
				}
			}
		}
		if (KEY_HOLD(KEY_TYPE::KEY_UP) && KEY_HOLD(KEY_TYPE::KEY_RIGHT))
		{
			
			if (KEY_HOLD(KEY_TYPE::SPACE) && (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE || m_eCurState == PLAYER_STATE::RUN))
			{
				m_eCurState = PLAYER_STATE::RUN;
			}
			else if (m_eCurState == PLAYER_STATE::IDLE || m_eCurState == PLAYER_STATE::MOVE)
			{
				m_eCurState = PLAYER_STATE::MOVE;
			}
			else if(m_eCurState == PLAYER_STATE::ITEMIDLE || m_eCurState == PLAYER_STATE::ITEM)
			{
				m_eCurState = PLAYER_STATE::ITEM;
			}
			m_eCurDir = DIR::UPRIGHT;
			if (m_AnimDir == DIR::DOWNRIGHT || m_AnimDir == DIR::UPLEFT || m_AnimDir == DIR::DOWNLEFT)
			{
				if (m_eCurState == PLAYER_STATE::ATTACK)
				{
					if (m_CurrentCombo != m_PreCombo)
						m_AnimDir = DIR::UP;
				}
				else
				{
					m_AnimDir = DIR::UP;
				}
			}
		}

		//HOLD
		if (KEY_TAP(KEY_TYPE::KEY_A))
		{
		
			Attacking();
		}
		if (KEY_TAP(KEY_TYPE::KEY_S)  && m_CoolTime <=0)
		{
			AttackEndComboState();
			m_ISkillNum = 1;
			m_eCurState = PLAYER_STATE::SKILL;
		}
		if (KEY_TAP(KEY_TYPE::KEY_D) && m_CoolTime2 <= 0)
		{
			if (m_Skill2.Get() != nullptr)
			{
				AttackEndComboState();
				m_ISkillNum = 2;
				m_eCurState = PLAYER_STATE::SKILL;
			}
		}
		if (KEY_NONE(KEY_TYPE::KEY_DOWN) && KEY_NONE(KEY_TYPE::KEY_UP) && KEY_NONE(KEY_TYPE::KEY_LEFT) && KEY_NONE(KEY_TYPE::KEY_RIGHT) && (m_eCurState != PLAYER_STATE::ATTACK && m_eCurState != PLAYER_STATE::SKILL))
		{
			if (m_eItem == PLAYER_ITEM::NONE)
				m_eCurState = PLAYER_STATE::IDLE;
			else if (m_eItem != PLAYER_ITEM::NONE)
				m_eCurState = PLAYER_STATE::ITEMIDLE;
		}
		


		if (KEY_TAP(KEY_TYPE::KEY_Z) && m_eItem != PLAYER_ITEM::NONE ) //������ ������
		{
			
			m_eItem = PLAYER_ITEM::NONE;
			m_eCurState = PLAYER_STATE::THROW;
		}
	}
	//�����̵� ���� : ���ǵ� ���� ��
	else if (m_eCurState == PLAYER_STATE::SLIDE && m_bIsOnCol == false)
	{
		if (m_eCurDir == DIR::DOWN) vPos.y -= 800.f * fDT;
		else if (m_eCurDir == DIR::UP) vPos.y += 800.f * fDT;
		else if (m_eCurDir == DIR::RIGHT) vPos.x += 800.f * fDT;
		else if (m_eCurDir == DIR::LEFT) vPos.x -= 800.f * fDT;
	}
	//���� ����  : ���� ���� ��
	else if (m_eCurState == PLAYER_STATE::JUMP && m_bIsOnCol == false)
	{
		Collider2D()->SetvOffsetScale(Vec2(0.f, 0.f));
		// * �÷��̾� �浹ü ���� �߰� *
		if (m_eCurDir == DIR::DOWN) vPos.y -= m_fJumpSpeed * fDT;
		
		else if (m_eCurDir == DIR::UP) vPos.y += m_fJumpSpeed * fDT;
		
		else if (m_eCurDir == DIR::RIGHT)
		{
			vPos.x -= m_vJumpSpeed.x * cosf(m_fAngle) * fDT;
			vPos.y += m_vJumpSpeed.y * sinf(m_fAngle) * fDT;
			// ������ �� y�� �������� land���·�
			if ((UINT)vPos.y <= (UINT)m_vStartPos.y)
			{
				int a = 1;
				m_eCurState = PLAYER_STATE::LAND;
			}
		}
		else if (m_eCurDir <= DIR::LEFT)
		{
			vPos.x += m_vJumpSpeed.x * cosf(m_fAngle) * fDT;
			vPos.y += m_vJumpSpeed.y * sinf(m_fAngle) * fDT;

			if ((UINT)vPos.y <= (UINT)m_vStartPos.y)
			{
				m_eCurState = PLAYER_STATE::LAND;
			}
		}
		// �¿� ����, �߷�, ������
		if (m_eCurDir == DIR::RIGHT || m_eCurDir == DIR::LEFT)
		{
			//������
			if (m_vJumpSpeed.x > 0) m_vJumpSpeed.x -= 130 * fDT;   //0.05
			else if (m_vJumpSpeed.x < 0) m_vJumpSpeed.x += 130 * fDT;

			//�߷�
			m_vJumpSpeed.y -= 700 * fDT;
		}
		// ���Ʒ� ���� , �����¸�
		if (m_eCurDir == DIR::UP || m_eCurDir == DIR::DOWN)
		{
			if (m_fJumpSpeed > 0) m_fJumpSpeed -= 250 * fDT;
			else if (m_fJumpSpeed < 0) m_fJumpSpeed += 250 * fDT;
			
			// �ӵ��� 0�� �Ǹ� LAND(����)����
			if ((UINT)m_fJumpSpeed <= 0 && m_eCurDir == DIR::UP) m_eCurState = PLAYER_STATE::LAND;
			else if ((UINT)m_fJumpSpeed >= 0 && m_eCurDir == DIR::DOWN) m_eCurState = PLAYER_STATE::LAND;
		}
	}
	// ���� ���� ( ���� �� ���� ���� )
	else if (m_eCurState == PLAYER_STATE::LAND)
	{   // �ʱ�ȭ
		m_vJumpSpeed.x = 0.f;
		m_vJumpSpeed.y = 0.f;
		m_fJumpSpeed = 0.f;
		Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));
		// * �÷��̾� �浹ü ���� �߰� *
		AttackEndComboState();
		// �÷��̾ idle���·� ����
		if (m_eItem == PLAYER_ITEM::NONE)
			m_eCurState = PLAYER_STATE::IDLE;
		else
			m_eCurState = PLAYER_STATE::ITEM;
		
	}
	
	
	if (Animator2D()->GetCurAnim()->IsFinish() && m_eCurState == PLAYER_STATE::THROW)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	if (Animator2D()->GetCurAnim()->IsFinish() && m_eCurState == PLAYER_STATE::SKILL)
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
	/*if (m_AnimDir == DIR::LEFT)
	{
		Transform()->SetLocalRot(Vec3(180.f, 0.f, 0.f));
	}
	else
	{
		Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	}*/

	Transform()->SetLocalPos(vPos);


}


void CPlayerScript::PlayAnimation()
{
	if (m_ePrevState != m_eCurState || m_PreAinmDir != m_AnimDir)
	{
		if (PLAYER_STATE::MOVE == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"WALK_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"WALK_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"WALK_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"WALK_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::IDLE == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"STOP_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"STOP_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"STOP_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"STOP_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::RUN == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"RUN_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"RUN_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"RUN_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"RUN_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::ITEM == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"WALKBOMB_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"WALKBOMB_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"WALKBOMB_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"WALKBOMB_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::ITEMIDLE == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"STOPBOMB_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"STOPBOMB_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"STOPBOMB_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"STOPBOMB_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::PUSH == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"PUSH_UP", true);
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"PUSH_DOWN", true);
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"PUSH_LEFT", true);
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"PUSH_RIGHT", true);
				break;
			}
		}
		else if (PLAYER_STATE::BREAK == m_eCurState)
		{
			switch (m_AnimDir)
			{

			}
		}
		else if (PLAYER_STATE::THROW == m_eCurState)
		{
			switch (m_AnimDir)
			{
			case DIR::UP:
			{
				
				Animator2D()->PlayAnimation(L"THROWBOMB_UP", false);
			}
			break;
			case DIR::DOWN:
			{
			
				Animator2D()->PlayAnimation(L"THROWBOMB_DOWN", false);
			}
			break;
			case DIR::LEFT:
			{
			
				Animator2D()->PlayAnimation(L"THROWBOMB_LEFT", false);
			}
			break;
			case DIR::RIGHT:
			{
			
				Animator2D()->PlayAnimation(L"THROWBOMB_RIGHT", false);
			}
			break;
			}
		}
		else if (PLAYER_STATE::ATTACK == m_eCurState  && m_CurrentCombo != 0)
		{
		switch (m_AnimDir)
		{
			case DIR::UP:
			{
				const wstring& name = L"ATTACK_UP" + to_wstring(m_CurrentCombo);
				Animator2D()->PlayAnimation(name, false);
			}
			break;
			case DIR::DOWN:
			{
				const wstring& name1 = L"ATTACK_DOWN" + to_wstring(m_CurrentCombo);
				Animator2D()->PlayAnimation(name1, false);
			}
			break;
			case DIR::LEFT:
			{
				const wstring& name2 = L"ATTACK_LEFT" + to_wstring(m_CurrentCombo);
				Animator2D()->PlayAnimation(name2, false);
				
			}
			break;
			case DIR::RIGHT:
			{
				const wstring& name3 = L"ATTACK_RIGHT" + to_wstring(m_CurrentCombo);
				Animator2D()->PlayAnimation(name3, false);
				
			}
			break;
			}
		
		}
		else if (PLAYER_STATE::SKILL == m_eCurState)
		{
		switch (m_AnimDir)
		{
		case DIR::UP:
		{
			if (m_ISkillNum == 1)
			{
				switch (m_Character)
				{
				case Character::NARI:
					Animator2D()->PlayAnimation(L"SKILL_UP", false);
					break;
				case Character::MARINA:
					Animator2D()->PlayAnimation(L"SKILL_RIGHT", false);
					break;
				case Character::EVA:
					break;
				case Character::GARAM:
					Animator2D()->PlayAnimation(L"SKILL_UP", false);
					break;
				default:
					break;
				}
					
			}
			else if(m_ISkillNum ==2)
				Animator2D()->PlayAnimation(L"SKILL2_UP", false);
		}
		break;
		case DIR::DOWN:
		{
			if (m_ISkillNum == 1)
			{
				switch (m_Character)
				{
				case Character::NARI:
					Animator2D()->PlayAnimation(L"SKILL_DOWN", false);
					break;
				case Character::MARINA:
					Animator2D()->PlayAnimation(L"SKILL_RIGHT", false);
					break;
				case Character::EVA:
					break;
				case Character::GARAM:
					Animator2D()->PlayAnimation(L"SKILL_DOWN", false);
					break;
				default:
					break;
				}
				
			}
			if (m_ISkillNum == 2)
				Animator2D()->PlayAnimation(L"SKILL2_DOWN", false);
		}
		break;
		case DIR::LEFT:
		{
			if (m_ISkillNum == 1)
			{
				switch (m_Character)
				{
				case Character::NARI:
					Animator2D()->PlayAnimation(L"SKILL_LEFT", false);
					break;
				case Character::MARINA:
					Animator2D()->PlayAnimation(L"SKILL_LEFT", false);
					break;
				case Character::EVA:
					break;
				case Character::GARAM:
					Animator2D()->PlayAnimation(L"SKILL_LEFT", false);
					break;
				default:
					break;
				}
				
			}
			if (m_ISkillNum == 2)
				Animator2D()->PlayAnimation(L"SKILL2_LEFT", false);

		}
		break;
		case DIR::RIGHT:
		{
			if (m_ISkillNum == 1)
			{
				switch (m_Character)
				{
				case Character::NARI:
					Animator2D()->PlayAnimation(L"SKILL_RIGHT", false);
					break;
				case Character::MARINA:
					Animator2D()->PlayAnimation(L"SKILL_RIGHT", false);
					break;
				case Character::EVA:
					break;
				case Character::GARAM:
					Animator2D()->PlayAnimation(L"SKILL_RIGHT", false);
					break;
				default:
					break;
				}
			}
			if (m_ISkillNum == 2)
				Animator2D()->PlayAnimation(L"SKILL2_RIGHT", false);

		}
		break;
		}

		}

	}
	if(PLAYER_STATE::ATTACK == m_eCurState && m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0)
	{
		switch (m_AnimDir)
		{
		case DIR::UP:
		{
			const wstring& name = L"ATTACK_UP" + to_wstring(m_CurrentCombo);
			Animator2D()->PlayAnimation(name, false);
		}
			break;
		case DIR::DOWN:
		{
			const wstring& name1 = L"ATTACK_DOWN" + to_wstring(m_CurrentCombo);
			Animator2D()->PlayAnimation(name1, false);
		}
			break;
		case DIR::LEFT:
		{
			const wstring& name2 = L"ATTACK_LEFT" + to_wstring(m_CurrentCombo);
			Animator2D()->PlayAnimation(name2, false);
		}
			break;
		case DIR::RIGHT:
		{
			const wstring& name3 = L"ATTACK_RIGHT" + to_wstring(m_CurrentCombo);
			Animator2D()->PlayAnimation(name3, false);
		}
			break;
		}
	
	}


}

void CPlayerScript::PlayerAction()
{
	
	if (PLAYER_STATE::MOVE == m_eCurState)
		m_fPlayerSpeed = 200.f;
	else if (PLAYER_STATE::RUN == m_eCurState)
		m_fPlayerSpeed = 300.f;
	else if (PLAYER_STATE::ITEM == m_eCurState)
		m_fPlayerSpeed = 200.f;
	else if (PLAYER_STATE::PUSH == m_eCurState)
		m_fPlayerSpeed = 150.f;
	else if (PLAYER_STATE::ATTACK == m_eCurState)
		m_fPlayerSpeed = 150.f;
	else
		return;



	if (KEY_NONE(KEY_TYPE::KEY_DOWN) && KEY_NONE(KEY_TYPE::KEY_UP) && KEY_NONE(KEY_TYPE::KEY_LEFT) && KEY_NONE(KEY_TYPE::KEY_RIGHT) && m_eCurState == PLAYER_STATE::ATTACK)
		return;

	Vec3 vPos = Transform()->GetLocalPos();

	
	


	switch (m_eCurDir)
	{
	case DIR::UP:
	{
		if (m_eColliderDir.b_UP)
		{

		}
		else
		vPos.y += fDT * m_fPlayerSpeed;

	}
		break;
	case DIR::DOWN:
	{
		if (m_eColliderDir.b_DOWN )
		{

		}
		else
		vPos.y -= fDT * m_fPlayerSpeed;
	}
		break;
	case DIR::LEFT:
	{
		if (m_eColliderDir.b_LEFT )
		{

		}
		else
		vPos.x -= fDT * m_fPlayerSpeed;
	}
		break;
	case DIR::RIGHT:
	{ 
		if (m_eColliderDir.b_RIGHT)
		{

		}
		else
		vPos.x += fDT * m_fPlayerSpeed;
	}
		break;
	case DIR::DOWNLEFT:
	{   
		if (m_eColliderDir.b_LEFT && m_eColliderDir.b_DOWN)
		{

		}
		else if (m_eColliderDir.b_LEFT)
		{
			vPos.y -= fDT * m_fPlayerSpeed / 1.4f;
		}
		else if (m_eColliderDir.b_DOWN )
		{
			vPos.x -= fDT * m_fPlayerSpeed /1.4f;
		}
		else
		{
			vPos.y -= fDT * m_fPlayerSpeed / 1.4f;
			vPos.x -= fDT * m_fPlayerSpeed / 1.4f;
		}
	}
		break;
	case DIR::DOWNRIGHT:
	{	
		if (m_eColliderDir.b_RIGHT && m_eColliderDir.b_DOWN)
		{

		}
		else if (m_eColliderDir.b_RIGHT)
		{
			vPos.y -= fDT * m_fPlayerSpeed / 1.4f;
		}
		else if (m_eColliderDir.b_DOWN )
		{
			vPos.x += fDT * m_fPlayerSpeed / 1.4f;
		}
		else
		{
			vPos.y -= fDT * m_fPlayerSpeed / 1.4f;
			vPos.x += fDT * m_fPlayerSpeed / 1.4f;
		}
	}
		break;
	case DIR::UPLEFT:
	{	
		if (m_eColliderDir.b_LEFT && m_eColliderDir.b_UP)
		{

		}
		else if (m_eColliderDir.b_LEFT )
		{
			vPos.y += fDT * m_fPlayerSpeed / 1.4f;
		}
		else if (m_eColliderDir.b_UP)
		{
			vPos.x -= fDT * m_fPlayerSpeed / 1.4f;
		}
		else
		{
			vPos.y += fDT * m_fPlayerSpeed / 1.4f;
			vPos.x -= fDT * m_fPlayerSpeed / 1.4f;
		}
	}
		break;
	case DIR::UPRIGHT:
	{	
		if (m_eColliderDir.b_RIGHT && m_eColliderDir.b_UP)
		{
			
		}
		else if (m_eColliderDir.b_UP)
		{
			vPos.x += fDT * m_fPlayerSpeed / 1.4f;
		}
		else if (m_eColliderDir.b_RIGHT)
		{
			vPos.y += fDT * m_fPlayerSpeed / 1.4f;
		}
		else
		{
			vPos.y += fDT * m_fPlayerSpeed / 1.4f;
			vPos.x += fDT * m_fPlayerSpeed / 1.4f;
		}
	}
		break;

	}



	Transform()->SetLocalPos(vPos);
}


void CPlayerScript::Attacking()
{
	if (m_IsAttacking)
	{
		float n = Animator2D()->GetCurAnim()->GetAnimFrmRatio();
		if (m_CanNextCombo && 0.2 < n)
		{
			m_IsComboInputOn = true;
		}
	}
	else
	{
		AttackStartComboState();
		m_eCurState = PLAYER_STATE::ATTACK;
		m_IsAttacking = true;
	}
}

void CPlayerScript::AttackStartComboState()
{
	
	m_CanNextCombo = true;
	m_IsComboInputOn = false;
	if (m_CurrentCombo+1> m_MaxCombo)
	{
		m_CurrentCombo = m_MaxCombo;
	}
	else if (m_CurrentCombo + 1 >=1 && m_CurrentCombo + 1<=m_MaxCombo)
	{
		m_CurrentCombo = m_CurrentCombo + 1;
	}
	else if (m_CurrentCombo + 1 < 1)
	{
		m_CurrentCombo = 1;
	}
	
}

void CPlayerScript::AttackEndComboState()
{
	m_IsAttacking = false;
	m_IsComboInputOn = false;
	m_CanNextCombo = false;
	m_CurrentCombo = 0;
	m_PreCombo = 0;
	m_eCurState = PLAYER_STATE::IDLE;
}


void CPlayerScript::OnCollisionEnter(CGameObject* _pOther)
{

	if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CStoneDoorScript") || _pOther->GetScript(L"CBreakableStoneScript") || _pOther->GetScript(L"CTileCollsion"))
	{
		
		m_bIsOnCol = true;
		float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
		float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
		float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
		float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
		if (cleft < cdown && cleft < cright && cleft < cup)
		{
			m_eColliderDir.b_LEFT = true;
		}
		else if (cdown < cleft && cdown < cright && cdown < cup)
		{
			m_eColliderDir.b_DOWN = true;
		}
		else if (cright < cdown && cright < cleft && cright < cup)
		{
			m_eColliderDir.b_RIGHT = true;
		}
		else if (cup < cdown && cup < cright && cup < cleft)
		{
			m_eColliderDir.b_UP = true;
		}
		

	
	}
	if (_pOther->GetScript(L"CJumpUpScript"))
	{
		m_vStartPos = Transform()->GetLocalPos();
	}
}



void CPlayerScript::OnCollision(CGameObject* _pOther)
{
	if (KEY_HOLD(KEY_TYPE::KEY_Z))//|| KEY_TAP(KEY_TYPE::KEY_Z))
	{
		//�浹�� ��ü ��ũ��Ʈ �̳Ѱ� �޾ƿ�
		
		if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CPushSmallStoneScript"))	m_eCurState = PLAYER_STATE::PUSH; //�м� �ִ� ���� ��
		if (_pOther->GetScript(L"CBreakableStoneScript") )
		{
				CScript* _script = dynamic_cast<CBreakableStoneScript*>(_pOther->GetScript(L"CBreakableStoneScript"));
			if ((dynamic_cast<CBreakableStoneScript*>(_script))->GetIsBreak() == false) m_eCurState = PLAYER_STATE::BREAK; //�ν� �� �ִ� ���� ����
		}
			if (_pOther->GetScript(L"CBreakableSmallStoneScript"))
		{
				//CScript* _script = dynamic_cast<CBreakableSmallStoneScript*>(_pOther->GetScript(L"CBreakableSmallStoneScript"));
				//if ((dynamic_cast<CBreakableSmallStoneScript*>(_script))->GetIsBreak() == false) m_eCurState = PLAYER_STATE::BREAK; //�ν� �� �ִ� ���� ����
		}
		if (m_eItem == PLAYER_ITEM::NONE)
		{
			if (_pOther->GetScript(L"CBombFlowerScript")) { 
				if (dynamic_cast<CBombFlowerScript*>(_pOther->GetScript(L"CBombFlowerScript"))->GetState() == FLOWER_STATE::COL)
				m_eItem = PLAYER_ITEM::BOMB; m_eCurState = PLAYER_STATE::ITEM;
			}
			else if (_pOther->GetScript(L"CFireBowlScript")) { 
				if (dynamic_cast<CFireBowlScript*>(_pOther->GetScript(L"CFireBowlScript"))->GetState() == FIRE_STATE::COL)
				m_eItem = PLAYER_ITEM::FIREBOWL; m_eCurState = PLAYER_STATE::ITEM; 
			}
		}
	}


	
	if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CStoneDoorScript") || _pOther->GetScript(L"CBreakableStoneScript") || _pOther->GetScript(L"CTileCollsion"))
	{
		
		m_bIsOnCol = true;
		float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x); 
		float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
		float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
		float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
		
		if (cleft < cdown && cleft < cright && cleft < cup)
		{
			m_eColliderDir.b_LEFT = true;
	
		}
		else if (cdown < cleft && cdown < cright && cdown < cup)
		{
			m_eColliderDir.b_DOWN = true;

		}
		else if (cright < cdown && cright < cleft && cright < cup)
		{
			m_eColliderDir.b_RIGHT = true;
			
		}
		else if (cup < cdown && cup < cright && cup < cleft)
		{
			m_eColliderDir.b_UP = true;
			
		}
	
	}
	
}

void CPlayerScript::OnCollisionExit(CGameObject* _pOther)
{

	if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CStoneDoorScript") || _pOther->GetScript(L"CBreakableStoneScript") || _pOther->GetScript(L"CTileCollsion"))
	{
		m_eColliderDir.b_RIGHT = false;
	
		m_eColliderDir.b_LEFT = false;
		
		m_eColliderDir.b_UP = false;
		
		m_eColliderDir.b_DOWN = false;
		if (m_eCurState == PLAYER_STATE::PUSH)
			m_eCurState = PLAYER_STATE::IDLE;
	}
	m_bIsOnCol = false;
}


void CPlayerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CPlayerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}
