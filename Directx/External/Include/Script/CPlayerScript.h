#pragma once
#include <Engine\CScript.h>

//typedef struct tile_info
//{
//    bool IsObj;                                 //Ÿ���̸� false object�̸� true
//    bool IsPush;                                //�м��ִ� ������Ʈ?
//    bool IsBlock;                               //��ֹ�?
//    void TileInit() { IsObj = false; IsPush = false; } //�ʱ�ȭ
//
//}TILE_INFO;

//enum class PLAYER_STATE
//{
//    MOVE,
//    STOP,
//    IDLE,
//    ATTACK,
//    SKILL,
//    PUSH,
//    BREAK,
//    ITEM,
//    NONE
//};

//enum class DIR
//{
//    UP,
//    DOWN,
//    RIGHT,
//    LEFT
//};
class CPlayerScript :
    public CScript
{
private:
    bool                m_IsOnCol;              //�浹��?
    Ptr<CTexture>       m_pPlayerTex;           //�÷��̾� tex

    //������ ��
    PLAYER_STATE        m_eCurState;            //�÷��̾��� ���� ����
    PLAYER_STATE        m_ePrevState;           //���� ����
    DIR                 m_eCurDir;              //���� ����
    DIR                 m_ePreDir;              //���� ����

    UINT                m_iHP;                  //�÷��̾� ü��
    float               m_fPlayerSpeed;         //�÷��̾� ���ǵ�

    //vector<tile_info*>& m_vecTileInfo;        //���� ���� Ÿ�� ���� vector (��������� �޾ƿ�)
    //vector<tile_info>   m_vecTileInfo;        //temp

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
    //GET SET
    //PLAYER_STATE GetStopPlayerState() { return m_StopPlayerState; } //key�� �ٲ�?
    //void SetStopPlayerState(PLAYER_STATE _stopstate) { m_StopPlayerState = _stopstate; } //key�� �ٲ�?

    PLAYER_STATE GetPlayerState() { return m_eCurState; }
    void SetPlayerState(PLAYER_STATE _state) { m_eCurState = _state; }

    DIR GetPlayerDir() { return m_eCurDir; }
    void SetPlayerDir(DIR _key) { m_eCurDir = _key; }

    float GetPlayerSpeed() { return m_fPlayerSpeed; }
    void SetPlayerSpeed(float _speed) { m_fPlayerSpeed = _speed; }

    int GetPlayerTileX() { return m_iTileX; }
    int GetPlayerTileY() { return m_iTileY; }


public:
    virtual void awake();
    virtual void update();

private:
    void CreateMissile();   
    void UpdateTilePos();
    
    void CheckState();
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

