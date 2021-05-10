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
#include <Script/CEndBlockScript.h>
#include <Script/CJumpUpScript.h>
#include <Script/CElecTowerScript.h>
#include <Script/CElecBlockScript.h>
#include <Script/CElecChildScript.h>

#include <Script\CTileCollsion.h>
#include <Script\CObjEventScript.h>
#include <Script\CMapScript.h>

#include "CSaveLoadMgr.h"

void CreateTestScene()
{
	SceneInit();
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
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari");

	

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 17, 0.03f,true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 16, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 11, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture, Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 55, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT", m_pTexture, Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 21, 0.03f, true);

	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_UP", m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 21, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 55, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT", m_pTexture, Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 21, 0.03f);


	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_DOWN", m_pTexture, Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 18, 0.03f);



	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);

	CPlayerScript* Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetCharacter(Character::NARI);

	pCurScene->AddObject(pObj, 0);


	/*
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

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 10, 0.03f,true);
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
	*/

	


	

	//애니메이션 
	//CResMgr::GetInst()->Load<CTexture>(L"SKILL", L"texture\\smoke.png");
	//Ptr<CTexture> pSTex = CResMgr::GetInst()->FindRes<CTexture>(L"SKILL");
	//CGameObject* pChildObj1 = new CGameObject;
	//pChildObj1->SetName(L"SKILL");
	//pChildObj1->AddComponent(new CTransform);
	//pChildObj1->AddComponent(new CMeshRender);
	//pChildObj1->AddComponent(new CAnimator2D);
	//pChildObj1->Transform()->SetLocalScale(Vec3(0.15f, 0.15f, 0.f));
	//pChildObj1->Transform()->SetLocalPos(Vec3(0.f, -0.2f, 0.f));
	//pChildObj1->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pChildObj1->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	////pChildObj1->Animator2D()->CreateAnimation(L"skill", pSTex, Vec2(0.f, 0.f), Vec2(497.f, 360.f), 22, 0.02f); //fff
	//pChildObj1->Animator2D()->CreateAnimation(L"smoke", pSTex, Vec2(0.f, 0.f), Vec2(43.f, 43.f), 9, 0.1f); //smoke
	//pChildObj1->Animator2D()->PlayAnimation(L"smoke", true);
	//pCurScene->AddObject(pChildObj1, 10);
	//CScript::AddChild(pObj, pChildObj1);


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
	/*CGameObject* pParticleObject = new CGameObject;
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);
	pParticleObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 300.f));
	pCurScene->AddObject(pParticleObject, 0);
	*/

	// ===============
	// Button object (빨간버튼)
	//// ===============
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


	// ===============
	// stonedoor object (열리는 돌문)
	// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"StoneDoor");//////////

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CStoneDoorScript);////////
	//pObj->AddComponent(new CObjEventScript);

	//pObj->Transform()->SetLocalPos(Vec3(191.f,-111.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));////////////

	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	//dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->SetEventType(EventType::TriggerOnOff);
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

	// ===============
	// Speed Up Board ( 스피드 업 발판 )
	// ===============
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
	//pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
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
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
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
	//pObj = new CGameObject;
	//pObj->SetName(L"BreakableStone"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBreakableStoneScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-224.f, -30.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	//// ===============
	//// BombFlower (폭탄꽃)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"BombFlower"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBombFlowerScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(32.f, 45.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(60, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 3);

	//Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->FindRes<CTexture>(L"Burn");

	//// ===============
	//// FireWood (장작)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"FireWood"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CFireWoodScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-32.f, 300.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(42, 60, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//dynamic_cast<CFireWoodScript*>(pObj->GetScript(L"CFireWoodScript"))->SetFireTime(5.f); //5초 설정, 아무것도 설정하지 않으면 계속 켜져있는 것
	//pObj->AddComponent(new CObjEventScript);
	//pCurScene->AddObject(pObj, 3);

	//// 불 애니메이션
	//CGameObject* pChildObj = new CGameObject;
	//pChildObj->SetName(L"FireWoodChild");
	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);
	//pChildObj->AddComponent(new CAnimator2D);
	//pChildObj->Transform()->SetLocalScale(Vec3(1.1, 1.5, 0.f));
	//pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.7f, 0.f));
	//pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	//pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	//pChildObj->Animator2D()->CreateAnimation(L"NONE", pSmokeTex, Vec2(0.f, 0.f), Vec2(0.f, 1.f), 5, 0.1f);
	//pChildObj->Animator2D()->PlayAnimation(L"NONE", true);
	//pCurScene->AddObject(pChildObj, 3);
	//CScript::AddChild(pObj, pChildObj);

	//// ===============
	////  FireBowl (화로)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"FireBowl"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CFireBowlScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-158.f, 227.f, 401.f));
	//pObj->Transform()->SetLocalScale(Vec3(60, 60, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 3);

	//// 불 애니메이션
	//pChildObj = new CGameObject;
	//pChildObj->SetName(L"FireBowlChild");
	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);
	//pChildObj->AddComponent(new CAnimator2D);
	//pChildObj->Transform()->SetLocalScale(Vec3(1, 2, 0.f));
	//pChildObj->Transform()->SetLocalPos(Vec3(0, 0.63, 0.f));
	//pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	//pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	//pChildObj->Animator2D()->PlayAnimation(L"BURN", true);
	//pCurScene->AddObject(pChildObj, 3);

	//CScript::AddChild(pObj, pChildObj);
	
	// ===============
	// EndBlock (ENd Block)
	// ===============
	/*
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
	pCurScene->AddObject(pObj, 2);

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
	pCurScene->AddObject(pObj, 3);

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
	pCurScene->AddObject(pObj, 2);

	// Elec Tower (자식)
	CGameObject* pChildObj = new CGameObject;
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
	pCurScene->AddObject(pChildObj, 2);
	CScript::AddChild(pObj, pChildObj);

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
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	pCurScene->AddObject(pObj, 3);

	// ===============
	// Elec Block (전기 블록) 2222
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecBlock2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-32.f, 170.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	pCurScene->AddObject(pObj, 3);

	// 0번 Player / 1번 배경 / 2번 장애물 / 3번 버튼,폭탄꽃

	//test
	//pObj = new CGameObject;
	//pObj->SetName(L"FireBowl"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 401.f));
	//pObj->Transform()->SetLocalScale(Vec3(500, 500, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));/////
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));
	// pTex = CResMgr::GetInst()->FindRes<CTexture>(L"dd");
	//if (nullptr == pTex)
	//	pTex = CResMgr::GetInst()->Load<CTexture>(L"dd", L"texture\\dd.png");
	//pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	//pCurScene->AddObject(pObj, 3);
	//CScript::AddChild(pObj, pChildObj);
	*/
	// Collision Check
	CCollisionMgr::GetInst()->CollisionCheck(0, 2);
	CCollisionMgr::GetInst()->CollisionCheck(0, 3);
	CCollisionMgr::GetInst()->CollisionCheck(2, 3);
	CCollisionMgr::GetInst()->CollisionCheck(0, 31);
	
	// Scene Save
	CSaveLoadMgr::SaveScene(pCurScene, L"scene\\TestScene.scene");
	
	// Scene Initialize()
	//pCurScene->awake();
	//pCurScene->start();
}

//이미지 로드
void SceneInit()
{
	// Load GUI UI
	CResMgr::GetInst()->Load<CTexture>(L"LoadButton", L"icon\\loadbutton.png");
	CResMgr::GetInst()->Load<CTexture>(L"SaveButton", L"icon\\savebutton.png");
	CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");

	// Load Player Img
	CResMgr::GetInst()->Load<CTexture>(L"Marina", L"texture\\player\\marina\\marina.png");	//마리나
	CResMgr::GetInst()->Load<CTexture>(L"Nari", L"texture\\player\\nari\\nari.png");		//나리
	CResMgr::GetInst()->Load<CTexture>(L"Eva", L"texture\\player\\eva\\eva.png");			//에바
	CResMgr::GetInst()->Load<CTexture>(L"Garam", L"texture\\player\\garam\\garam.png");	//가람


	// Load Attack Effect
	// Marina
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack1", L"texture\\player\\marina\\skill\\Attack1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack2", L"texture\\player\\marina\\skill\\Attack2.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack3", L"texture\\player\\marina\\skill\\Attack3.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Skill1", L"texture\\player\\marina\\skill\\Skill1_1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Skill2", L"texture\\player\\marina\\skill\\hook.png");

	//Nari
	CResMgr::GetInst()->Load<CTexture>(L"Nari_Attack1", L"texture\\player\\nari\\skill\\Attack1.png");


	//garam


	//marina




	// BackGround Img
	CResMgr::GetInst()->Load<CTexture>(L"Desert", L"texture\\BackGround\\Desert.png");
	CResMgr::GetInst()->Load<CTexture>(L"Dungeon", L"texture\\BackGround\\Dungeon.png");
	CResMgr::GetInst()->Load<CTexture>(L"Snack", L"texture\\BackGround\\Snack.png");
	CResMgr::GetInst()->Load<CTexture>(L"Town", L"texture\\BackGround\\Town.png");


	// Load Obj Img 
	CResMgr::GetInst()->Load<CTexture>(L"redbutton", L"texture\\object\\8.png");			//빨간 버튼
	CResMgr::GetInst()->Load<CTexture>(L"stonedoor", L"texture\\object\\6.png");			//돌로 된 문 (버튼을 밟으면 열림)
	CResMgr::GetInst()->Load<CTexture>(L"stonedoor2", L"texture\\object\\6-1.png");			//돌로 된 문 (버튼을 밟으면 열림)
	CResMgr::GetInst()->Load<CTexture>(L"pushstone", L"texture\\object\\17.png");			//밀 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"pushsmallstone", L"texture\\object\\12.png");		//밀 수 있는 작은돌
	CResMgr::GetInst()->Load<CTexture>(L"breakablestone", L"texture\\object\\15.png");		//부실 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"block", L"texture\\object\\18.png");				//지나갈 수 없는 장애물
	CResMgr::GetInst()->Load<CTexture>(L"barbedblock", L"texture\\object\\13.png");			//가시 달린 장애물
	CResMgr::GetInst()->Load<CTexture>(L"speedup", L"texture\\object\\9.png");				//스피드 업 발판
	CResMgr::GetInst()->Load<CTexture>(L"jumpup", L"texture\\object\\7.png");				//점픛 업 발판
	CResMgr::GetInst()->Load<CTexture>(L"bombflower", L"texture\\object\\14.png");			//폭탄꽃
	CResMgr::GetInst()->Load<CTexture>(L"flower", L"texture\\object\\14-1.png");			//꽃
	CResMgr::GetInst()->Load<CTexture>(L"bomb", L"texture\\object\\14-3.png");				//폭탄
	CResMgr::GetInst()->Load<CTexture>(L"firewood", L"texture\\object\\5.png");				//장작
	CResMgr::GetInst()->Load<CTexture>(L"firebowl", L"texture\\object\\4.png");				//화로
	CResMgr::GetInst()->Load<CTexture>(L"endblock", L"texture\\object\\1.png");				//End block
	CResMgr::GetInst()->Load<CTexture>(L"endblock2", L"texture\\object\\1-1.png");			//End block 부셔진것
	CResMgr::GetInst()->Load<CTexture>(L"elecblock", L"texture\\object\\10.png");			//Electric Block
	CResMgr::GetInst()->Load<CTexture>(L"electower", L"texture\\object\\11.png");			//Electirc Tower

	// Texture 로딩 테스트
	CResMgr::GetInst()->Load<CTexture>(L"Burn", L"texture\\particle\\fire.png");
	CResMgr::GetInst()->Load<CTexture>(L"Background", L"texture\\Background.png");
}