#pragma once

#include "CSingleton.h"

class CCore
	: public CSingleton<CCore>
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	POINT		m_ptWndRes;		// ���� ������ �ػ�

public:
	int init(HWND _hWnd, POINT _ptResolution, bool _bWindow = true);
	void progress();

public:
	HWND GetWndHwnd() { return m_hWnd; }
	POINT GetWndResolution() { return m_ptWndRes; }
};

