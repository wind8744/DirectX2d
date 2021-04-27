#include "pch.h"
#include "CEventMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CGameObject.h"

CEventMgr::CEventMgr()
	: m_bEvent(false)
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// ======================
	// ���� ���� ������Ʈ ����
	// ======================
	for (size_t i = 0; i < m_vecDeadObj.size(); ++i)
	{
		if (nullptr != m_vecDeadObj[i])
		{
			// Layer ���� ������(�ֻ��� �θ��� ���)
			if (nullptr == m_vecDeadObj[i]->GetParent())
				m_vecDeadObj[i]->ReleaseAsParentObj();

			// �ڽ� ������Ʈ�� ���, �θ� ���� ����
			else
				m_vecDeadObj[i]->DisconnectWithParent();
			
			delete m_vecDeadObj[i];
		}		
	}
	m_vecDeadObj.clear();


	// ==========
	// Event ó��
	// ==========
	m_bEvent = false;

	while (!m_event.empty())
	{
		const tEvent& event = m_event.top();
		
		ExcuteEvent(event);

		m_event.pop();
	}
}

void CEventMgr::ExcuteEvent(const tEvent& _event)
{
	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:		
		CSceneMgr::GetInst()->GetCurScene()->AddObject((CGameObject*)_event.lParam, (int)_event.wParam);
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		CGameObject* pObject = (CGameObject*)_event.lParam;
		m_vecDeadObj.push_back(pObject);
		pObject->m_bDead = true;
	}

		break;	
	case EVENT_TYPE::ADD_CHILD:
	{
		CGameObject* pParent = (CGameObject*)_event.lParam;
		CGameObject* pChild = (CGameObject*)_event.wParam;
				
		pParent->AddChild(pChild);
	}

		break;
	case EVENT_TYPE::DISCONNECT_PARENT:
	{
		CGameObject* pObject = (CGameObject*)_event.lParam;
		pObject->DisconnectWithParent();
		pObject->RegisterAsParentObj();
	}
		break;

		// lParam : Prev Scene
		// wParam : Next Scene
	case EVENT_TYPE::SCENE_CHANGE:
		m_vecDeadObj.clear(); // Scene �� ��ȯ�Ǹ鼭, ���� SCene ���� ��������. ���� EventMgr ���� ó������ �ʴ´�.

		delete ((CScene*)_event.lParam);
		CSceneMgr::GetInst()->m_pCurScene = (CScene*)_event.wParam;

		break;

	case EVENT_TYPE::END:
		break;
	default:
		break;
	}


	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:		
	case EVENT_TYPE::DELETE_OBJECT:
	case EVENT_TYPE::ADD_CHILD:
	case EVENT_TYPE::DISCONNECT_PARENT:
	case EVENT_TYPE::SCENE_CHANGE:
		m_bEvent = true;
		break;	
	}	
}
