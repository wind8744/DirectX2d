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
	//�׽�Ʈ ������ redbutton ��ũ��Ʈ �޾ƿ�
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
	int a = 1;
	//���� ���� ��ư ��ũ��Ʈ���� bool�� �޾ƿ�
	if (GetGameObject()->GetScript(L"CObjEventScript") != nullptr)
	{
		if ((dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript")))->GetTrigger())
		{
			a = 100;
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a); //���̴��� �� ���� 
			//100 �̸� ���̴����� ����������
		}
	}

		
		MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a); //���̴��� �� ����
	
	//�������� �ƴϸ� 1�� ��� ����
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
