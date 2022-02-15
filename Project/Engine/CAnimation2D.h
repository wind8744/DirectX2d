#pragma once
#include "CEntity.h"

#include "CTexture.h"

class CAnimator2D;

struct tAnimFrm
{    
    Vec2            vLT;
    Vec2            vStep;
    float           fDuration;
};

class CAnimation2D :
    public CEntity
{
private:
    CAnimator2D*        m_pAnimator;
    vector<tAnimFrm>    m_vecFrm;
    Ptr<CTexture>       m_pTex;
    int                 m_iCurFrm;

    float               m_fAccTime;
    bool                m_bFinish;
    bool                m_bReversal;
public:
    void lateupdate();


public:
    void Create(const wstring& _strAnimName, Ptr<CTexture> _pAnimTex, Vec2 _vLeftTop, Vec2 _vStep, int _iFrameCount, float _fDuration);
    const tAnimFrm& GetFrame(int _iFrmIdx) { return m_vecFrm[_iFrmIdx]; }
    const tAnimFrm& GetCurFrame() { return m_vecFrm[m_iCurFrm]; }
    void SetFrame(UINT _iFrmIdx, const tAnimFrm& _frm) 
    { 
        assert(m_vecFrm.size() > _iFrmIdx);
        m_vecFrm[_iFrmIdx] = _frm;
    }

    Ptr<CTexture> GetTex() { return m_pTex; }
    bool IsFinish() { return m_bFinish; }
    bool IsReversal() { return m_bReversal; }
    void SetFrameIndex(UINT _iFrmIdx, bool _bActive)
    {
        assert(m_vecFrm.size() > _iFrmIdx);
        m_iCurFrm = _iFrmIdx;
        m_bFinish = !_bActive;
        m_fAccTime = 0.f;
    }
    
    float GetAnimFrmRatio();
    int   GetFrmSize() { return (int)m_vecFrm.size(); }
public:
    CLONE(CAnimation2D);
    void SaveToScene(FILE* _pFile);
    void LoadFromScene(FILE* _pFile);

public:
    CAnimation2D();
    ~CAnimation2D();

    friend class CAnimator2D;
};

