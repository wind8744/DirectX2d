#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh()
	: m_tVBDesc{}
	, m_tIBDesc{}
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CMesh::~CMesh()
{
}

void CMesh::Create(VTX* _pVTXSysmem, UINT _iVtxCount, UINT* _IdxSysmem, UINT _iIdxCount)
{
	m_iVtxCount = _iVtxCount;
	m_iIdxCount = _iIdxCount;
	
	// GPU �޸𸮿� Vertex Buffer �����
	m_tVBDesc.ByteWidth = sizeof(VTX) * m_iVtxCount;	// GPU �� ������ ���� �޸� ũ��
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;				// ���� �Ұ���
	m_tVBDesc.CPUAccessFlags = 0;						// ���� �Ұ���
	m_tVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// Vertex Buffer �뵵

	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = _pVTXSysmem;							// �ʱ� ������

	HRESULT hr = DEVICE->CreateBuffer(&m_tVBDesc, &tSubDesc, &m_pVB);

	// GPU �޸𸮿� Index Buffer �����
	m_tIBDesc.ByteWidth = sizeof(UINT) * m_iIdxCount;	// GPU �� ������ ���� �޸� ũ��
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;				// ���� �Ұ��� ����
	m_tIBDesc.CPUAccessFlags = 0;						// ���� �Ұ��� ����
	m_tIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		// Index Buffer �뵵

	tSubDesc = {};
	tSubDesc.pSysMem = _IdxSysmem;						// �ʱ� ������

	hr = DEVICE->CreateBuffer(&m_tIBDesc, &tSubDesc, &m_pIB);
}

void CMesh::UpdateData()
{	
	// Topology(������) ����
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	UINT iStride = sizeof(VTX);
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_pVB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::render()
{
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}

void CMesh::render_particle(UINT _iParticleCount)
{
	CONTEXT->DrawIndexedInstanced(m_iIdxCount, _iParticleCount, 0, 0, 0);
}
