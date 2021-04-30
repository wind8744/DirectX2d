#include "pch.h"
#include "CBombFlowerScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombFlowerScript::CBombFlowerScript()
	: CScript((int)SCRIPT_TYPE::BOMBFLOWERSCRIPT)
	, m_bIsPushed(false)
	, m_pPlayerScript(nullptr)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"bombflower");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
}

CBombFlowerScript::~CBombFlowerScript()
{
}

void CBombFlowerScript::awake()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->GetLayer(0);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();

	//플레이어 스크립트
	m_pPlayerScript = dynamic_cast<CPlayerScript*>(vecParent[2]->GetScript());
}

void CBombFlowerScript::update()
{


}

void CBombFlowerScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsPushed = true;

}

void CBombFlowerScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsPushed = false;
}

void CBombFlowerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CBombFlowerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

