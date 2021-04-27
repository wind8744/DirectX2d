#include "pch.h"
#include "ListGUI.h"

#include "CImGUIMgr.h"

ListGUI::ListGUI()
    : m_iSelIdx(0)
    , m_pInst(nullptr)
    , m_pSelectFunc(nullptr)
{

}

ListGUI::~ListGUI()
{

}

void ListGUI::render()
{	
    bool bOpen = true;	
    ImGui::OpenPopup("ListGUI");
    if (ImGui::BeginPopupModal("ListGUI", &bOpen))
    {
        ImGui::Text(m_strCaption.c_str());
        if (ImGui::BeginListBox("##listbox", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (size_t n = 0; n < m_vecItem.size(); n++)
            {
                const bool is_selected = (m_iSelIdx == n);
                if (ImGui::Selectable(m_vecItem[n].c_str(), is_selected))
                {
                    m_iSelIdx = n;
                }

                // �������� ����Ŭ�� �� ���
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
                {
                    m_strSel = m_vecItem[m_iSelIdx];

                    // ���� �ݹ��� ��ϵ� ���
                    if (m_pSelectFunc && m_pInst)
                    {
                        tGUIEvent2 event = {};
                        event.pInst = m_pInst;
                        event.pFunc = (EVENT_FUNC_PARAM_2)m_pSelectFunc;
                        event.pData[0] = (void*)this;
                        event.pData[1] = (void*)m_strSel.c_str();
                        CImGUIMgr::GetInst()->AddCallBackEvent(event);

                        m_pInst = nullptr;
                        m_pSelectFunc = nullptr;
                    }

                    Clear();
                    DeActivate();
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndListBox();
        }
      
        ImGui::EndPopup();
    }

    m_bOpen = bOpen;

    // ListGui ���� == ���
    if (m_bOpen == false)
    {
        ImGui::CloseCurrentPopup();
        Clear();
        DeActivate();
    }
}