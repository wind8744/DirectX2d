#include "pch.h"
#include "CRedButtonScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>

#include "CObjEventScript.h"

CRedButtonScript::CRedButtonScript()
	: CScript((int)SCRIPT_TYPE::REDBUTTONSCRIPT)
	, m_pEventScript(nullptr)
	
{
	//m_pRedButTex = CResMgr::GetInst()->FindRes<CTexture>(L"REDBUTTON");
	//if (nullptr == m_pRedButTex)
	//	m_pRedButTex = CResMgr::GetInst()->Load<CTexture>(L"REDBUTTON", L"texture\\object\\8.jpg");
	//AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "Int Data", &m_iData));
	//AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "float Data", &m_fData));

	Ptr<CTexture> pTex  = CResMgr::GetInst()->FindRes<CTexture>(L"redbutton");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}


CRedButtonScript::~CRedButtonScript()
{
}

void CRedButtonScript::awake()
{
	m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));

}

void CRedButtonScript::update()
{
	
}

void CRedButtonScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (m_pEventScript != nullptr)
	{
		m_pEventScript->SetTrigger(true);
	}
}

void CRedButtonScript::OnCollisionExit(CGameObject* _pOther)
{
	if (m_pEventScript != nullptr) 
	{
		m_pEventScript->SetTrigger(false);
	}
}

void CRedButtonScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CRedButtonScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

