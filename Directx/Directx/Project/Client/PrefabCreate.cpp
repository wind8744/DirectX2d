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
#include <Script\CJumpUpScript.h>
#include <Script\CEndBlockScript.h>
#include <Script\CElecChildScript.h>
#include <Script\CElecBlockScript.h>
#include <Script\CElecTowerScript.h>
#include <Script\CPlayerPosSetScript.h>
#include <Script\CTargetToAuto.h>
#include "CSaveLoadMgr.h"


void CreateSamplePrefab()
{
	//TileCollsion
	CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CTileCollsion);

	pObject->Transform()->SetLocalScale(Vec3(TileSize_X, TileSize_Y, 400.f));


	Ptr<CPrefab> pPrefab = new CPrefab(pObject);
	pPrefab->Save(L"prefab\\TileCollsion.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"TileCollsion", pPrefab);
	

	//===============
	// Button object (빨간버튼)
	// ===============
	CGameObject* redbutton = new CGameObject;
	redbutton->SetName(L"RedButton");////////

	redbutton->AddComponent(new CTransform);
	redbutton->AddComponent(new CMeshRender);
	redbutton->AddComponent(new CCollider2D);
	redbutton->AddComponent(new CRedButtonScript);////////
	redbutton->AddComponent(new CObjEventScript);
	redbutton->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));
	redbutton->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	redbutton->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	redbutton->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl"));////////

	redbutton->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(redbutton);

	pPrefab->Save(L"prefab\\redbutton.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"redbutton", pPrefab);

	//// ===============
	//// stonedoor object (열리는 돌문)
	//// ===============
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"StoneDoor");//////////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CStoneDoorScript);////////
	pObj->AddComponent(new CObjEventScript);

	pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));////////////

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	//pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, 8.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 48.f));
	pPrefab->Save(L"prefab\\StoneDoor.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"StoneDoor", pPrefab);

	//// ===============
	//// push stone object (미는 장애물)
	//// ===============
	pObj = new CGameObject;
	pObj->SetName(L"PushStone"); /////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CPushStoneScript); ////

	pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl"));/////

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -16.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 48.f));
	pPrefab->Save(L"prefab\\PushStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"PushStone", pPrefab);

	//// ===============
	//// Speed Up Board ( 스피드 업 발판 )
	//// ===============
	pObj = new CGameObject;
	pObj->SetName(L"SpeedUp"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CSpeedUpScript); ////
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SpeedUp.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SpeedUp", pPrefab);

	// ===============
	// Barbed Block (가시 있는 장애물)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BarbedBlock"); /////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBarbedBlockScript); ////
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -8.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\BarbedBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BarbedBlock", pPrefab);


	// ===============
	// Block (일반 장애물)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Block"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBlockScript); ////

	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -8.f));

	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\Block.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Block", pPrefab);



	// ===============
	// BreakableStone (부술 수 있는 돌)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BreakableStone"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBreakableStoneScript); ////

	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BreakableStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BreakableStone", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"BreakableSmallStone"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBreakableStoneScript); ////

	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BreakableSmallStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BreakableSmallStone", pPrefab);

	// ===============
	// BombFlower (폭탄꽃)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BombFlower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombFlowerScript); ////

	pObj->Transform()->SetLocalScale(Vec3(60, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\BombFlower.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BombFlower", pPrefab);

	// ===============
	// Bomb (폭탄)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Bomb"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombScript); ////

	pObj->Transform()->SetLocalScale(Vec3(40, 50, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Bomb.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Bomb", pPrefab);

	// ===============
	// FireWood (장작)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireWood"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CObjEventScript);
	pObj->AddComponent(new CFireWoodScript); ////
	pObj->Transform()->SetLocalScale(Vec3(42, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->FindRes<CTexture>(L"Burn");

	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"FireWoodChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->Transform()->SetLocalScale(Vec3(1.1, 1.5, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.7f, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	pChildObj->Animator2D()->CreateAnimation(L"NONE", pSmokeTex, Vec2(0.f, 0.f), Vec2(0.f, 1.f), 5, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"NONE", true);

	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireWood.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireWood", pPrefab);

	// ===============
	//  FireBowl (화로)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireBowl"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CFireBowlScript); ////
	pObj->Transform()->SetLocalScale(Vec3(60, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	// 불 애니메이션
	pChildObj = new CGameObject;
	pChildObj->SetName(L"FireBowlChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->Transform()->SetLocalScale(Vec3(1, 2, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0, 0.63, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"BURN", true);

	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireBowl.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireBowl", pPrefab);



	// ===============
   // EndBlock (ENd Block)
   // ===============
	pObj = new CGameObject;
	pObj->SetName(L"EndBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CEndBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(0.f, -210.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(150, 200, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"EndBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.5f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -50.f));

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EndBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EndBlock", pPrefab);

	// ===============
	// Jump Up Board ( 점프 발판 )
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"JumpUp"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CJumpUpScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-220.f, 160.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"JumpUpMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\JumpUp.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"JumpUp", pPrefab);

	// ===============
	// Elec Tower (전기 생성 탑)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecTower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecTowerScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-288.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecTowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));

	// Elec Tower (자식)
	pChildObj = new CGameObject;
	pChildObj->SetName(L"ElecChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CElecChildScript); ////
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));/////
	pChildObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pChildObj->Transform()->SetLocalScale(Vec3(10.f, 10.0f, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ElecTower.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ElecTower", pPrefab);


	// ===============
	// Elec Block (전기 블록)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-32.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ElecBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ElecBlock", pPrefab);

	
	//Character
	// ===============
	// Marina
	// ===============

	pObj = new CGameObject;
	pObj->SetName(L"Marina");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);

	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina");

	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2", m_pTexture, Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP3", m_pTexture, Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP4", m_pTexture, Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_UP", m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 22, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture, Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3", m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT4", m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_RIGHT", m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3", m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN4", m_pTexture, Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_DOWN", m_pTexture, Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 22, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture, Vec2(0.f, 256.f * 40), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3", m_pTexture, Vec2(0.f, 256.f * 41), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT4", m_pTexture, Vec2(0.f, 256.f * 42), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture, Vec2(0.f, 256.f * 43), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 256.f * 44), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 256.f * 45), Vec2(256.f, 256.f), 15, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 256.f * 46), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 47), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 48), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 49), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 256.f * 50), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_LEFT", m_pTexture, Vec2(0.f, 256.f * 51), Vec2(256.f, 256.f), 15, 0.03f, true);



	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);


	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Marina.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Marina", pPrefab);

	//Effect
	// ===============
	// Marina Attack
	// ===============

	pObj = new CGameObject;
	pObj->SetName(L"MarinaAttack"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP1", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN1", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT1", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT1", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.033f);

	pObj->Animator2D()->CreateAnimation(L"Attack_UP3", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN3", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT3", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT3", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack2");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP2", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN2", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT2", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT2", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack3");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP4", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN4", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT4", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT4", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);


	pObj->Animator2D()->PlayAnimation(L"Attack_UP1");

	CMissileScript* Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(0.66f);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaAttack.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaAttack", pPrefab);

	// ===============
	// Marina Skill
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"MarinaSkill"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CPlayerPosSetScript);
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Skill1");

	pObj->Animator2D()->CreateAnimation(L"Skill", m_pTexture, Vec2(0.f, 0.f ), Vec2(128.f, 128.f), 95, 0.03125f);
	pObj->Animator2D()->PlayAnimation(L"Skill");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	
	
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaSkill1", pPrefab);

	// ===============
	// Marina Skill2
	// ===============
	pObj = new CGameObject;

	pObj->SetName(L"MarinaSkill2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CMissileScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Transform()->SetLocalScale(Vec3(96.f, 128.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Marina_SkillMtrl"));/////Std2DMtrl SkillMtrl
	CTargetToAuto* Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(800.f);

	

	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Skill2");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"Marina_SkillMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	



	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaSkill2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaSkill2", pPrefab);




	// ===============
	// Nari Attack
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariAttack"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack1");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttack1", pPrefab);
	// ===============
	// Nari Attack2
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariAttack2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 37.f*2.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack2");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttack2", pPrefab);
	// ===============
	// Nari SKill
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariSkill"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Skill1", m_pTexture, Vec2(0.f, 37.f * 1.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Skill1");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariSkill1", pPrefab);
	/*pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(1000.f, 1000.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));


	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl"));
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Background.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Background", pPrefab);
	*/
	//CResMgr::GetInst()->Load<CPrefab>(L"TileCollsion", L"prefab\\TileCollsion.pref");
}
