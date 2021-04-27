#include "pch.h"
#include "CScriptMgr.h"

#include "CCameraScript.h"
#include "CMapScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CObjEventScript.h"
#include "CPlayerScript.h"
#include "CRedButtonScript.h"
#include "CStoneDoorScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CMapScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CObjEventScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CRedButtonScript");
	_vec.push_back(L"CStoneDoorScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CMapScript" == _strScriptName)
		return new CMapScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CObjEventScript" == _strScriptName)
		return new CObjEventScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CRedButtonScript" == _strScriptName)
		return new CRedButtonScript;
	if (L"CStoneDoorScript" == _strScriptName)
		return new CStoneDoorScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
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
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::REDBUTTONSCRIPT:
		return new CRedButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::STONEDOORSCRIPT:
		return new CStoneDoorScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
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

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::REDBUTTONSCRIPT:
		return L"CRedButtonScript";
		break;

	case SCRIPT_TYPE::STONEDOORSCRIPT:
		return L"CStoneDoorScript";
		break;

	}
	return nullptr;
}