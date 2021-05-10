#include "pch.h"
#include "CCamera.h"

#include "CTransform.h"
#include "CDevice.h"
#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CRenderMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CLayer.h"

#include "CMeshRender.h"
#include "CParticleSystem.h"
#include "CCollider2D.h"

#include "CMaterial.h"
#include "CGraphicsShader.h"


CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_eProjType(PROJ_TYPE::PERSPECTIVE)
	, m_vScale(Vec2(1.f, 1.f))
	, m_fFOV(XM_PI / 2.f)
{
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
	/*if (KEY_HOLD(KEY_TYPE::NUM_1))
	{
		m_vScale += 1.f * fDT;
	}
	else if (KEY_HOLD(KEY_TYPE::NUM_2))
	{
		m_vScale -= 1.f * fDT;
	}
	*/
	Vec3 vPos = Transform()->GetLocalPos();
	/*
	if (KEY_HOLD(KEY_TYPE::KEY_W))
	{
		Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::UP);
		vPos += vFront * fDT * 500.f;
	}

	if (KEY_HOLD(KEY_TYPE::KEY_S))
	{
		Vec3 vBack = -Transform()->GetWorldDir(DIR_TYPE::UP);
		vPos += vBack * fDT * 500.f;
	}
	
	if (KEY_HOLD(KEY_TYPE::KEY_A))
	{
		Vec3 vLeft = -Transform()->GetWorldDir(DIR_TYPE::RIGHT);		
		vPos += vLeft * fDT * 500.f;	
	}

	if (KEY_HOLD(KEY_TYPE::KEY_D ))
	{
		Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);		
		vPos += vRight * fDT * 500.f;		
	}
		*/
	/*if (KEY_HOLD(KEY_TYPE::RBTN))
	{
		Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();

		Vec3 vRot = Transform()->GetLocalRot();

		vRot.x -= vMouseDir.y * fDT * 10.f;
		vRot.y += vMouseDir.x * fDT * 10.f;

		Transform()->SetLocalRot(vRot);
	}*/
	
	Transform()->SetLocalPos(vPos);
	CamaraPos = vPos;
}

void CCamera::finalupdate()
{
	// View 행렬
	// View 행렬 이동파트(카메라 위치 역)
	Vec3 vCamPos = -Transform()->GetWorldPos();
	Matrix matTranslation = XMMatrixTranslation(vCamPos.x, vCamPos.y, vCamPos.z);
	
	// View 행렬 회전파트(우, 상, 전 벡터의 전치)
	Matrix matRot = XMMatrixIdentity();
	Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	Vec3 vUp = Transform()->GetWorldDir(DIR_TYPE::UP);
	Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	matRot._11 = vRight.x;	matRot._12 = vUp.x; matRot._13 = vFront.x; 
	matRot._21 = vRight.y;	matRot._22 = vUp.y;	matRot._23 = vFront.y;	
	matRot._31 = vRight.z;	matRot._32 = vUp.z;	matRot._33 = vFront.z;	

	m_matView = matTranslation* matRot;

	// Proj 행렬
	// FOV(file of view) 시야각
	// Aspect Ratio 종횡비
	if (PROJ_TYPE::PERSPECTIVE == m_eProjType)
	{
		POINT ptResolution = CDevice::GetInst()->GetBufferResolution();
		float fAR = (float)ptResolution.x / (float)ptResolution.y;
		m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, fAR, 1.f, 1000.f);
	}
	else
	{
		POINT ptRes = CCore::GetInst()->GetWndResolution();
		m_matProj = XMMatrixOrthographicLH(ptRes.x * m_vScale.x, ptRes.y * m_vScale.y, 1.f, 1000.f);
	}	

	CRenderMgr::GetInst()->RegisterCamera(this);
}


void CCamera::SetLayerCheck(UINT _iLayerIdx, bool _bAdd)
{
	assert(!(_iLayerIdx >= MAX_LAYER));
		
	if (_bAdd)
	{
		m_iLayerCheck |= 1 << _iLayerIdx;
	}	
	else
	{
		m_iLayerCheck &= ~(1 << _iLayerIdx);
	}
}

void CCamera::SortObject()
{
	m_vecForward.clear();
	m_vecParticle.clear();
	m_vecPostEffect.clear();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if ((1 << i) & m_iLayerCheck)
		{
			const vector<CGameObject*>& vecObj = pCurScene->GetLayer(i)->GetObjects();
			for (size_t j = 0; j < vecObj.size(); ++j)
			{
				if (vecObj[j]->ParticleSystem())
				{
					m_vecParticle.push_back(vecObj[j]);
				}
				else if ( vecObj[j]->MeshRender() 
					&& vecObj[j]->MeshRender()->GetSharedMaterial().Get() 
					&& vecObj[j]->MeshRender()->GetSharedMaterial()->GetShader().Get())
				{
					SHADER_POV ePOV = vecObj[j]->MeshRender()->GetSharedMaterial()->GetShader()->GetPOV();

					if (SHADER_POV::FORWARD == ePOV)
						m_vecForward.push_back(vecObj[j]);
					else if(SHADER_POV::POSTEFFECT == ePOV)
						m_vecPostEffect.push_back(vecObj[j]);
				}
				else if (!vecObj[j]->MeshRender() && vecObj[j]->Collider2D())
				{
					m_vecForward.push_back(vecObj[j]);
				}
			}
		}
	}
}

void CCamera::render_forward()
{
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;

	for (size_t i = 0; i < m_vecForward.size(); ++i)
	{
		if(m_vecForward[i]->MeshRender())
			m_vecForward[i]->MeshRender()->render();

		if (m_vecForward[i]->Collider2D())
			m_vecForward[i]->Collider2D()->render();
	}

	for (size_t i = 0; i < m_vecParticle.size(); ++i)
	{
		m_vecParticle[i]->ParticleSystem()->render();

		if (m_vecParticle[i]->Collider2D())
			m_vecParticle[i]->Collider2D()->render();
	}
}

void CCamera::render_posteffect()
{
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;

	for (size_t i = 0; i < m_vecPostEffect.size(); ++i)
	{
		CRenderMgr::GetInst()->CopyTarget();

		m_vecPostEffect[i]->MeshRender()->render();

		if (m_vecPostEffect[i]->Collider2D())
			m_vecPostEffect[i]->Collider2D()->render();
	}
}

void CCamera::SaveToScene(FILE* _pFile)
{
	CComponent::SaveToScene(_pFile);

	fwrite(&m_eProjType, sizeof(UINT), 1, _pFile);
	fwrite(&m_vScale, sizeof(Vec2), 1, _pFile);
	fwrite(&m_fFOV, sizeof(float), 1, _pFile);
	fwrite(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}

void CCamera::LoadFromScene(FILE* _pFile)
{
	CComponent::LoadFromScene(_pFile);

	fread(&m_eProjType, sizeof(UINT), 1, _pFile);
	fread(&m_vScale, sizeof(Vec2), 1, _pFile);
	fread(&m_fFOV, sizeof(float), 1, _pFile);
	fread(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
}
