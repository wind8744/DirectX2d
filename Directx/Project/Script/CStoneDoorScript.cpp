#include "pch.h"
#include "CStoneDoorScript.h"
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CRedButtonScript.h"

CStoneDoorScript::CStoneDoorScript()
	: CScript((int)SCRIPT_TYPE::STONEDOORSCRIPT)
{
	//테스트 씬에서 redbutton 스크립트 받아옴
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene(); 
	CLayer* pLayer = pCurScene->GetLayer(2);
	vector<CGameObject*> vecParent = pLayer->GetParentObj();
	m_pTarScript = vecParent[0]->GetScript();
}

CStoneDoorScript::~CStoneDoorScript()
{
}

void CStoneDoorScript::awake()
{
}

void CStoneDoorScript::update()
{
	/* temp */

	//현재 씬의 버튼 스크립트에서 bool값 받아옴
	CRedButtonScript* temp;
	temp = dynamic_cast<CRedButtonScript*>(m_pTarScript);
	bool _IsPushed = temp->GetIsPushed();

	int a = 1;

	//버튼이 눌렸으면
	if(_IsPushed == true)
	{
		a = 100;
		MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a); //쉐이더에 값 전달 
		//100 이면 쉐이더에서 빨간색으로
	}
	
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a); //쉐이더에 값 전달
	//눌린것이 아니면 1을 계속 전달
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
