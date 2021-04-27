#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(COMPONENT_TYPE _eType)
	: m_eComType(_eType)
	, m_pObject(nullptr)
{
}

CComponent::CComponent(const CComponent& _origin)
	: m_eComType(_origin.m_eComType)
	, m_pObject(nullptr)
{
}

CComponent::~CComponent()
{
}

void CComponent::SaveToScene(FILE* _pFile)
{
	CEntity::SaveToScene(_pFile);

}

void CComponent::LoadFromScene(FILE* _pFile)
{
	CEntity::LoadFromScene(_pFile);
		
}