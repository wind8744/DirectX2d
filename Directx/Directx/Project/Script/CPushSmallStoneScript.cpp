#include "pch.h"
#include "CPushSmallStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>

CPushSmallStoneScript::CPushSmallStoneScript()
	: CScript((int)SCRIPT_TYPE::PUSHSMALLSTONESCRIPT)
	, m_bIsPushed(false)
{

}

CPushSmallStoneScript::~CPushSmallStoneScript()
{
}

void CPushSmallStoneScript::awake()
{
}

void CPushSmallStoneScript::update()
{
	int a = 1;
}

void CPushSmallStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;
}

void CPushSmallStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CPushSmallStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CPushSmallStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

