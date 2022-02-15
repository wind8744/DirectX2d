#include "pch.h"
#include "CBombScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine/CEventMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CCollider2D.h>

#include "CPlayerScript.h"
#include "CBreakableStoneScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombScript::CBombScript()
    : CScript((int)SCRIPT_TYPE::BOMBSCRIPT)
    //, m_pPlayerScript(nullptr)
    //, m_pTarScript(nullptr)
    , m_eState(BOMB_STATE::ONHEAD)
    , m_fSpeed(350.f)
    , m_eDir(DIR::DOWN)
    , m_fAtime(0.f)
    , m_vSpeed(350.f, 300.f)
    , m_fAngle(15.f)
    , m_vStartPos(0, 0, 0)
    , m_fAdjSpeed(100.f)
    , m_fPower(0.f)
    , m_IsCol(false)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"bomb");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CBombScript::~CBombScript() {}

void CBombScript::awake()
{
    //��ũ��Ʈ
    //CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
    //m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
    //m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"SmokeEffect");
    m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"BombEffect");
}

void CBombScript::update()
{
    CheckState();
    Move();
}

void CBombScript::CheckState()
{
    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

    //�÷��̾�� ������Ʈ �̺�Ʈ �ָ� ������ ���ָ� �� ���Ⱚ �Ѱ��ְ�
    PLAYER_STATE _curstate = pPS->GetPlayerState();

    //�Ӹ� ���� �־��µ�, �÷��̾ ������ ��
    if (m_eState == BOMB_STATE::ONHEAD && _curstate == PLAYER_STATE::THROW)
    {
        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_bombfuse");
        pSound->Play(1); //0�� ������ ���ѹݺ� ,�ߺ���� �ϰ������ true (�⺻���� false, �ߺ���� ���Ƴ���)

        //�Ӹ����� ������ ��ġ, ���� ���� ����
        m_fSpeed = 350.f;
        m_vSpeed = Vec2(350.f, 300.f);
        m_fAdjSpeed = 100.f;
        m_eDir = pPS->GetPlayerAnimDir();
        m_vPos = pPS->Transform()->GetLocalPos();
        m_vStartPos = m_vPos;
        m_eState = BOMB_STATE::SLIDE;
    }
    else if (m_eState == BOMB_STATE::EXPLODE)
    {

        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_bombexp");
        pSound->Play(1); //0�� ������ ���ѹݺ� ,�ߺ���� �ϰ������ true (�⺻���� false, �ߺ���� ���Ƴ���)

        //���� �浹ü�� ����ִ� ���� ���� ��
        if (m_pTarScript != nullptr)
        {
            //�ε��� target�� ������ ���� �� �ε��� ������ m_IsBreak�� true�� �ٲ۴�
            dynamic_cast<CBreakableStoneScript*>(m_pTarScript)->SetIsBreak(true);
        }

        //�μ����� ����Ʈ����
        Vec3 _Pos = Transform()->GetLocalPos();
        _Pos.z = 399.f;
        CGameObject* m_pObject = m_effect->Instantiate();
        m_pObject->Transform()->SetLocalPos(_Pos);

        tEvent _temp = {};
        _temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
        _temp.lParam = (DWORD_PTR)m_pObject;
        CEventMgr::GetInst()->AddEvent(_temp);

        //���� ����
        _temp = {};
        _temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
        _temp.lParam = (DWORD_PTR)GetGameObject();
        CEventMgr::GetInst()->AddEvent(_temp);

    }
    else if (m_eState == BOMB_STATE::EXPLODE_READY)
    {
        Collider2D()->SetvOffsetScale(Vec2(3.f, 3.f));
        m_eState = BOMB_STATE::EXPLODE;
    }

}

void CBombScript::Move()
{
    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

    if (pPS != nullptr)
    {
        Vec3 _vPlayerpos = pPS->Transform()->GetLocalPos();
        Vec3 _vPos = Transform()->GetLocalPos();

        if (m_eState == BOMB_STATE::ONHEAD)
        {
            _vPos.x = _vPlayerpos.x;
            _vPos.y = _vPlayerpos.y + 30;

            Transform()->SetLocalPos(_vPos);
        }
    }
    if (m_eState == BOMB_STATE::SLIDE)
    {
        m_fAtime += fDT;
        //�浹�� �ƴҶ���
        if (!m_IsCol)
        {
            switch (m_eDir)
            {
            case DIR::RIGHT:
                m_vPos.x -= m_vSpeed.x * cosf(m_fAngle) * fDT;
                m_vPos.y += m_vSpeed.y * sinf(m_fAngle) * fDT;
                break;
            case DIR::LEFT:
                m_vPos.x += m_vSpeed.x * cosf(m_fAngle) * fDT;
                m_vPos.y += m_vSpeed.y * sinf(m_fAngle) * fDT;
                break;

            case DIR::DOWN:
                m_vPos.y -= m_fSpeed * fDT;
                break;

            case DIR::UP:
                m_vPos.y += m_fSpeed * fDT;
                break;
            }

            if (m_eDir == DIR::RIGHT || m_eDir == DIR::LEFT)
            {
                //������
                if (m_vSpeed.x > 0)
                {
                    m_vSpeed.x -= 130 * fDT;   //0.05
                }
                else if (m_vSpeed.x < 0)
                {
                    m_vSpeed.x += 130 * fDT;
                }
                //�߷�
                m_vSpeed.y -= 800 * fDT;

                if ((UINT)m_vPos.y <= (UINT)m_vStartPos.y)
                {
                    m_vSpeed.y = m_fAdjSpeed;
                    m_fAdjSpeed -= 10;
                    if (m_fAdjSpeed < 0.f) m_fAdjSpeed = 0.f;
                }
            }
            else //���Ʒ� �������� ������ ��
            {
                //������
                if (m_fSpeed > 0)
                {
                    m_fSpeed -= 250 * fDT;
                }
                else if (m_fSpeed < 0)
                {
                    m_fSpeed += 250 * fDT;
                }
            }
            Transform()->SetLocalPos(m_vPos);
        }

        //�� �̲����� �� ���� ���·�
        if (m_fAtime > 5.f)
        {
            m_fAtime = 0.f;
            m_eState = BOMB_STATE::EXPLODE_READY;
        }
    }
}


void CBombScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (dynamic_cast<CBreakableStoneScript*>(_pOther->GetScript(L"CBreakableStoneScript")))
    {
        m_IsCol = true;
        m_pTarScript = _pOther->GetScript(L"CBreakableStoneScript");
    }

}

void CBombScript::OnCollisionOn(CGameObject* _pOther)
{
    if (dynamic_cast<CBreakableStoneScript*>(_pOther->GetScript(L"CBreakableStoneScript")))
    {
        m_pTarScript = _pOther->GetScript(L"CBreakableStoneScript");
    }
}

void CBombScript::OnCollisionExit(CGameObject* _pOther)
{
    if (dynamic_cast<CBreakableStoneScript*>(_pOther->GetScript(L"CBreakableStoneScript")))
    {
        m_IsCol = false;
        m_pTarScript = nullptr;
    }

}

void CBombScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CBombScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}