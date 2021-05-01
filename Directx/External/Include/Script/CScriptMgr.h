#pragma once

#include <vector>
#include <string>

enum class SCRIPT_TYPE
{
	BARBEDBLOCKSCRIPT,
	BLOCKSCRIPT,
	BOMBFLOWERSCRIPT,
	BOMBSCRIPT,
	BREAKABLESMALLSTONESCRIPT,
	BREAKABLESTONESCRIPT,
	CAMERASCRIPT,
	FIREBOWLSCRIPT,
	FIREWOODSCRIPT,
	MAPSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	OBJEVENTSCRIPT,
	PLAYERSCRIPT,
	PUSHSMALLSTONESCRIPT,
	PUSHSTONESCRIPT,
	REDBUTTONSCRIPT,
	SPEEDUPSCRIPT,
	STONEDOORSCRIPT,
	TILECOLLSION,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
