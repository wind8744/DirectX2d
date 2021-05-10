#pragma once
#include "CEntity.h"

class CStructuredBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer>                m_pSB;
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;          // ���̴� ���ҽ� ��(���ҽ� ���ε� �뵵)
    ComPtr<ID3D11UnorderedAccessView>   m_pUAV;          // RWStructuredbuffer(register u) ���ε�

    UINT                                m_iElementSize;  // ���� ��� ������
    UINT                                m_iElementCount; // ���� ��� ����

    int                                 m_iSRVRecentNum;    // �ֱ� ���ε��� �������� ��ȣ
    int                                 m_iUAVRecentNum;

public:
    void Create(UINT _iElementSize, UINT _iElementCount, void* _pSysMem);
    void CreateRW(UINT _iElementSize, UINT _iElementCount, void* _pSysMem);
    void UpdateData(UINT _iRegisterNum);
    void UpdateDataRW(UINT _iRegisterNum);

    void Clear();
    void ClearRW();

    void SetData(void* _pData, UINT _iElementSize, UINT _iElementCount);

    int GetElementSize() { return m_iElementSize; }
    int GetElementCount() { return m_iElementCount; }
    int GetBufferSize() { return m_iElementSize * m_iElementCount; }

public:
    CLONE_DISABLE(CStructuredBuffer);
    virtual void SaveToScene(FILE* _pFile) { assert(nullptr); }
    virtual void LoadFromScene(FILE* _pFile) { assert(nullptr); }

public:
    CStructuredBuffer();
    ~CStructuredBuffer();
};

