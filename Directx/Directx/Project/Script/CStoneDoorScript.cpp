#include "pch.h"
#include "CStoneDoorScript.h"
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include "CRedButtonScript.h"
#include "CObjEventScript.h"

CStoneDoorScript::CStoneDoorScript()
	: CScript((int)SCRIPT_TYPE::STONEDOORSCRIPT)
{
	//�׽�Ʈ ������ redbutton ��ũ��Ʈ �޾ƿ�
	

	Ptr<CTexture> pTex  = CResMgr::GetInst()->FindRes<CTexture>(L"stonedoor");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	pTex = CResMgr::GetInst()->FindRes<CTexture>(L"stonedoor2");
	pMtrl->SetData(SHADER_PARAM::TEX_1, pTex.Get());
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

	//���� ���� ��ư ��ũ��Ʈ���� bool�� �޾ƿ�
	if (m_pEventScript != nullptr)
	{
		if (m_pEventScript->GetTrigger())
		{
			int a = 1;
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a);
			// ++ �浹ü ����
			GetGameObject()->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.f));
			
		}
		else
		{
			int a = 0;
			GetGameObject()->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a);
		}
	}
	
	
	//�������� �ƴϸ� 1�� ��� ����	
	// //���̴��� �� ����
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
