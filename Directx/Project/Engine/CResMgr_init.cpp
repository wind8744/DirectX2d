#include "pch.h"
#include "CResMgr.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

void CResMgr::init()
{
	CreateDefaultMesh();

	CreateDefaultShader();

	CreateComputeShader();

	CreateDefaultMaterial();
}

void CResMgr::ClearCloneRes()
{
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		vector<CRes*>::iterator iter = m_vecCloneRes[i].begin();
		for (iter; iter != m_vecCloneRes[i].end();)
		{
			if (0 == (*iter)->GetRefCount())
				iter = m_vecCloneRes[i].erase(iter);			
			else
				++iter;
		}
	}
}

void CResMgr::CreateDefaultMesh()
{
	Ptr<CMesh> pMesh = nullptr;

	vector<VTX> vecVtx;
	vector<UINT> vecIdx;
	VTX v = {};

	// ==========
	// Point Mesh
	// ==========
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);

	vecVtx.push_back(v);
	vecIdx.push_back(0);

	// 생성
	pMesh = new CMesh;
	pMesh->SetTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"PointMesh", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// =========
	// Rect Mesh
	// =========	
	// 0 - 1
	// | \ |
	// 3 - 2
	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	v.vUV = Vec2(1.f, 0.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	v.vUV = Vec2(1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	v.vUV = Vec2(0.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);

	// RectMesh 생성
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"RectMesh", pMesh);	
	
	vecIdx.clear();

	// ====================
	// Rect Collider2D Mesh
	// ====================
	// 0 - 1
	// |   |
	// 3 - 2
	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	vecIdx.push_back(0);	
		
	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
	AddRes<CMesh>(L"RectMesh_C2D", pMesh);

	vecVtx.clear();
	vecIdx.clear();

	// ============
	// Circle Mesh
	// ============
	float fRadius = 0.5f;
	int	  iSliceCount = 40;
	float fTheta = 0.f;

	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	v.vUV = Vec2(0.5f, 0.5f);

	// 중심 점
	vecVtx.push_back(v);

	// 테두리 점
	for (int i = 0; i < iSliceCount + 1; ++i)
	{
		v.vPos = Vec3(fRadius * cosf(fTheta), fRadius * sinf(fTheta), 0.f);
		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);		
		v.vUV = Vec2(v.vPos.x + 0.5f, -v.vPos.y + 0.5f);
		vecVtx.push_back(v);

		fTheta += XM_2PI / iSliceCount;
	}

	// 인덱스
	for (int i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);	
	}

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddRes<CMesh>(L"CircleMesh", pMesh);
	
	vecIdx.clear();

	// =====================
	// Collider2D CircleMesh
	// =====================
	vecVtx.erase(vecVtx.begin());

	// 인덱스
	for (int i = 0; i < iSliceCount; ++i)
	{
		vecIdx.push_back(i);		
	}
	vecIdx.push_back(0);

	pMesh = new CMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	pMesh->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
	AddRes<CMesh>(L"CircleMesh_C2D", pMesh);

	vecVtx.clear();
	vecIdx.clear();
}

void CResMgr::CreateDefaultShader()
{
	// InputLayout 작성
	CGraphicsShader::AddInputLayout("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, false);
	CGraphicsShader::AddInputLayout("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, false);
	CGraphicsShader::AddInputLayout("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, false);
	
	Ptr<CGraphicsShader> pShader;

	// ==============
	// Std2D Shader
	// ==============
	pShader = new CGraphicsShader(SHADER_POV::FORWARD);
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D");

	// OM
	pShader->SetBlendType(BLEND_TYPE::ALPHABLEND);
	//pShader->SetDepthStencilType();

	// Shader Param	
	pShader->AddShaderParam(SHADER_PARAM::TEX_0, L"Output Texture");

	AddRes<CGraphicsShader>(L"Std2DShader", pShader);

	// ==================
	// Collider2D Shader
	// ==================
	pShader = new CGraphicsShader(SHADER_POV::FORWARD);
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Collider2D");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Collider2D");
	pShader->SetDSType(DS_TYPE::NO_TEST);

	AddRes<CGraphicsShader>(L"Collider2DShader", pShader);


	pShader = new CGraphicsShader(SHADER_POV::FORWARD);

	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_TILE");
	//pShader->CreateGeometryShader(L"shader\\std2d.fx", "GS_TILE");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_TILE");

	AddRes<CGraphicsShader>(L"MaptoolShader", pShader);


	// ======================
	// Particle Render Shader
	// ======================
	pShader = new CGraphicsShader(SHADER_POV::PARTICLE);	

	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Particle");
	pShader->CreateGeometryShader(L"shader\\std2d.fx", "GS_Particle");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Particle");
	pShader->SetBlendType(BLEND_TYPE::ALPHA_ONE);
	pShader->SetDSType(DS_TYPE::LESS_NO_WRITE);	

	AddRes<CGraphicsShader>(L"ParticleRenderShader", pShader);

	// ==================
	// PostEffect Shader
	// ==================
	pShader = new CGraphicsShader(SHADER_POV::POSTEFFECT);
	pShader->CreateVertexShader(L"shader\\posteffect.fx", "VS_PostEffect");
	pShader->CreatePixelShader(L"shader\\posteffect.fx", "PS_PostEffect");
	pShader->SetDSType(DS_TYPE::NO_TEST);

	AddRes<CGraphicsShader>(L"PostEffectShader", pShader);


	// ==============
	// Std2D Shader222222222
	// ==============
	pShader = new CGraphicsShader(SHADER_POV::FORWARD);
	pShader->CreateVertexShader(L"shader\\std2d.fx", "VS_Std2D2");
	pShader->CreatePixelShader(L"shader\\std2d.fx", "PS_Std2D2");

	// OM
	pShader->SetBlendType(BLEND_TYPE::ALPHABLEND);
	//pShader->SetDepthStencilType();

	// Shader Param	
	//pShader->AddShaderParam(SHADER_PARAM::TEX_0, L"Output Texture2");

	AddRes<CGraphicsShader>(L"Std2DShader2", pShader);


}

#include "CCopyShaderCS.h"
#include "CParticleUpdateShader.h"
void CResMgr::CreateComputeShader()
{
	Ptr<CComputeShader> pCS = nullptr;
	
	// CopyTextureShader
	pCS = new CCopyShaderCS;
	pCS->CreateComputeShader(L"shader\\CopyTexture.fx", "CS_CopyTex");
	AddRes<CComputeShader>(L"CopyTextureShader", pCS);

	// Particle Update Shader
	pCS = new CParticleUpdateShader;
	pCS->CreateComputeShader(L"shader\\particleupdate.fx", "CS_ParticleUpdate");
	AddRes<CComputeShader>(L"ParticleUpdateShader", pCS);
}

void CResMgr::CreateDefaultMaterial()
{
	Ptr<CMaterial> pMtrl = nullptr;

	// ===============
	// Std2D Material
	// ===============
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"Std2DMtrl", pMtrl);

	// ===================
	// Collider2D Material
	// ===================
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"Collider2DShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"Collider2DMtrl", pMtrl);

	// ========================
	// Particle Render Material
	// ========================
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"ParticleRenderShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"ParticleRenderMtrl", pMtrl);

	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"MaptoolShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"MaptoolRenderMtrl", pMtrl);


	// ===================
	// PostEffect Material
	// ===================
	pMtrl = new CMaterial;
	pMtrl->m_bDefault = true;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"PostEffectShader"));
	AddRes<CMaterial>(L"PostEffectMtrl", pMtrl);

	//============================================================================== OBJ Material

	// ==================
	// StoneDoor material
	// ==================
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"Std2DMtrl2", pMtrl);

	// ==================
	// RedButton material
	// ==================
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"RedButtonMtrl", pMtrl);

	// ==================
	// PushStone material
	// ==================
	pMtrl = new CMaterial;
	pMtrl->SetShader(FindRes<CGraphicsShader>(L"Std2DShader"));
	pMtrl->m_bDefault = true;
	AddRes<CMaterial>(L"PushStoneMtrl", pMtrl);

}

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
