#include "pch.h"
#include "CBreakableSmallStoneScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CBreakableSmallStoneScript::CBreakableSmallStoneScript()
	: CScript((int)SCRIPT_TYPE::BREAKABLESMALLSTONESCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	//m_pStoneTex = CResMgr::GetInst()->FindRes<CTexture>(L"pushstone");
	//m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl");
	//m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pStoneTex.Get());
}

CBreakableSmallStoneScript::~CBreakableSmallStoneScript()
{
}

void CBreakableSmallStoneScript::awake()
{
}

void CBreakableSmallStoneScript::update()
{


}

void CBreakableSmallStoneScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CBreakableSmallStoneScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CBreakableSmallStoneScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBreakableSmallStoneScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

