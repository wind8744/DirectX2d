#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroup(iRow, iCol);				
			}
		}
	}

}

void CCollisionMgr::CollisionGroup(int _iLeft, int _iRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetLayer(_iLeft)->GetObjects();
	const vector<CGameObject*>& vecRight = pCurScene->GetLayer(_iRight)->GetObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->Collider2D())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->Collider2D() || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			// 두 충돌체 조합 아이디 생성
			COLLIDER_PAIR pairid;
			pairid.iLeftID = vecLeft[i]->Collider2D()->GetID();
			pairid.iRightID = vecRight[j]->Collider2D()->GetID();

			map<LONGLONG, bool>::iterator iter = m_mapColPairInfo.find(pairid.iPairID);
			if (m_mapColPairInfo.end() == iter)
			{
				m_mapColPairInfo.insert(make_pair(pairid.iPairID, false));
				iter = m_mapColPairInfo.find(pairid.iPairID);
			}

			// 현재 기준, 충돌 중인지 검사
			if(Collision(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				// 충돌 했다.
				if (iter->second) // 이전에도 충돌했었다.
				{					
					// 두 오브젝트중 하나라도 삭제 예정상태라면
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						vecLeft[i]->Collider2D()->OnCollisionExit(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollisionExit(vecLeft[i]->Collider2D());
					}
					else
					{
						vecLeft[i]->Collider2D()->OnCollision(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollision(vecLeft[i]->Collider2D());
					}					
				}
				else // 이전에는 충돌하지 않았다.
				{
					// 두 오브젝트중 하나라도 삭제 예정상태라면
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())					
						continue;

					vecLeft[i]->Collider2D()->OnCollisionEnter(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollisionEnter(vecLeft[i]->Collider2D());
					iter->second = true;
				}
			}
			else // 충돌하지 않는다.
			{				
				if (iter->second) // 이전엔 충돌 했었다.
				{
					vecLeft[i]->Collider2D()->OnCollisionExit(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->OnCollisionExit(vecLeft[i]->Collider2D());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::Collision(CCollider2D* _pLeftCol, CCollider2D* _pRightCol)
{
	if (COLLIDER2D_TYPE::RECT == _pLeftCol->GetCollider2DType()
		&& COLLIDER2D_TYPE::RECT == _pRightCol->GetCollider2DType())
	{
		return CollisionRvsR(_pLeftCol, _pRightCol);
	}

	else if (COLLIDER2D_TYPE::CIRCLE == _pLeftCol->GetCollider2DType()
		&& COLLIDER2D_TYPE::CIRCLE == _pRightCol->GetCollider2DType())
	{
		return CollisionCvsC(_pLeftCol, _pRightCol);
	}

	return false;
}

bool CCollisionMgr::CollisionRvsR(CCollider2D* _pLeftCol, CCollider2D* _pRightCol)
{
	const Matrix& matColLeft = _pLeftCol->GetmatColWorld();
	const Matrix& matColRight = _pRightCol->GetmatColWorld();

	// 0 -- 1
	// |    |
	// 3 -- 2
	//로컬메쉬를 설정해놓고 , 매번 쓸거니까 static으로 수정못하게 박아놓음 
	static const Vec3 vLocalMesh[4] = { Vec3(-0.5f, 0.5f, 0.f)
		, Vec3(0.5f, 0.5f, 0.f)
		, Vec3(0.5f, -0.5f, 0.f)
		, Vec3(-0.5f, -0.5f, 0.f) };

	// 두 충돌체를 이은 벡터 
	Vec2 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matColLeft) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matColRight);

	Vec2 vLeft0 = XMVector3TransformCoord(vLocalMesh[0], matColLeft);
	Vec2 vLeft1 = XMVector3TransformCoord(vLocalMesh[1], matColLeft);
	Vec2 vLeft3 = XMVector3TransformCoord(vLocalMesh[3], matColLeft);
	Vec2 vRight0 = XMVector3TransformCoord(vLocalMesh[0], matColRight);
	Vec2 vRight1 = XMVector3TransformCoord(vLocalMesh[1], matColRight);
	Vec2 vRight3 = XMVector3TransformCoord(vLocalMesh[3], matColRight);

	Vec2 vAxis[4] = {}; // a, b 벡터
	vAxis[0] = vLeft1 - vLeft0;
	vAxis[1] = vLeft3 - vLeft0;
	vAxis[2] = vRight1 - vRight0;
	vAxis[3] = vRight3 - vRight0;

	Vec2 vProjAxis[4] = {}; 
	for (int i = 0; i < 4; ++i)
	{
		vProjAxis[i] = vAxis[i];
		vProjAxis[i].Normalize(); 	// 투영할 축
	}

	for (int i = 0; i < 4; ++i)
	{
		float fProjDist = 0.f;
		for (int j = 0; j < 4; ++j) //한 축에 대해 4번 투영
		{			
			fProjDist += abs(vProjAxis[i].Dot(vAxis[j])) / 2.f; 
		}
		if (fProjDist < abs(vProjAxis[i].Dot(vCenter)))
		{
			return false;
		}
	}
	return true;
}

bool CCollisionMgr::CollisionCvsC(CCollider2D* _pLeftCol, CCollider2D* _pRightCol)
{
	_pLeftCol->GetmatColWorld();
	_pRightCol->GetmatColWorld();

	return false;
}


void CCollisionMgr::CollisionCheckClear()
{
	memset(m_arrCheck, 0, sizeof(UINT) * MAX_LAYER);
}

void CCollisionMgr::CollisionCheck(int _iLeft, int _iRight)
{
	int iRow = -1;
	int iCol = -1;

	if ((UINT)_iLeft < (UINT)_iRight)
	{
		iRow = (UINT)_iLeft;
		iCol = (UINT)_iRight;
	}
	else
	{
		iRow = (UINT)_iRight;
		iCol = (UINT)_iLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= 1 << iCol;
	}
}
