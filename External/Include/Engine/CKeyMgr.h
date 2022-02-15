#pragma once

enum class KEY_STATE
{
	TAP,  // �� ���ȴ�.
	HOLD, // �������� ������ ���ݵ� �����ִ�
	AWAY, // �� �ô�
	NONE  // �ƹ��͵� �ƴ�
};

enum class KEY_TYPE
{
	KEY_W, // = 0
	KEY_S, // = 1
	KEY_A, // = 2
	KEY_D, // = 3
	KEY_Z, // = 3

	SPACE,
	ENTER,

	LBTN,
	RBTN,

	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,

	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,

	END,
};

struct tKeyData
{
	KEY_STATE	eState;
	bool		bPress;
};

#include "CSingleton.h"

class CKeyMgr : 
	public CSingleton<CKeyMgr>
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyData>	m_vecKey;
	POINT				m_ptMousePos;
	POINT				m_ptPrevMousePos;

	Vec2				m_vMouseDir;

public:
	void init();
	void update();

public:
	POINT GetMousePos() { return m_ptMousePos; }
	POINT GetPrevMousePos() { return m_ptPrevMousePos; }
	Vec2 GetMouseDir() { return m_vMouseDir; }

public:
	KEY_STATE GetKeyState(KEY_TYPE _eType)
	{
		return m_vecKey[(UINT)_eType].eState;
	}
};

