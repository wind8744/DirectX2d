#include "pch.h"
#include "extern.h"

tTransform g_transform = {};
tGlobalValue g_global = {};

pSaveFunc g_pScriptSave = nullptr;
pLoadFunc g_pScriptLoad = nullptr;

const wchar_t* g_szResName[(UINT)RES_TYPE::END] =
{
	L"PREFAB",
	L"MATERIAL",
	L"SHADER",
	L"MESH",
	L"TEXTURE",
	L"SOUND"
};