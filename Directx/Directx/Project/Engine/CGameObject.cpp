#include "pch.h"
#include "CGameObject.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CLayer.h"

#include "CComponent.h"
#include "CMeshRender.h"
#include "CParticleSystem.h"
#include "CAnimator2D.h"
#include "CCollider2D.h"
#include "CCamera.h"
#include "CLight2D.h"

#include "CScript.h"


#include <Script\CScriptMgr.h>

CGameObject::CGameObject()
	: m_arrCom{}
	, m_iLayerIdx(-1)
	, m_pParentObj(nullptr)
	, m_bDead(false)
{
}

CGameObject::CGameObject(const CGameObject& _origin)
	: CEntity(_origin)
	, m_arrCom{}
	, m_vecChild()
	, m_pParentObj(nullptr)
	, m_iLayerIdx(-1)
	, m_bDead(false)
{
	// ������Ʈ ����
	for (int i = 0; i < (int)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != _origin.m_arrCom[i])
		{
			AddComponent(_origin.m_arrCom[i]->Clone());			
		}		
	}

	// Script ����
	for (size_t i = 0; i < _origin.m_vecScript.size(); ++i)
	{
		AddComponent(_origin.m_vecScript[i]->Clone());
	}

	// �ڽ� ������Ʈ ����
	for (size_t i = 0; i < _origin.m_vecChild.size(); ++i)
	{
		AddChild(_origin.m_vecChild[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Safe_Delete_Array(m_arrCom);
	Safe_Delete_Vector(m_vecScript);
	Safe_Delete_Vector(m_vecChild);
}

void CGameObject::awake()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->awake();
	}	

	if (!m_bDead)
	{
		for (size_t i = 0; i < m_vecScript.size(); ++i)
		{
			m_vecScript[i]->awake();
		}
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->awake();
	}
}

void CGameObject::start()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->start();
	}

	if (!m_bDead)
	{
		for (size_t i = 0; i < m_vecScript.size(); ++i)
		{
			m_vecScript[i]->start();
		}
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->start();
	}
}

void CGameObject::update()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->update();
	}

	if (!m_bDead)
	{
		for (size_t i = 0; i < m_vecScript.size(); ++i)
		{
			m_vecScript[i]->update();
		}
	}
	

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->update();
	}
}

void CGameObject::lateupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->lateupdate();
	}

	if (!m_bDead)
	{
		for (size_t i = 0; i < m_vecScript.size(); ++i)
		{
			m_vecScript[i]->lateupdate();
		}
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->lateupdate();
	}
}

void CGameObject::finalupdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finalupdate();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finalupdate();
	}

	// Register
	CLayer* pCurLayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(m_iLayerIdx);
	pCurLayer->RegisterObject(this);
}


void CGameObject::AddComponent(CComponent* _pComponent)
{
	UINT iType = (UINT)_pComponent->GetType();
		
	if (iType != (UINT)COMPONENT_TYPE::SCRIPT)
	{
		assert(!m_arrCom[iType]); // �̹� ������ ������Ʈ�� �����ϰ� �ִ� ���
		assert(!_pComponent->GetGameObject()); // ������Ʈ�� �̹� �ٸ� ������Ʈ�� ���� ���
		m_arrCom[iType] = _pComponent;
	}
	else
	{
		m_vecScript.push_back((CScript*)_pComponent);
	}
		
	_pComponent->SetGameObject(this);
}

CScript* CGameObject::GetScript(const wstring& _strName)
{
	
		for (size_t j = 0; j < m_vecScript.size(); ++j)
		{
			
			if (CScriptMgr::GetScriptName(m_vecScript[j]) == _strName)
				return m_vecScript[j];
		}
	return nullptr;
}

CGameObject* CGameObject::GetChild(const wstring& _strName)
{
	for (size_t j = 0; j < m_vecChild.size(); ++j)
	{

		if (m_vecChild[j]->GetName() == _strName)
			return m_vecChild[j];
	}
	return nullptr;
}

void CGameObject::DisconnectWithParent()
{
	// �θ� ���� ������Ʈ�� �θ����� �Լ� ȣ���� ���
	assert(m_pParentObj);

	vector<CGameObject*>::iterator iter = m_pParentObj->m_vecChild.begin();
	for (; iter != m_pParentObj->m_vecChild.end(); ++iter)
	{
		if (this == (*iter))
		{
			m_pParentObj->m_vecChild.erase(iter);
			m_pParentObj = nullptr;
			return;
		}
	}
	
	// �ڽ��� �θ� �ƴµ�, �θ�� �ڽ��� �𸣴°��
	assert(nullptr);
}

void CGameObject::RegisterAsParentObj()
{
	// �Ҽ� Layer �� ���� ���
	if (-1 == m_iLayerIdx)
	{
		return;
	}

	// �Ҽ� Layer �� �θ������Ʈ�� ���
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	int iLayerIdx = m_iLayerIdx;
	m_iLayerIdx = -1;
	pCurScene->AddObject(this, iLayerIdx);
}

void CGameObject::ReleaseAsParentObj()
{
	// �Ҽӷ��̾ ���� ���(Scene �� ���Ե����� ������)
	if (-1 == m_iLayerIdx)
		return;
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pCurLayer = pCurScene->GetLayer(m_iLayerIdx);	

	vector<CGameObject*>::iterator iter = pCurLayer->m_vecParentObj.begin();
	for (; iter != pCurLayer->m_vecParentObj.end(); ++iter)
	{
		if (this == (*iter))
		{
			pCurLayer->m_vecParentObj.erase(iter);			
			return;
		}
	}

	// �θ������Ʈ�� �Ҽ� ���̾ ����� �ȵǾ� �־��� --> ����
	assert(nullptr);
}

void CGameObject::AddChild(CGameObject* _pChildObj)
{
	// 1. �ֻ��� �θ� ������Ʈ�� �ڽ����� ������ ���
	if (nullptr == _pChildObj->GetParent())
	{
		_pChildObj->ReleaseAsParentObj();
	}

	// 2. �ٸ� �θ� �ִ� ������Ʈ�� �ڽ����� ���� ���
	else
	{
		// �̹� �ش� ������Ʈ�� �ڽ��� ���
		if (this == _pChildObj->m_pParentObj)
		{
			return;
		}

		// ���� ����
		_pChildObj->DisconnectWithParent();
	}
	
	m_vecChild.push_back(_pChildObj);
	_pChildObj->m_pParentObj = this;

	// �ڽĿ�����Ʈ�� ���̾� �Ҽ��� ������ �θ� ���󰣴�.
	if (-1 == _pChildObj->m_iLayerIdx)
	{
		_pChildObj->m_iLayerIdx = m_iLayerIdx;
	}
}

void CGameObject::SaveToScene(FILE* _pFile)
{
	CEntity::SaveToScene(_pFile);

	fwrite(&m_iLayerIdx, sizeof(int), 1, _pFile);

	UINT i = 0;
	for (; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (m_arrCom[i] != nullptr)
		{
			fwrite(&i, sizeof(UINT), 1, _pFile);
			m_arrCom[i]->SaveToScene(_pFile);
		}		
	}

	fwrite(&i, sizeof(UINT), 1, _pFile);
	
	UINT iScriptCount = (UINT)m_vecScript.size();
	fwrite(&iScriptCount, sizeof(UINT), 1, _pFile);

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		g_pScriptSave(m_vecScript[i], _pFile);
	}	

	UINT iChildCount = (UINT)m_vecChild.size();
	fwrite(&iChildCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iChildCount; ++i)
	{
		m_vecChild[i]->SaveToScene(_pFile);
	}
}

void CGameObject::LoadFromScene(FILE* _pFile)
{
	CEntity::LoadFromScene(_pFile);

	fread(&m_iLayerIdx, sizeof(int), 1, _pFile);

	UINT i = 0;	
	while (true)
	{
		fread(&i, sizeof(UINT), 1, _pFile);
		CComponent* pComponent = nullptr;
		switch ((COMPONENT_TYPE)i)
		{
		case COMPONENT_TYPE::TRANSFORM:
			pComponent = new CTransform;			
			break;
		case COMPONENT_TYPE::MESHRENDER:
			pComponent = new CMeshRender;			
			break;
		case COMPONENT_TYPE::CAMERA:
			pComponent = new CCamera;
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			pComponent = new CCollider2D;
			break;
		case COMPONENT_TYPE::COLLIDER3D:
			//pComponent = new CCollider2D;
			break;
		case COMPONENT_TYPE::ANIMATOR2D:
			pComponent = new CAnimator2D;
			break;
		case COMPONENT_TYPE::ANIMATOR3D:
			//pComponent = new CCollider2D;
			break;
		case COMPONENT_TYPE::LIGHT2D:
			pComponent = new CLight2D;
			break;
		case COMPONENT_TYPE::LIGHT3D:
			//pComponent = new CLight3D;
			break;
		case COMPONENT_TYPE::PARTICLE:
			pComponent = new CParticleSystem;
			break;			
		}

		if (i == (UINT)COMPONENT_TYPE::END)
			break;
		else
		{
			pComponent->LoadFromScene(_pFile);
			AddComponent(pComponent);
		}
		
	}

	UINT iScriptCount = 0;
	fread(&iScriptCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iScriptCount; ++i)
	{
		CScript* pScript = g_pScriptLoad(_pFile);
		AddComponent(pScript);
	}

	UINT iChildCount = 0;
	fread(&iChildCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iChildCount; ++i)
	{
		CGameObject* pChild = new CGameObject;
		pChild->LoadFromScene(_pFile);	
		int iLayerIdx = pChild->m_iLayerIdx;
		pChild->m_iLayerIdx = -1;
		AddChild(pChild);
		pChild->m_iLayerIdx = iLayerIdx;
	}
}