#include "pch.h"
#include "CFireBowlScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CFireBowlScript::CFireBowlScript()
    : CScript((int)SCRIPT_TYPE::FIREBOWLSCRIPT)
    //, m_pPlayerScript(nullptr)
    , m_bCol(false)
    , m_fAtime(0.f)
    , m_vSpeed(350.f, 300.f)
    , m_fSpeed(350.f)
    , m_fAngle(15.f)
    , m_eState(FIRE_STATE::NONE)
    , m_vPos(0, 0, 400)
    , m_eDir(DIR::DOWN)
    , m_vStartPos(0, 0, 0)
    , m_fAdjSpeed(100.f)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firebowl");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());


}

CFireBowlScript::~CFireBowlScript()
{
}

void CFireBowlScript::awake()
{
    //��ũ��Ʈ
    //CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
    //m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CFireBowlScript::update()
{
    CheckState();
    Move();
}

void CFireBowlScript::CheckState()
{
    //if (m_eState == FIRE_STATE::COL)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;

        CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();
        PLAYER_STATE _curstate = pPS->GetPlayerState();
        PLAYER_ITEM _playeritem = pPS->GetPlayerItem();

        // �浹�����̰� �÷��̾ Item�����϶� , �Ӹ� ����
        if (m_eState == FIRE_STATE::COL && _curstate == PLAYER_STATE::ITEM && _playeritem == PLAYER_ITEM::FIREBOWL)   m_eState = FIRE_STATE::HEAD;

        // �Ӹ� ���� �־��µ�, �÷��̾ ������ ��
        else if (m_eState == FIRE_STATE::HEAD && _curstate == PLAYER_STATE::THROW)
        {
            // �Ӹ����� ������ ��ġ, ���� ���� ����
            m_fSpeed = 350.f;
            m_vSpeed = Vec2(350.f, 300.f);
            m_fAdjSpeed = 100.f;
            m_eDir = pPS->GetPlayerAnimDir();
            m_vPos = pPS->Transform()->GetLocalPos();
            m_vPos.z = 399.f; //�÷��̾� ������ ȭ��
            m_vStartPos = m_vPos;
            m_eState = FIRE_STATE::SLIDE;
        }
    }
}
void CFireBowlScript::Move()
{
    //if (m_pPlayerScript != nullptr)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;

        CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

        Vec3 _vPlayerpos = pPS->Transform()->GetLocalPos();
        Vec3 _vPos = Transform()->GetLocalPos();

        if (m_eState == FIRE_STATE::HEAD)
        {
            _vPos.x = _vPlayerpos.x;
            _vPos.y = _vPlayerpos.y + 30;
            _vPos.z = 399.f;
            Transform()->SetLocalPos(_vPos);
        }
        else if (m_eState == FIRE_STATE::SLIDE)
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

            //�� �̲����� �� ���� ���·�
            m_fAtime += fDT;
            if (m_fAtime > 3.f)
            {
                m_eState = FIRE_STATE::NONE;
                m_fAtime = 0.f;
            }


        }
    }
}


void CFireBowlScript::OnCollisionEnter(CGameObject* _pOther)
{
    //�ε��� ������Ʈ �̸� �޾ƿ�
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_eState = FIRE_STATE::COL;
    }

}

void CFireBowlScript::OnCollisionExit(CGameObject* _pOther)
{
    //�ε��� ������Ʈ �̸� �޾ƿ�
    if (nullptr != _pOther->GetScript(L"CPlayerScript") && (m_eState == FIRE_STATE::COL))
    {
        m_eState = FIRE_STATE::NONE;
    }
    //if (m_eState == FIRE_STATE::COL) m_eState = FIRE_STATE::NONE;
}

void CFireBowlScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CFireBowlScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}