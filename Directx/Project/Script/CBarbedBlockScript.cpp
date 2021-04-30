#include "pch.h"
#include "CBarbedBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"

CBarbedBlockScript::CBarbedBlockScript()
	: CScript((int)SCRIPT_TYPE::BARBEDBLOCKSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	//m_pRedButTex = CResMgr::GetInst()->FindRes<CTexture>(L"barbedblock");
	//m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl");
	//m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pRedButTex.Get());
}

CBarbedBlockScript::~CBarbedBlockScript()
{
}

void CBarbedBlockScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CBarbedBlockScript::update()
{
	//for debug
	//int temp = 100;

	//m_pMtrl->SetData(SHADER_PARAM::INT_0, &temp);
}

void CBarbedBlockScript::OnCollisionEnter(CGameObject* _pOther)
{

}

void CBarbedBlockScript::OnCollisionExit(CGameObject* _pOther)
{

}

void CBarbedBlockScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBarbedBlockScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

