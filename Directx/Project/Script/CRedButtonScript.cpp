#include "pch.h"
#include "CRedButtonScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>

#include "CMissileScript.h"

CRedButtonScript::CRedButtonScript()
	: CScript((int)SCRIPT_TYPE::REDBUTTONSCRIPT)
	, m_bIsPushed(false)
{
	//m_pRedButTex = CResMgr::GetInst()->FindRes<CTexture>(L"REDBUTTON");
	//if (nullptr == m_pRedButTex)
	//	m_pRedButTex = CResMgr::GetInst()->Load<CTexture>(L"REDBUTTON", L"texture\\object\\8.jpg");
	//AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "Int Data", &m_iData));
	//AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "float Data", &m_fData));
}

CRedButtonScript::~CRedButtonScript()
{
}

void CRedButtonScript::awake()
{
}

void CRedButtonScript::update()
{
	int a = 1;
}

void CRedButtonScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;
}

void CRedButtonScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CRedButtonScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CRedButtonScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

