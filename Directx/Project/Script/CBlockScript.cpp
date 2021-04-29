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
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	//m_pRedButTex = CResMgr::GetInst()->FindRes<CTexture>(L"redbutton");
	//m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl");
	//m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pRedButTex.Get());
}

CBlockScript::~CBlockScript()
{
}

void CBlockScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CBlockScript::update()
{
	//for debug
	//int temp = 100;

	//m_pMtrl->SetData(SHADER_PARAM::INT_0, &temp);
}

void CBlockScript::OnCollisionEnter(CGameObject* _pOther)
{

}

void CBlockScript::OnCollisionExit(CGameObject* _pOther)
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

