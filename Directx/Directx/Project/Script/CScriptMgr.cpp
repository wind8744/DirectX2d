#include "pch.h"
#include "CScriptMgr.h"

#include "CBarbedBlockScript.h"
#include "CBlockScript.h"
#include "CBombFlowerScript.h"
#include "CBombScript.h"
#include "CBreakableSmallStoneScript.h"
#include "CBreakableStoneScript.h"
#include "CCameraScript.h"
#include "CElecBlockScript.h"
#include "CElecChildScript.h"
#include "CElecTowerScript.h"
#include "CEndBlockScript.h"
#include "CFireBowlScript.h"
#include "CFireWoodScript.h"
#include "CJumpUpScript.h"
#include "CMapScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CObjEventScript.h"
#include "CPlayerPosSetScript.h"
#include "CPlayerScript.h"
#include "CPushSmallStoneScript.h"
#include "CPushStoneScript.h"
#include "CRedButtonScript.h"
#include "CSpeedUpScript.h"
#include "CStoneDoorScript.h"
#include "CTargetToAuto.h"
#include "CTileCollsion.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBarbedBlockScript");
	_vec.push_back(L"CBlockScript");
	_vec.push_back(L"CBombFlowerScript");
	_vec.push_back(L"CBombScript");
	_vec.push_back(L"CBreakableSmallStoneScript");
	_vec.push_back(L"CBreakableStoneScript");
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CElecBlockScript");
	_vec.push_back(L"CElecChildScript");
	_vec.push_back(L"CElecTowerScript");
	_vec.push_back(L"CEndBlockScript");
	_vec.push_back(L"CFireBowlScript");
	_vec.push_back(L"CFireWoodScript");
	_vec.push_back(L"CJumpUpScript");
	_vec.push_back(L"CMapScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CObjEventScript");
	_vec.push_back(L"CObjEventScriptMgr");
	_vec.push_back(L"CPlayerPosSetScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPushSmallStoneScript");
	_vec.push_back(L"CPushStoneScript");
	_vec.push_back(L"CRedButtonScript");
	_vec.push_back(L"CScriptMgr");
	_vec.push_back(L"CSpeedUpScript");
	_vec.push_back(L"CStoneDoorScript");
	_vec.push_back(L"CTargetToAuto");
	_vec.push_back(L"CTileCollsion");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBarbedBlockScript" == _strScriptName)
		return new CBarbedBlockScript;
	if (L"CBlockScript" == _strScriptName)
		return new CBlockScript;
	if (L"CBombFlowerScript" == _strScriptName)
		return new CBombFlowerScript;
	if (L"CBombScript" == _strScriptName)
		return new CBombScript;
	if (L"CBreakableSmallStoneScript" == _strScriptName)
		return new CBreakableSmallStoneScript;
	if (L"CBreakableStoneScript" == _strScriptName)
		return new CBreakableStoneScript;
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CElecBlockScript" == _strScriptName)
		return new CElecBlockScript;
	if (L"CElecChildScript" == _strScriptName)
		return new CElecChildScript;
	if (L"CElecTowerScript" == _strScriptName)
		return new CElecTowerScript;
	if (L"CEndBlockScript" == _strScriptName)
		return new CEndBlockScript;
	if (L"CFireBowlScript" == _strScriptName)
		return new CFireBowlScript;
	if (L"CFireWoodScript" == _strScriptName)
		return new CFireWoodScript;
	if (L"CJumpUpScript" == _strScriptName)
		return new CJumpUpScript;
	if (L"CMapScript" == _strScriptName)
		return new CMapScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CObjEventScript" == _strScriptName)
		return new CObjEventScript;
	if (L"CPlayerPosSetScript" == _strScriptName)
		return new CPlayerPosSetScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPushSmallStoneScript" == _strScriptName)
		return new CPushSmallStoneScript;
	if (L"CPushStoneScript" == _strScriptName)
		return new CPushStoneScript;
	if (L"CRedButtonScript" == _strScriptName)
		return new CRedButtonScript;
	if (L"CSpeedUpScript" == _strScriptName)
		return new CSpeedUpScript;
	if (L"CStoneDoorScript" == _strScriptName)
		return new CStoneDoorScript;
	if (L"CTargetToAuto" == _strScriptName)
		return new CTargetToAuto;
	if (L"CTileCollsion" == _strScriptName)
		return new CTileCollsion;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BARBEDBLOCKSCRIPT:
		return new CBarbedBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::BLOCKSCRIPT:
		return new CBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBFLOWERSCRIPT:
		return new CBombFlowerScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBSCRIPT:
		return new CBombScript;
		break;
	case (UINT)SCRIPT_TYPE::BREAKABLESMALLSTONESCRIPT:
		return new CBreakableSmallStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::BREAKABLESTONESCRIPT:
		return new CBreakableStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECBLOCKSCRIPT:
		return new CElecBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECCHILDSCRIPT:
		return new CElecChildScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECTOWERSCRIPT:
		return new CElecTowerScript;
		break;
	case (UINT)SCRIPT_TYPE::ENDBLOCKSCRIPT:
		return new CEndBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::FIREBOWLSCRIPT:
		return new CFireBowlScript;
		break;
	case (UINT)SCRIPT_TYPE::FIREWOODSCRIPT:
		return new CFireWoodScript;
		break;
	case (UINT)SCRIPT_TYPE::JUMPUPSCRIPT:
		return new CJumpUpScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPSCRIPT:
		return new CMapScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::OBJEVENTSCRIPT:
		return new CObjEventScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERPOSSETSCRIPT:
		return new CPlayerPosSetScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::PUSHSMALLSTONESCRIPT:
		return new CPushSmallStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::PUSHSTONESCRIPT:
		return new CPushStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::REDBUTTONSCRIPT:
		return new CRedButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::SPEEDUPSCRIPT:
		return new CSpeedUpScript;
		break;
	case (UINT)SCRIPT_TYPE::STONEDOORSCRIPT:
		return new CStoneDoorScript;
		break;
	case (UINT)SCRIPT_TYPE::TARGETTOAUTO:
		return new CTargetToAuto;
		break;
	case (UINT)SCRIPT_TYPE::TILECOLLSION:
		return new CTileCollsion;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BARBEDBLOCKSCRIPT:
		return L"CBarbedBlockScript";
		break;

	case SCRIPT_TYPE::BLOCKSCRIPT:
		return L"CBlockScript";
		break;

	case SCRIPT_TYPE::BOMBFLOWERSCRIPT:
		return L"CBombFlowerScript";
		break;

	case SCRIPT_TYPE::BOMBSCRIPT:
		return L"CBombScript";
		break;

	case SCRIPT_TYPE::BREAKABLESMALLSTONESCRIPT:
		return L"CBreakableSmallStoneScript";
		break;

	case SCRIPT_TYPE::BREAKABLESTONESCRIPT:
		return L"CBreakableStoneScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
		break;

	case SCRIPT_TYPE::ELECBLOCKSCRIPT:
		return L"CElecBlockScript";
		break;

	case SCRIPT_TYPE::ELECCHILDSCRIPT:
		return L"CElecChildScript";
		break;

	case SCRIPT_TYPE::ELECTOWERSCRIPT:
		return L"CElecTowerScript";
		break;

	case SCRIPT_TYPE::ENDBLOCKSCRIPT:
		return L"CEndBlockScript";
		break;

	case SCRIPT_TYPE::FIREBOWLSCRIPT:
		return L"CFireBowlScript";
		break;

	case SCRIPT_TYPE::FIREWOODSCRIPT:
		return L"CFireWoodScript";
		break;

	case SCRIPT_TYPE::JUMPUPSCRIPT:
		return L"CJumpUpScript";
		break;

	case SCRIPT_TYPE::MAPSCRIPT:
		return L"CMapScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::OBJEVENTSCRIPT:
		return L"CObjEventScript";
		break;

	case SCRIPT_TYPE::PLAYERPOSSETSCRIPT:
		return L"CPlayerPosSetScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::PUSHSMALLSTONESCRIPT:
		return L"CPushSmallStoneScript";
		break;

	case SCRIPT_TYPE::PUSHSTONESCRIPT:
		return L"CPushStoneScript";
		break;

	case SCRIPT_TYPE::REDBUTTONSCRIPT:
		return L"CRedButtonScript";
		break;

	case SCRIPT_TYPE::SPEEDUPSCRIPT:
		return L"CSpeedUpScript";
		break;

	case SCRIPT_TYPE::STONEDOORSCRIPT:
		return L"CStoneDoorScript";
		break;

	case SCRIPT_TYPE::TARGETTOAUTO:
		return L"CTargetToAuto";
		break;

	case SCRIPT_TYPE::TILECOLLSION:
		return L"CTileCollsion";
		break;

	}
	return nullptr;
}