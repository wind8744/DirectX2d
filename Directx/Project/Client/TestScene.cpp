#include "pch.h"
#include "TestScene.h"

#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CMeshRender.h>
#include <Engine\CCamera.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CCollider2D.h>
#include <Engine\CParticleSystem.h>
#include <Engine\CLight2D.h>
#include <Engine\CTexture.h>
#include <Engine\CPathMgr.h>
#include <Engine\CCollisionMgr.h>
#include <Engine\CCopyShaderCS.h>
#include <Engine\CSceneMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMonsterScript.h>
#include <Script\CMissileScript.h>
#include <Script/CRedButtonScript.h>
#include <Script/CStoneDoorScript.h>
#include <Script\CObjEventScript.h>
#include <Script\CMapScript.h>
#include <Script/CPushStoneScript.h>
#include <Script\CTileCollsion.h>
#include "CSaveLoadMgr.h"

void CreateSamplePrefab()
{
	/*CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CMissileScript);

	pObject->Transform()->SetLocalScale(Vec3(50.f, 50.f, 1.f));
	pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CircleMesh"));
	pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));*/

	//Ptr<CPrefab> pPrefab = new CPrefab(pObject);
	//pPrefab->Save(L"prefab\\missile.pref");
	//CResMgr::GetInst()->AddRes<CPrefab>(L"Missile", pPrefab);

	/*CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CTileCollsion);

	pObject->Transform()->SetLocalScale(Vec3(TileSize_X, TileSize_Y, 400.f));


	Ptr<CPrefab> pPrefab = new CPrefab(pObject);
	pPrefab->Save(L"prefab\\TileCollsion.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"TileCollsion", pPrefab);
	*/


	CResMgr::GetInst()->Load<CPrefab>(L"Missile", L"prefab\\missile.pref");
	CResMgr::GetInst()->Load<CPrefab>(L"TileCollsion", L"prefab\\TileCollsion.pref");
}


void CreateTestScene()
{
	CreateSamplePrefab();
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Scene Load
	//CSaveLoadMgr::LoadScene(pCurScene, L"scene\\TestScene.scene");
	//return;


	// =================== 
	// Compute Shader Test
	// ===================
	// Texture Create
	/*Ptr<CTexture> pRWTex = CResMgr::GetInst()->CreateTexture(L"RWTex", 256, 256
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS
		, DXGI_FORMAT_R8G8B8A8_UNORM);*/

		//Ptr<CCopyShaderCS> pCS = (CCopyShaderCS*)CResMgr::GetInst()->FindRes<CComputeShader>(L"CopyTextureShader").Get();
		//pCS->SetDestTex(pRWTex);
		//pCS->Excute();


	CGameObject* pObj = nullptr;

	// Texture 로딩 테스트

	Ptr<CTexture> pTexture = CResMgr::GetInst()->Load<CTexture>(L"Plane", L"texture\\player.bmp");
	Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->Load<CTexture>(L"Smoke", L"texture\\smokeparticle.png");
	Ptr<CTexture> pAnimAtlas = CResMgr::GetInst()->Load<CTexture>(L"Link", L"texture\\link_0.png");
	Ptr<CTexture> pBackgroundTex = CResMgr::GetInst()->Load<CTexture>(L"Background", L"texture\\Background.png");

	int a = 0;


	// =============
	// Camera Object
	// =============
	pObj = new CGameObject;
	pObj->SetName(L"Camera Object");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCamera);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pObj->Camera()->SetLayerAllCheck();

	pCurScene->AddObject(pObj, 0);


	// =======
	// Light2D
	// =======
	pObj = new CGameObject;
	pObj->SetName(L"Light2D Object");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CLight2D);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));

	pObj->Light2D()->SetLightType(LIGHT_TYPE::DIR);
	pObj->Light2D()->SetAmbient(Vec3(1.f, 1.f, 1.f));
	pObj->Light2D()->SetRange(100.f);

	pCurScene->AddObject(pObj, 0);

	// ==============
	// Player Object
	// ==============
	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetLocalPos(Vec3(-200.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(70.f, 70.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", pAnimAtlas, Vec2(0.f, 325.f), Vec2(60.f, 65.f), 10, 0.1f);
	pObj->Animator2D()->PlayAnimation(L"WALK_LEFT", true);

	pCurScene->AddObject(pObj, 0);

	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"Child");
	pChildObj->AddComponent(new CTransform);
	pCurScene->AddObject(pChildObj, 0);

	CScript::AddChild(pObj, pChildObj);


	// ==========
	// Background
	// ==========
	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(1000.f, 1000.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//Camera->SetMapTile(pObj);
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl"));

	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"TILE");
	if (nullptr == pTex)
		pTex = CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");

	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());

	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pCurScene->AddObject(pObj, 1);
	// =============
	// PostEffect
	// =============
	/*CGameObject* pPostEffect = new CGameObject;
	pPostEffect->SetName(L"PostEffect Object");

	pPostEffect->AddComponent(new CTransform);
	pPostEffect->AddComponent(new CMeshRender);

	pPostEffect->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
	pPostEffect->Transform()->SetLocalScale(Vec3(1600.f, 900.f, 1.f));

	pPostEffect->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pPostEffect->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PostEffectMtrl"));

	pCurScene->AddObject(pPostEffect, 1);*/

	// ===============
	// particle object
	// ===============
	/*CGameObject* pParticleObject = new CGameObject;
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);
	pParticleObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	m_pCurScene->AddObject(pParticleObject, 0);*/

	// ===============
	// Button object
	// ===============
	CGameObject* redbutton = new CGameObject;
	redbutton->SetName(L"redbutton");

	redbutton->AddComponent(new CTransform);
	redbutton->AddComponent(new CMeshRender);
	redbutton->AddComponent(new CCollider2D);
	redbutton->AddComponent(new CRedButtonScript);
	redbutton->AddComponent(new CObjEventScript);
	redbutton->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	redbutton->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));
	redbutton->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	redbutton->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	redbutton->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	redbutton->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(redbutton, 2);


	// ===============
	// stonedoor object
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"stonedoor");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CStoneDoorScript);
	pObj->AddComponent(new CObjEventScript);

	pObj->Transform()->SetLocalPos(Vec3(127.f, -125.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl2"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->SetEvnetType(EventType::TriggerOnOff);
	dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->PushEvnetChild(redbutton);

	pCurScene->AddObject(pObj, 2);


	// ===============
	// push stone object (미는 장애물)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"pushstone"); //

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CPushStoneScript); //
	pObj->AddComponent(new CObjEventScript);

	pObj->Transform()->SetLocalPos(Vec3(0.f, -125.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pCurScene->AddObject(pObj, 2);



	
	// Collision Check
	CCollisionMgr::GetInst()->CollisionCheck(0, 2);

	// Scene Save
	CSaveLoadMgr::SaveScene(pCurScene, L"scene\\TestScene.scene");

	// Scene Initialize()
	//pCurScene->awake();
	//pCurScene->start();
}
