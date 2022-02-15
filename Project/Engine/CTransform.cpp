#include "pch.h"
#include "CTransform.h"

#include "CCore.h"
#include "CDevice.h"
#include "CConstBuffer.h"

#include "CGameObject.h"


CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vLocalPos(0.f, 0.f, 0.f)
	, m_vLocalScale(1.f, 1.f, 1.f)
	, m_vLocalRot(0.f, 0.f, 0.f)
	, m_vLocalDir{}
	, m_vWorldDir{}
{
}

CTransform::~CTransform()
{
}

void CTransform::update()
{

}

void CTransform::finalupdate()
{
	Matrix matTranslation = XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_matLocalScale = XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);

	m_matLocalRot = XMMatrixIdentity();
	m_matLocalRot *= XMMatrixRotationX(m_vLocalRot.x);
	m_matLocalRot *= XMMatrixRotationY(m_vLocalRot.y);
	m_matLocalRot *= XMMatrixRotationZ(m_vLocalRot.z);

	m_matWorld = m_matLocalScale * m_matLocalRot * matTranslation;

	// Local ���� ���ϱ�
	static Vec3 vArr[3] = { Vec3(1.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f), Vec3(0.f, 0.f, 1.f) };
	for (int i = 0; i < (int)DIR_TYPE::END; ++i)
	{
		m_vWorldDir[i] = m_vLocalDir[i] = XMVector3TransformNormal(vArr[i], m_matLocalRot);
	}

	// �θ� ������, �θ��� ������� �����
	if (nullptr != GetObj()->GetParent())
	{
		const Matrix& matParentWorldMat = GetObj()->GetParent()->Transform()->GetWorldMat();
		m_matWorld *= matParentWorldMat;

		for (int i = 0; i < (int)DIR_TYPE::END; ++i)
		{
			m_vWorldDir[i] = XMVector3TransformNormal(m_vLocalDir[i], m_matWorld);
			m_vWorldDir[i].Normalize();
		}
	}	
}

void CTransform::UpdateData()
{
	static const CConstBuffer* pBuffer = CDevice::GetInst()->GetCB(CB_TYPE::TRANSFORM);

	g_transform.matWorld = m_matWorld;
	g_transform.matWV = g_transform.matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;

	pBuffer->SetData(&g_transform);
	pBuffer->UpdateData((UINT)PIPELINE_STAGE::PS_ALL);
}

Vec3 CTransform::GetWorldScale()
{
	CGameObject* pParentObj = GetObj()->GetParent();

	Matrix matWorldScale = m_matLocalScale;

	while (nullptr != pParentObj)
	{
		matWorldScale *= pParentObj->Transform()->m_matLocalScale;
		pParentObj = pParentObj->GetParent();
	}

	return Vec3(matWorldScale._11, matWorldScale._22, matWorldScale._33);
}

void CTransform::SaveToScene(FILE* _pFile)
{
	CComponent::SaveToScene(_pFile);

	fwrite(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vLocalRot, sizeof(Vec3), 1, _pFile);
}

void CTransform::LoadFromScene(FILE* _pFile)
{
	CComponent::LoadFromScene(_pFile);

	fread(&m_vLocalPos, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalScale, sizeof(Vec3), 1, _pFile);
	fread(&m_vLocalRot, sizeof(Vec3), 1, _pFile);
}


//Vec3 CTransform::GetWorldRot()
//{
//	CGameObject* pParentObj = GetObj()->GetParent();
//
//	Matrix matWorldRot = m_matLocalRot;
//
//	while (nullptr != pParentObj)
//	{
//		matWorldRot *= pParentObj->Transform()->m_matLocalRot;
//		pParentObj = pParentObj->GetParent();
//	}
//
//	return Vec3(matWorldRot._11, matWorldRot._22, matWorldRot._33);
//}
