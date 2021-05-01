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

// Obj script
#include <Script/CRedButtonScript.h>
#include <Script/CStoneDoorScript.h>
#include <Script/CPushStoneScript.h>
#include <Script/CSpeedUpScript.h>
#include <Script/CBlockScript.h>
#include <Script/CBarbedBlockScript.h>
#include <Script/CBreakableStoneScript.h>
#include <Script/CBombFlowerScript.h>
#include <Script/CBombScript.h>
#include <Script/CFireBowlScript.h>
#include <Script/CFireWoodScript.h>

#include <Script\CTileCollsion.h>
#include <Script\CObjEventScript.h>
#include <Script\CMapScript.h>

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

	SceneInit();

	CGameObject* pObj = nullptr;

	// Texture 로딩 테스트

	Ptr<CTexture> pTexture = CResMgr::GetInst()->Load<CTexture>(L"Plane", L"texture\\player.bmp");
	Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->Load<CTexture>(L"Burn", L"texture\\particle\\firesprite2.png");
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

	pObj->Transform()->SetLocalPos(Vec3(-288.f, 288.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64.f, 64.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", pAnimAtlas, Vec2(0.f, 325.f), Vec2(60.f, 65.f), 10, 0.1f);
	pObj->Animator2D()->PlayAnimation(L"WALK_LEFT", true);

	pCurScene->AddObject(pObj, 0);

	//CGameObject* pChildObj = new CGameObject;
	//pChildObj->SetName(L"Child");
	//pChildObj->AddComponent(new CTransform);
	//pCurScene->AddObject(pChildObj, 0);

	//CScript::AddChild(pObj, pChildObj);


	// ==========
	// Background
	// ==========
	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
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
	///*CGameObject* pPostEffect = new CGameObject;
	//pPostEffect->SetName(L"PostEffect Object");
	//pPostEffect->AddComponent(new CTransform);
	//pPostEffect->AddComponent(new CMeshRender);
	//pPostEffect->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
	//pPostEffect->Transform()->SetLocalScale(Vec3(1600.f, 900.f, 1.f));
	//pPostEffect->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pPostEffect->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PostEffectMtrl"));
	//pCurScene->AddObject(pPostEffect, 1);*/

	// ===============
	// particle object
	// ===============
	CGameObject* pParticleObject = new CGameObject;
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);
	pParticleObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 300.f));
	pCurScene->AddObject(pParticleObject, 0);


	// ===============
	// Button object (빨간버튼)
	// ===============
	//CGameObject* redbutton = new CGameObject;
	//redbutton->SetName(L"RedButton");////////

	//redbutton->AddComponent(new CTransform);
	//redbutton->AddComponent(new CMeshRender);
	//redbutton->AddComponent(new CCollider2D);
	//redbutton->AddComponent(new CRedButtonScript);////////
	//redbutton->AddComponent(new CObjEventScript);
	//redbutton->Transform()->SetLocalPos(Vec3(-95.f, 286.f, 400.f));
	//redbutton->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));
	//redbutton->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	//redbutton->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//redbutton->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl"));////////

	//redbutton->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(redbutton, 3);


	//// ===============
	//// stonedoor object (열리는 돌문)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"StoneDoor");//////////

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CStoneDoorScript);////////
	//pObj->AddComponent(new CObjEventScript);

	//pObj->Transform()->SetLocalPos(Vec3(-30.f,-88.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));////////////

	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	//dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->SetEvnetType(EventType::TriggerOnOff);
	//dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->PushEvnetChild(redbutton);

	//pCurScene->AddObject(pObj, 2);


	//// ===============
	//// push stone object (미는 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"PushStone"); /////

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CPushStoneScript); ////
	//pObj->AddComponent(new CObjEventScript);

	//pObj->Transform()->SetLocalPos(Vec3(-286.f, 170.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl"));/////

	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	//pCurScene->AddObject(pObj, 2);


	//// ===============
	//// Speed Up Board ( 스피드 업 발판 )
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"SpeedUp"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CSpeedUpScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-30.f, 160.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//dynamic_cast<CSpeedUpScript*>(pObj->GetScript(L"CSpeedUpScript"))->PushDir(DIR::DOWN); //방향 선택
	//pCurScene->AddObject(pObj, 3);

	//// ===============
	//// Barbed Block (가시 있는 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"BarbedBlock"); /////

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBarbedBlockScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(228.f, 200.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	//// ===============
	//// Block (일반 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"Block"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBlockScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-222.f, -222.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlockMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	// ===============
	// BreakableStone (부술 수 있는 돌)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BreakableStone"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBreakableStoneScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-224.f, -30.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 2);

	// ===============
	// BombFlower (폭탄꽃)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BombFlower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombFlowerScript); ////
	pObj->Transform()->SetLocalPos(Vec3(32.f, 32.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 3);

	// ===============
	// Bomb (폭탄)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Bomb"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-225.f, 160.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(60, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 3);

	// ===============
	// FireWood (장작)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireWood"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CFireWoodScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-32.f, 300.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(37, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 3);

	// 불 애니메이션
	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"FireWoodChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.3f, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 20.f), Vec2(64.f, 64.f), 5, 0.1f);
	pChildObj->Animator2D()->CreateAnimation(L"NONE", pSmokeTex, Vec2(0.f, 0.f), Vec2(0.f, 1.f), 5, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"NONE", true);
	pCurScene->AddObject(pChildObj, 3);
	CScript::AddChild(pObj, pChildObj);

	// ===============
	//  FireBowl (화로)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireBowl"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CFireBowlScript); ////
	pObj->Transform()->SetLocalPos(Vec3(162.f, 227.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 3);

	// 불 애니메이션
	pChildObj = new CGameObject;
	pChildObj->SetName(L"FireBowlChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 20.f), Vec2(64.f, 64.f), 5, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"BURN", true);
	pCurScene->AddObject(pChildObj, 3);

	CScript::AddChild(pObj, pChildObj);


	// 0번 Player / 1번 배경 / 2번 장애물 / 3번 버튼,폭탄꽃



	// Collision Check
	CCollisionMgr::GetInst()->CollisionCheck(0, 2);
	CCollisionMgr::GetInst()->CollisionCheck(0, 3);
	CCollisionMgr::GetInst()->CollisionCheck(2, 3);

	// Scene Save
	CSaveLoadMgr::SaveScene(pCurScene, L"scene\\TestScene.scene");

	// Scene Initialize()
	//pCurScene->awake();
	//pCurScene->start();
}

//이미지 로드
void SceneInit()
{
	// Load Obj img 
	CResMgr::GetInst()->Load<CTexture>(L"redbutton", L"texture\\object\\8.bmp");			//빨간 버튼
	CResMgr::GetInst()->Load<CTexture>(L"stonedoor", L"texture\\object\\6.jpg");			//돌로 된 문 (버튼을 밟으면 열림)
	CResMgr::GetInst()->Load<CTexture>(L"pushstone", L"texture\\object\\17.jpg");			//밀 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"pushsmallstone", L"texture\\object\\12.jpg");		//밀 수 있는 작은돌
	CResMgr::GetInst()->Load<CTexture>(L"breakablestone", L"texture\\object\\15.jpg");		//부실 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"block", L"texture\\object\\18.jpg");				//지나갈 수 없는 장애물
	CResMgr::GetInst()->Load<CTexture>(L"barbedblock", L"texture\\object\\13.jpg");			//가시 달린 장애물
	CResMgr::GetInst()->Load<CTexture>(L"speedup", L"texture\\object\\9.jpg");				//스피드 업 발판
	CResMgr::GetInst()->Load<CTexture>(L"bombflower", L"texture\\object\\14.jpg");			//폭탄꽃
	CResMgr::GetInst()->Load<CTexture>(L"bomb", L"texture\\object\\14-3.jpg");				//폭탄
	CResMgr::GetInst()->Load<CTexture>(L"firewood", L"texture\\object\\5.jpg");				//장작
	CResMgr::GetInst()->Load<CTexture>(L"firebowl", L"texture\\object\\4.jpg");				//화로

}
