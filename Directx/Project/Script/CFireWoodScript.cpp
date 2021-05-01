#include "pch.h"
#include "CFireWoodScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>

#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CFireWoodScript::CFireWoodScript()
	: CScript((int)SCRIPT_TYPE::FIREWOODSCRIPT)
	, m_IsOnCol(false)
	, m_bHaveItem(false)
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

	if (m_IsOnCol)
	{
		//int a = 100;
		//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a); //쉐이더에 값 전달
		const vector<CGameObject*>& _child = this->GetObj()->GetChild();
		_child[0]->Animator2D()->PlayAnimation(L"BURN", true);
	}

}	

void CFireWoodScript::OnCollisionEnter(CGameObject* _pOther)
{
	//부딪힌 오브젝트 이름 받아옴
	const wstring& _str = _pOther->GetName();
	if (_str == L"FireBowl") m_IsOnCol = true;
	if (_str == L"Player")
	{
		UINT _itemnum = m_pPlayerScript->GetPlayerItemNum();
		if(_itemnum == 2) m_IsOnCol = true;
	}
}

void CFireWoodScript::OnCollisionExit(CGameObject* _pOther)
{
	//m_IsOnCol = false;
}

void CFireWoodScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CFireWoodScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

