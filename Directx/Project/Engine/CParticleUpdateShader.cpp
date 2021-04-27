#include "pch.h"
#include "CParticleUpdateShader.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

CParticleUpdateShader::CParticleUpdateShader()
	: m_tInfo{}
	, m_pParticleBuffer(nullptr)
	, m_pSharedBuffer(nullptr)
{
	m_pSharedBuffer = new CStructuredBuffer();
}

CParticleUpdateShader::~CParticleUpdateShader()
{
	if (nullptr != m_pSharedBuffer)
		delete m_pSharedBuffer;
}

void CParticleUpdateShader::UpdateData()
{
	static const CConstBuffer* pMtrlBuffer = CDevice::GetInst()->GetCB(CB_TYPE::MATERIAL);
		
	pMtrlBuffer->SetData(&m_tInfo);
	pMtrlBuffer->UpdateData((UINT)PIPELINE_STAGE::PS_COMPUTE);

	m_pParticleBuffer->UpdateDataRW(0);

	// Shared �����͸� �����ϱ� ���� ���� ����
	tParticleShared tShared = {};
	tShared.iAliveCount = m_iAliveCount;
	m_pSharedBuffer->CreateRW(sizeof(tParticleShared), 1, &tShared);
	m_pSharedBuffer->UpdateDataRW(1);
}

void CParticleUpdateShader::Clear()
{
	m_pParticleBuffer->ClearRW();
}

void CParticleUpdateShader::Excute()
{
	// group thread �� 1024 ��
	int iGroupCount = m_tInfo.arrInt[0] / 1024 + 1;
	Dispatch(iGroupCount , 1, 1);
}