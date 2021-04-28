#pragma once
#include <Engine\CScript.h>


enum class PLAYER_STATE
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    IDLE,
    STOP,
    ATTACK,
    SKILL,
    PUSH,
    BREAK,
    ITEM,
    NONE
};

typedef struct tile_info
{
    bool IsObj;                                 //Ÿ���̸� false object�̸� true
    bool IsPush;                                //�м��ִ� ������Ʈ?
    bool IsBlock;                               //��ֹ�?
    void TileInit() { IsObj = false; IsPush = false; } //�ʱ�ȭ

}TILE_INFO;


class CPlayerScript :
    public CScript
{
private:
    Ptr<CTexture>       m_pPlayerTex;           //�÷��̾� tex
    PLAYER_STATE        m_PlayerState;          //�÷��̾��� ���� ����
    KEY_TYPE            m_PlayerKey;            //����Ű

    //vector<tile_info*>& m_vecTileInfo;        //���� ���� Ÿ�� ���� vector (��������� �޾ƿ�)
    vector<tile_info>   m_vecTileInfo;          //temp

    int                 m_iTileX;               //�÷��̾� Ÿ�� X pos
    int                 m_iTileY;               //�÷��̾� Ÿ�� Y pos

    int                 m_iMapCol;              //���� ���� ũ��
    int                 m_iMapRow;

private:
    Ptr<CPrefab>        m_pMissilePrefab;
    int                 m_iData;
    int                 m_fData;
    Vec2                m_v2Data;
    Vec4                m_v4Data;



public:
    virtual void awake();
    virtual void update();

private:
    void CreateMissile();   
    void UpdateTilePos();
    
    void InputKey();
    void PlayAnimation();
    void SetState();
    void SetCurPlayerKey();
    void PlayerMove();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CPlayerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CPlayerScript();
    ~CPlayerScript();
};

