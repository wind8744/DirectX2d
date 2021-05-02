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
	//TileCollsion
	/*CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CTileCollsion);

	pObject->Transform()->SetLocalScale(Vec3(TileSize_X, TileSize_Y, 400.f));


	Ptr<CPrefab> pPrefab = new CPrefab(pObject);
	pPrefab->Save(L"prefab\\TileCollsion.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"TileCollsion", pPrefab);
	*/

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

	Ptr<CPrefab> pPrefab = new CPrefab(redbutton);

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
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -16.f));
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
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.3f, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 20.f), Vec2(64.f, 64.f), 5, 0.1f);
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
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 20.f), Vec2(64.f, 64.f), 5, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"BURN", true);

	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireBowl.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireBowl", pPrefab);


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
	CResMgr::GetInst()->Load<CPrefab>(L"TileCollsion", L"prefab\\TileCollsion.pref");
}
