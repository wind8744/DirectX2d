#include "pch.h"
#include "MaptoolGUI.h"
#include <Script\CMapScript.h>
#include <Engine\CTexture.h>
#include <Engine\CResMgr.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScript.h>
#include <Engine\CScene.h>
#include <Engine\CKeyMgr.h>
MaptoolGUI::MaptoolGUI() :
	m_Map(nullptr),
	m_x(0),
	m_y(0),
	m_size(0),
	m_SetIndex(0.f,0.f)
{
}

MaptoolGUI::~MaptoolGUI()
{
}
void MaptoolGUI::init()
{
	m_TileTex = CResMgr::GetInst()->FindRes<CTexture>(L"TILE");
	if (nullptr == m_TileTex)
		m_TileTex = CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");

	m_Map =(CMapScript*)CSceneMgr::GetInst()->GetCurScene()->FindObjectByName(L"Background")->GetScript();
	;
	m_x = m_TileTex.Get()->Width() / TileSize_X;
	m_y = m_TileTex.Get()->Height() / TileSize_Y;
	m_size = m_Map->GetTileSIze();
}
void MaptoolGUI::update()
{
	Vec3 Pos = m_Map->GetGameObject()->Transform()->GetLocalPos();
	Vec3 Scale = m_Map->GetGameObject()->Transform()->GetLocalScale();
	if (KEY_TAP(KEY_TYPE::LBTN))
	{
		POINT _Pos = CKeyMgr::GetInst()->GetPrevMousePos();
		_Pos.x = _Pos.x - 800;
		_Pos.y = -_Pos.y + 450;
		if (_Pos.x > Pos.x - Scale.x / 2 && _Pos.x< Pos.x + Scale.x / 2 &&
			_Pos.y > Pos.y - Scale.y / 2 && _Pos.y < Pos.y + Scale.y / 2)
		{
			int x = (_Pos.x - (Pos.x - Scale.x/2)) / TileSize_X;
			int y = ((Pos.y + Scale.y/2)-_Pos.y) / TileSize_Y;
			m_Map->SetTile(x, y, m_SetIndex);
		}
	}
	
}

void MaptoolGUI::render()
{
	static int Data1 = 0;
	static int Data2 = 0;
	bool bOpen = true;

	ImGui::Begin("##Maptool", &bOpen);

	ImGui::PushItemWidth(50);
	ImGui::Text("Tile Size"); ImGui::SameLine(); ImGui::InputInt("##Size1", &Data1, 0);
	ImGui::SameLine();
	ImGui::InputInt("##Size2", &Data2, 0);
	ImGui::SameLine();
	if (ImGui::Button("Set", { 50, 20 }))
	{
		m_Map->SetTileNum(Data1,Data2);
	}

	float sizex = (float)TileSize_X;
	float sizey = (float)TileSize_Y;
	Vec2 teszie = Vec2(sizex, sizey);				// Texture render size
	Vec4 tint_col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	Vec4 bg_col = Vec4(1.0f, 1.0f, 1.0f, 0.f); // 50% opaque white
	for (int i = 0; i < m_y; i++)
	{
		for (int l = 0; l < m_x; l++)
		{
			ImGui::ImageButton(m_TileTex.Get()->GetSRV().Get(), teszie, Vec2(l *m_Map->GetTileUvX(), i * m_Map->GetTileUvY()), Vec2((l + 1) * m_Map->GetTileUvX(), (i + 1) * m_Map->GetTileUvY()), 1, bg_col, tint_col);
			if (ImGui::IsItemClicked()) {
				m_SetIndex = Vec2(l, i);
			}
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
	
		

	ImGui::GetWindowSize();

	ImGui::End();
}
