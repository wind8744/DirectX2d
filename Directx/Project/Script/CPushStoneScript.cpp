#include "pch.h"
#include "CPushStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>

#include "CMissileScript.h"
#include "CObjEventScript.h"

CPushStoneScript::CPushStoneScript()
	: CScript((int)SCRIPT_TYPE::PUSHSTONESCRIPT)
	, m_bIsPushed(false)
{
	m_pStoneTex = CResMgr::GetInst()->FindRes<CTexture>(L"pushstone");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pStoneTex.Get());
}

CPushStoneScript::~CPushStoneScript()
{
}

void CPushStoneScript::awake()
{
	//m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
}

void CPushStoneScript::update()
{
	//for debug
	//int temp = 101;
	//m_pMtrl->SetData(SHADER_PARAM::INT_1, &temp);
	

}

void CPushStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	//if (m_pEventScript != nullptr)
	//{
	//	m_pEventScript->SetTrigger(true);
	//}
}

void CPushStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	//if (m_pEventScript != nullptr)
	//{
	//	m_pEventScript->SetTrigger(false);
	//}
}

void CPushStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CPushStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

