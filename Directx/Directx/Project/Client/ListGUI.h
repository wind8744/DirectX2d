#pragma once
#include "GUI.h"

class ListGUI;

typedef void (GUI::* LIST_SELECT_ITEM)(const ListGUI* _data1, const char* _data2);

class ListGUI :
    public GUI
{
private:
    string            m_strCaption;
    vector<string>    m_vecItem;
    string            m_strSel;
    int               m_iSelIdx;
    bool              m_bOpen;

    // �׸� ���� ��, ȣ���� �Լ��� ��ü
    LIST_SELECT_ITEM  m_pSelectFunc;
    GUI*              m_pInst;

public:
    virtual void render();

public:
    void SetCaption(const string& _str) { m_strCaption = _str; }
    const string& GetCaption() { return m_strCaption; }
    void AddItem(string _strItem){m_vecItem.push_back(_strItem);}
    void Clear() { m_vecItem.clear(); m_iSelIdx = -1; }

    bool IsCancle() {return !m_bOpen;}
    const string& GetSelect() { return m_strSel; };

    void SetSelectCallBack(GUI* _Inst, LIST_SELECT_ITEM _pFunc)
    {
        m_pInst = _Inst;
        m_pSelectFunc = _pFunc;
    }


public:
    ListGUI();
    ~ListGUI();
};

