#include "pch.h"
#include "CElecBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CElecBlockScript::CElecBlockScript()
	: CScript((int)SCRIPT_TYPE::ELECBLOCKSCRIPT)
	, m_bIsCol(false)
	, m_bIsLinked(false)
	, m_pPlayerScript(nullptr)
{
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"elecblock");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "m_bIsLinked", &m_bIsLinked));
}

CElecBlockScript::~CElecBlockScript()
{
}

void CElecBlockScript::awake()
{
}

void CElecBlockScript::update()
{
	if (m_bIsLinked)
	{

	}

}

void CElecBlockScript::OnCollisionEnter(CGameObject* _pOther)
{
	//m_bIsPushed = true;

}

void CElecBlockScript::OnCollisionExit(CGameObject* _pOther)
{
	//m_bIsPushed = false;
}

void CElecBlockScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CElecBlockScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

