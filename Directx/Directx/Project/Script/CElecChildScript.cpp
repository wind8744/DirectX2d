#include "pch.h"
#include "CElecChildScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"
#include "CElecBlockScript.h"

CElecChildScript::CElecChildScript()
	: CScript((int)SCRIPT_TYPE::ELECCHILDSCRIPT)
	, m_bIsCol(false)
	, m_pPlayerScript(nullptr)
	, m_pTarScript(nullptr)
	, m_fMinDir(10000.f)
{
	//Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"electower");
	//Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ElecTowerMtrl");
	//pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CElecChildScript::~CElecChildScript() {}

void CElecChildScript::awake() {}

void CElecChildScript::update()
{
	Vec3 _pos = Transform()->GetLocalPos();

	//벡터안에 있는 블록과의 거리 검사
	for (int i = 0; i < m_vecScript.size(); ++i)
	{
		Vec3 _childpos = m_vecScript[i]->Transform()->GetLocalPos();
		float _dir = sqrt(pow((_pos.x - _childpos.x), 2) + pow((_pos.y - _childpos.y), 2));
		
		//저장된 최소 거리보다 같거나 더 작은 거리의 블록을 발견하면
		if (m_fMinDir >= _dir)
		{
			//연결
			dynamic_cast<CElecBlockScript*>(m_vecScript[i])->SetIsLinked(true);
			m_fMinDir = _dir;
			m_pTarScript = m_vecScript[i];
			
		}

		//나머지는 연결 해제
		else dynamic_cast<CElecBlockScript*>(m_vecScript[i])->SetIsLinked(false); 
	}

}

void CElecChildScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (dynamic_cast<CElecBlockScript*>(_pOther->GetScript(L"CElecBlockScript")))
	{
		//m_vecElec.push_back(dynamic_cast<CElecBlockScript*>(_pOther->GetScript(L"CElecBlockScript")));
		m_vecScript.push_back(_pOther->GetScript(L"CElecBlockScript"));
	}
	m_bIsCol = true;
}

void CElecChildScript::OnCollisionOn(CGameObject* _pOther)
{


}

void CElecChildScript::OnCollisionExit(CGameObject* _pOther)
{
	UINT _id = _pOther->GetID();
	for (int i = 0; i < m_vecScript.size(); ++i)
	{
		if (_id == m_vecScript[i]->GetID())
		{
			m_vecScript.erase(m_vecScript.begin() + i);
		}
	}
	m_bIsCol = false;

}

void CElecChildScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CElecChildScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}

