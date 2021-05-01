#include "pch.h"
#include "CBombScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombScript::CBombScript()
	: CScript((int)SCRIPT_TYPE::BOMBSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"bomb");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CBombScript::~CBombScript()
{
}

void CBombScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CBombScript::update()
{


}

void CBombScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CBombScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CBombScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBombScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

