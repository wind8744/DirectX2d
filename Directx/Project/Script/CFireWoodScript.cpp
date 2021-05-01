#include "pch.h"
#include "CFireWoodScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CFireWoodScript::CFireWoodScript()
	: CScript((int)SCRIPT_TYPE::FIREWOODSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firewood");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CFireWoodScript::~CFireWoodScript()
{
}

void CFireWoodScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CFireWoodScript::update()
{


}

void CFireWoodScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CFireWoodScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CFireWoodScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CFireWoodScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

