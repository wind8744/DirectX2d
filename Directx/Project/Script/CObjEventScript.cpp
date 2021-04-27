#include "pch.h"
#include "CObjEventScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include "CMissileScript.h"

CObjEventScript::CObjEventScript()
	: CScript((int)SCRIPT_TYPE::OBJEVENTSCRIPT)
{

}

CObjEventScript::~CObjEventScript()
{
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
				if (!ChildTrigger[i].GetTrigger())
					return;
			}
			b_TriggerOn = true;
		}

		break;
		case EventType::TriggerOrderOn:


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

