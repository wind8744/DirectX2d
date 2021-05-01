#include "pch.h"
#include "CObjEventScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include "CMissileScript.h"

CObjEventScript::CObjEventScript()
	: CScript((int)SCRIPT_TYPE::OBJEVENTSCRIPT),
	E_EvnetType(EventType::TriggerOn),
	b_TriggerOn(false),
	m_pParentObj(nullptr)
{

	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "HP", &a));
}

CObjEventScript::~CObjEventScript()
{
	if (m_pParentObj != nullptr)
	{
		vector<CObjEventScript*>& Parent = m_pParentObj->GetChildeTrigger();
		vector<CObjEventScript*>::iterator iter = Parent.begin();
		for (; iter != Parent.end(); ++iter)
		{
			if (this == (*iter))
			{
				Parent.erase(iter);
				break;
			}
		}
	}
	if (ChildTrigger.size() > 0)
	{
		for (size_t i = 0; i < ChildTrigger.size(); i++)
		{
			ChildTrigger[i]->SetParent(nullptr);
		}
	}
}

void CObjEventScript::awake()
{

}

void CObjEventScript::update()
{

	if (ChildTrigger.size() > 0)
	{
		switch (E_EvnetType)
		{
		case EventType::TriggerOn:
		{
			for (size_t i = 0; i < ChildTrigger.size(); i++)
			{
				if (!ChildTrigger[i]->GetTrigger())
					return;
			}
			b_TriggerOn = true;
		}
		break;
		case EventType::TriggerOnOff:
		{
			for (size_t i = 0; i < ChildTrigger.size(); i++)
			{
				if (!ChildTrigger[i]->GetTrigger())
				{
					b_TriggerOn = false;
					return;
				}
			}
		}
		b_TriggerOn = true;
		case EventType::TriggerOrderOn:


			break;
		}
	}



}

void CObjEventScript::PushEvnetChild(CGameObject* _Event)
{
	if (dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"))->GetTrigger())
		return;

	ChildTrigger.push_back(dynamic_cast<CObjEventScript*>(_Event->GetScript(L"CObjEventScript")));
	CObjEventScript* Event = dynamic_cast<CObjEventScript*>(_Event->GetScript(L"CObjEventScript"));
	Event->m_pParentObj = this;
}

void CObjEventScript::ReleaseEvent(int _num)
{
	size_t n = _num;
	ChildTrigger[n]->SetParent(nullptr);
	vector<CObjEventScript*>::iterator iter = ChildTrigger.begin();
	for (; iter != ChildTrigger.end(); ++iter)
	{
		if (ChildTrigger[n] == (*iter))
		{
			ChildTrigger.erase(iter);
			break;
		}
	}


}

void CObjEventScript::OnCollisionEnter(CGameObject* _pOther)
{

}

void CObjEventScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);


}

void CObjEventScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);


}

