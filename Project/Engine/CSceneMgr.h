#pragma once

#include "CSingleton.h"

class CScene;
class CGameObject;
class CSceneMgr
	: public CSingleton<CSceneMgr>
{
	SINGLE(CSceneMgr);
private:
	CScene* m_pCurScene;


	
	Character    m_PartyList[4];
public:
	void init();
	void progress();
	
public:
	CScene* GetCurScene() { return m_pCurScene; }

	CGameObject* FindPlayer(int _num);

	CGameObject* FindObjectByName(const wstring& _strName);

	void ChangeScene(CScene* _pNextScene);

	Character GetPartyListNum(int _Num) { return m_PartyList[_Num]; }
	void     PlayerListChange(int _Num1, int _Num2);
	friend class CEventMgr;
};

