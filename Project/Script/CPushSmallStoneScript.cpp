#include "pch.h"
#include "CPushSmallStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine/CEventMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CTimeMgr.h>
#include <Engine/CCollider2D.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"


CPushSmallStoneScript::CPushSmallStoneScript()
    : CScript((int)SCRIPT_TYPE::PUSHSMALLSTONESCRIPT)
    , m_bIsPushed(false)
    , m_bAni(false)
    , m_pushdir(DIR::NONE)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"pushsmallstone");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PushSmallStoneMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CPushSmallStoneScript::~CPushSmallStoneScript()
{
}

void CPushSmallStoneScript::awake()
{
    Transform()->SetLocalPosZ(399.f); //플레이어 앞으로
    m_Child = GetGameObject()->GetChild(L"PushEffect");
}

void CPushSmallStoneScript::update()
{
    Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_pushstone");
    Vec3 vPos = Transform()->GetLocalPos();

    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();
    PLAYER_STATE _curstate = pPS->GetPlayerState();
    DIR _curdir = pPS->GetPlayerDir();

    if (m_bIsPushed == true && _curstate == PLAYER_STATE::PUSH)
    {

        pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

        if (_curdir == DIR::RIGHT && _curdir == m_pushdir && m_eColliderDir.b_RIGHT == false)
        {
            vPos.x += 150.f * fDT;
            if (!m_bAni)
            {
                m_Child->Animator2D()->PlayAnimation(L"SMOKE", true);
                m_Child->Transform()->SetLocalPos(Vec3(-0.3f, -0.4f, 0.f));
                m_bAni = true;
            }

        }
        if (_curdir == DIR::LEFT && _curdir == m_pushdir && m_eColliderDir.b_LEFT == false)
        {
            vPos.x -= 150.f * fDT;
            if (!m_bAni)
            {
                m_Child->Animator2D()->PlayAnimation(L"SMOKE", true);
                m_Child->Transform()->SetLocalPos(Vec3(0.3f, -0.4f, 0.f));
                m_bAni = true;
            }
        }
        if (_curdir == DIR::DOWN && _curdir == m_pushdir && m_eColliderDir.b_DOWN == false)
        {
            vPos.y -= 150.f * fDT;
            if (!m_bAni)
            {
                m_Child->Animator2D()->PlayAnimation(L"SMOKE", true);
                m_Child->Transform()->SetLocalPos(Vec3(0.f, -0.5f, 0.f));
                m_bAni = true;
            }
        }
        if (_curdir == DIR::UP && _curdir == m_pushdir && m_eColliderDir.b_UP == false)
        {
            vPos.y += 150.f * fDT;
        }

    }
    if (KEY_AWAY(KEY_TYPE::KEY_Z) || KEY_NONE(KEY_TYPE::KEY_Z))
    {
        pSound->Stop();
        m_Child->Animator2D()->PlayAnimation(L"NONE", false);
        m_bAni = false;
    }

    Transform()->SetLocalPos(vPos);

}

void CPushSmallStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CObjTileCol"))
    {
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

    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = true;
        Vec3 _PlayerPos = _pOther->Transform()->GetLocalPos();
        Vec3 _pos = Transform()->GetLocalPos();
        Vec2 _scale = Collider2D()->GetScale();

        if ((_PlayerPos.x < _pos.x + _scale.x / 2) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::RIGHT;
        }
        else if ((_pos.x + _scale.x / 2 < _PlayerPos.x) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::LEFT;
        }
        else if (_pos.y + _scale.y / 2 < _PlayerPos.y && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::DOWN;
        }
        else if (_PlayerPos.y < _pos.y - _scale.y / 2 && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::UP;
        }
        else m_pushdir = DIR::NONE;
    }

}

void CPushSmallStoneScript::OnCollisionOn(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = true;

        Vec3 _PlayerPos = _pOther->Transform()->GetLocalPos();
        Vec3 _pos = Transform()->GetLocalPos();
        Vec2 _scale = Collider2D()->GetScale();

        if ((_PlayerPos.x < _pos.x + _scale.x / 2) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::RIGHT;
        }
        else if ((_pos.x + _scale.x / 2 < _PlayerPos.x) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::LEFT;
        }
        else if (_pos.y + _scale.y / 2 < _PlayerPos.y && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::DOWN;
        }
        else if (_PlayerPos.y < _pos.y - _scale.y / 2 && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::UP;
        }
        else m_pushdir = DIR::NONE;
    }
}

void CPushSmallStoneScript::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CObjTileCol"))
    {
        m_eColliderDir.b_RIGHT = false;

        m_eColliderDir.b_LEFT = false;

        m_eColliderDir.b_UP = false;

        m_eColliderDir.b_DOWN = false;
    }

    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = false;
    }
}

void CPushSmallStoneScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CPushSmallStoneScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}