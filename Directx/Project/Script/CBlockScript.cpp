#include "pch.h"
#include "CBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"

CBlockScript::CBlockScript()
	: CScript((int)SCRIPT_TYPE::BLOCKSCRIPT)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"block");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BlockMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CBlockScript::~CBlockScript()
{
}

void CBlockScript::awake()
{
}

void CBlockScript::update()
{
}

void CBlockScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBlockScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

