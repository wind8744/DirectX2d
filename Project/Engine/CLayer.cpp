#include "pch.h"
#include "CLayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CGameObject.h"



CLayer::CLayer(int _iLayerIdx)
	: m_iLayerIndex(_iLayerIdx)
{
}

CLayer::~CLayer()
{
	Safe_Delete_Vector(m_vecParentObj);
}

void CLayer::awake()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->awake();
	}
}

void CLayer::start()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->start();
	}
}

void CLayer::update()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->update();
	}
}

void CLayer::lateupdate()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->lateupdate();
	}
}

void CLayer::finalupdate()
{
	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->finalupdate();
	}
}

void CLayer::AddObject(CGameObject* _pObject, bool _bMoveChild)
{
	// Object �� �ٸ� Layer �Ҽ��̾��� ���, ���� ������ �Ѵ�.
	int iLayerIdx = _pObject->GetLayerIndex();

	// �̹� �ش� ���̾� �Ҽ� ������Ʈ�̴�
	if (m_iLayerIndex == _pObject->GetLayerIndex())
	{
		return;
	}
	// �Ҽ� Layer �� �����ϰ�, ���� Layer �� �ƴѰ��
	else if (-1 != iLayerIdx && m_iLayerIndex != iLayerIdx)
	{
		// ���� Layer ���� ���� ����
		_pObject->ReleaseAsParentObj();
	}

	m_vecParentObj.push_back(_pObject);
	_pObject->SetLayerIndex(m_iLayerIndex);
	if (SCENE_STATE::PAUSE == CSceneMgr::GetInst()->GetCurScene()->GetState() || SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetCurScene()->GetState())
		_pObject->awake();

	// Layer �� �ԷµǴ� ������Ʈ�� �ڽĿ�����Ʈ�� �ִ� ���
	list<CGameObject*> queue(_pObject->m_vecChild.begin(), _pObject->m_vecChild.end());

	while (!queue.empty())
	{
		CGameObject* pChild = queue.front();
		queue.pop_front();

		// �ڽĵ��� �θ��� ���̾ ���󰡴� ��� or �ڽ� ������Ʈ�� Layer �Ҽ��� ���°�� �θ�� �����ϰ� �����ش�.
		if (_bMoveChild || -1 == pChild->m_iLayerIdx)
		{
			pChild->SetLayerIndex(m_iLayerIndex);
			//if (SCENE_STATE::PAUSE == CSceneMgr::GetInst()->GetCurScene()->GetState() || SCENE_STATE::PLAY == CSceneMgr::GetInst()->GetCurScene()->GetState())
				//pChild->awake();
		}

		// �ش� ������Ʈ�� �� �ڽ��� �����ϰ� ������ ť�� �־ ��� ��ȸ�ϵ��� �Ѵ�.
		std::back_insert_iterator< list<CGameObject*>> enditer(queue);
		std::copy(pChild->m_vecChild.begin(), pChild->m_vecChild.end(), enditer);
	}
}

void CLayer::SaveToScene(FILE* _pFile)
{
	CEntity::SaveToScene(_pFile);

	UINT iCount = (UINT)m_vecParentObj.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);

	for (size_t i = 0; i < m_vecParentObj.size(); ++i)
	{
		m_vecParentObj[i]->SaveToScene(_pFile);
	}
}

void CLayer::LoadFromScene(FILE* _pFile)
{
	CEntity::LoadFromScene(_pFile);

	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iCount; ++i)
	{
		CGameObject* pNew = new CGameObject;
		pNew->LoadFromScene(_pFile);
		pNew->SetLayerIndex(-1);
		AddObject(pNew, false);
	}
}
