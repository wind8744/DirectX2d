#pragma once
#include <Engine\CScript.h>

//typedef struct tile_info
//{
//    bool IsObj;                                 //타일이면 false object이면 true
//    bool IsPush;                                //밀수있는 오브젝트?
//    bool IsBlock;                               //장애물?
//    void TileInit() { IsObj = false; IsPush = false; } //초기화
//
//}TILE_INFO;


class CPlayerScript :
    public CScript
{
private:
    bool                m_IsOnCol;              //충돌중?
    Ptr<CTexture>       m_pPlayerTex;           //플레이어 tex
    
    CScript*            m_pTarScript;           //부딪힌 타겟 스크립트
    CGameObject*        m_pTarObj;              //부딪힌 타겟 게임 오브젝트

    PLAYER_STATE        m_eCurState;            //플레이어의 현재 상태
    PLAYER_STATE        m_ePrevState;           //이전 상태
    DIR                 m_eCurDir;              //현재 방향
    DIR                 m_ePreDir;              //이전 방향

    UINT                m_iItem;                //가지고 있는 아이템 ( 0 : 없음 1 : 폭탄  2 : 화로 )
    UINT                m_iHP;                  //플레이어 체력
    float               m_fPlayerSpeed;         //플레이어 스피드
    float               m_fAtime;               //누적시간

    //vector<tile_info*>& m_vecTileInfo;        //현재 씬의 타일 정보 vector (현재씬에서 받아옴)
    //vector<tile_info>   m_vecTileInfo;        //temp

    int                 m_iTileX;               //플레이어 타일 X pos
    int                 m_iTileY;               //플레이어 타일 Y pos

    int                 m_iMapCol;              //현재 맵의 크기
    int                 m_iMapRow;

private:
    Ptr<CPrefab>        m_pMissilePrefab;

public:
    //GET SET
    PLAYER_STATE GetPlayerState() { return m_eCurState; }
    void SetPlayerState(PLAYER_STATE _state) { m_eCurState = _state; }
    PLAYER_STATE GetPlayerPrevState() { return m_ePrevState; }
    //void SetPlayerPrevState(PLAYER_STATE _state) { m_ePrevState = _state; }

    DIR GetPlayerDir() { return m_eCurDir; }
    void SetPlayerDir(DIR _key) { m_eCurDir = _key; }

    float GetPlayerSpeed() { return m_fPlayerSpeed; }
    void SetPlayerSpeed(float _speed) { m_fPlayerSpeed = _speed; }

    int GetPlayerTileX() { return m_iTileX; }
    int GetPlayerTileY() { return m_iTileY; }

    UINT GetPlayerItemNum() { return m_iItem; }
    void SetPlayerItemNum(UINT _item) { m_iItem = _item; }


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

