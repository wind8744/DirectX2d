#include "pch.h"
#include "CObjEvent.h"

void CObjEvent::awake()
{
}

void CObjEvent::update()
{
	if (ChildTrigger.size() > 0)
	{
		switch (E_EvnetType)
		{
		case EventType::TriggerOn:
		{
			for (size_t i = 0; i < ChildTrigger.size(); i++)
			{
				if (!ChildTrigger[i].GetTirrger())
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



CObjEvent::CObjEvent() : CScript((int)SCRIPT_TYPE::OBJEVENT),
E_EvnetType(EventType::TriggerOn),
b_TriggerOn(false)
{
	
}

CObjEvent::~CObjEvent()
{
}
