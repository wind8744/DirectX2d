#include "pch.h"
#include "CBreakableStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CEventMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CAnimator2D.h>

#include <Engine/CAnimation2D.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CBreakableStoneScript::CBreakableStoneScript()
    : CScript((int)SCRIPT_TYPE::BREAKABLESTONESCRIPT)
    , m_bIsCol(false)
    //, m_pPlayerScript(nullptr)
    , m_fAtime(0.f)
    , m_bIsBreak(false)
    , m_delete(false)
    , m_ani(false)
    , m_end(false)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"breakablestone");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CBreakableStoneScript::~CBreakableStoneScript()
{
}

void CBreakableStoneScript::awake()
{
    m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"SmokeEffect");


}

void CBreakableStoneScript::update()
{
    //CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    //if (pPlayer == nullptr)
    //   return;

    //CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();
    //PLAYER_STATE _curstate = pPS->GetPlayerState();

    //�浹�����̰� �÷��̾ zŰ�� ������������ 
    //if (m_bIsCol == true && _curstate == PLAYER_STATE::BREAK && m_delete == false)
    //{
    //   m_fAtime += fDT;
    //   if (m_fAtime > 1.f) //2���� ����;
    //   {
    //      pPS->SetPlayerState(PLAYER_STATE::IDLE);
    //      pPS->SetPlayerIsOnCol(false);
    //      m_delete = true;

    //      Vec3 _Pos = Transform()->GetLocalPos();
    //      _Pos.z = 399.f;
    //      CGameObject* m_pObject = m_effect->Instantiate();
    //      m_pObject->Transform()->SetLocalPos(_Pos);

    //      tEvent _temp = {};
    //      _temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
    //      _temp.lParam = (DWORD_PTR)m_pObject;
    //      CEventMgr::GetInst()->AddEvent(_temp);
    //   }   
    //}

    //��ź�� ��� ���� ��
    if (m_bIsCol == true && m_bIsBreak == true)
    {
        m_delete = true;

        //effect
        Vec3 _Pos = Transform()->GetLocalPos();
        _Pos.z = 399.f;
        //m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"SmokeEffect");
        CGameObject* m_pObject = m_effect->Instantiate();
        m_pObject->Transform()->SetLocalPos(_Pos);

        tEvent _temp = {};
        _temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
        _temp.lParam = (DWORD_PTR)m_pObject;
        CEventMgr::GetInst()->AddEvent(_temp);

    }

    if (m_delete)
    {

        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_breakstone");
        pSound->Play(1); //0�� ������ ���ѹݺ� ,�ߺ���� �ϰ������ true (�⺻���� false, �ߺ���� ���Ƴ���)

        //���� ����
        tEvent _temp = {};
        _temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
        _temp.lParam = (DWORD_PTR)GetGameObject();
        CEventMgr::GetInst()->AddEvent(_temp);
    }
}

void CBreakableStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
    //�ε��� ������Ʈ �̸� �޾ƿ�
    if (nullptr != _pOther->GetScript(L"CBombScript"))
    {
        m_bIsCol = true;
    }


}

void CBreakableStoneScript::OnCollisionExit(CGameObject* _pOther)
{
    //�ε��� ������Ʈ �̸� �޾ƿ�
    if (nullptr != _pOther->GetScript(L"CBombScript"))
    {
        m_bIsCol = false;
    }
    //m_bIsCol = false;
}

void CBreakableStoneScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CBreakableStoneScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}