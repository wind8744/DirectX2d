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
	, m_fDir(1.f)
	, m_pPlayerScript(nullptr)
	, m_fSpeed(300.f)
	, m_fRange(100.f)
	, m_vStartPos(0,0)
{
	m_pTex = CResMgr::GetInst()->FindRes<CTexture>(L"barbedblock");
	m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl");
	m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex.Get());
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
	//m_vStartPos.x = Transform()->GetLocalPos().x;
	//m_vStartPos.y = Transform()->GetLocalPos().y;
	m_vStartPos = Transform()->GetLocalPos();
}

void CBarbedBlockScript::update()
{

	Vec3 _vPos = Transform()->GetLocalPos();

	_vPos.y += m_fDir * m_fSpeed * DT;

	if (abs(_vPos.y - m_vStartPos.y) > m_fRange)
	{
		if (1.f == m_fDir)
		{
			_vPos.y = m_vStartPos.y + m_fRange;
		}
		else
		{
			_vPos.y = m_vStartPos.y - m_fRange;
		}

		m_fDir *= -1.f;
	}

	Transform()->SetLocalPos(_vPos);
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

