#include "pch.h"
#include "CEndBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CEndBlockScript::CEndBlockScript()
	: CScript((int)SCRIPT_TYPE::ENDBLOCKSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"endblock");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"EndBlockMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

}

CEndBlockScript::~CEndBlockScript()
{
}

void CEndBlockScript::awake()
{
}

void CEndBlockScript::update()
{


}

void CEndBlockScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CEndBlockScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CEndBlockScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CEndBlockScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

