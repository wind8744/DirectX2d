#include "pch.h"
#include "CStoneDoorScript.h"
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CRedButtonScript.h"
#include "CObjEventScript.h"

CStoneDoorScript::CStoneDoorScript()
	: CScript((int)SCRIPT_TYPE::STONEDOORSCRIPT)
{
	//테스트 씬에서 redbutton 스크립트 받아옴
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene(); 
	CLayer* pLayer = pCurScene->GetLayer(3);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();
	m_pTarScript = vecParent[0]->GetScript();

	m_pStoneDoorTex = CResMgr::GetInst()->FindRes<CTexture>(L"stonedoor");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pStoneDoorTex.Get());
}

CStoneDoorScript::~CStoneDoorScript()
{
}

void CStoneDoorScript::awake()
{
	m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
}

void CStoneDoorScript::update()
{
	/* temp */
	int a = 22;

	//현재 씬의 버튼 스크립트에서 bool값 받아옴
	if (m_pEventScript != nullptr)
	{
		if (m_pEventScript->GetTrigger())
		{
			a = 100;
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a); //쉐이더에 값 전달 
			//100 이면 쉐이더에서 빨간색으로
		}
	}

	//눌린것이 아니면 1을 계속 전달	
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a); //쉐이더에 값 전달
}

void CStoneDoorScript::OnCollisionEnter(CGameObject* _pOther)
{

}

void CStoneDoorScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);


}

void CStoneDoorScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);


}
