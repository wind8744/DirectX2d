#pragma once
#include <Engine\CScript.h>



typedef struct tile_info
{
    bool IsObj;                                 //타일이면 false object이면 true
    bool IsPush;                                //밀수있는 오브젝트?
    bool IsBlock;                               //장애물?
    void TileInit() { IsObj = false; IsPush = false; } //초기화

}TILE_INFO;


class CPlayerScript :
    public CScript
{
private:
    Ptr<CTexture>       m_pPlayerTex;           //플레이어 tex
    PLAYER_STATE        m_PlayerState;          //플레이어의 현재 상태
    PLAYER_STATE        m_StopPlayerState;      //충돌 시 마지막 눌린 상태
    KEY_TYPE            m_PlayerKey;            //눌린키

    //vector<tile_info*>& m_vecTileInfo;        //현재 씬의 타일 정보 vector (현재씬에서 받아옴)
    vector<tile_info>   m_vecTileInfo;          //temp

    int                 m_iTileX;               //플레이어 타일 X pos
    int                 m_iTileY;               //플레이어 타일 Y pos

    int                 m_iMapCol;              //현재 맵의 크기
    int                 m_iMapRow;

private:
    Ptr<CPrefab>        m_pMissilePrefab;
    int                 m_iData;
    int                 m_fData;
    Vec2                m_v2Data;
    Vec4                m_v4Data;

public:
    //GET SET
    PLAYER_STATE GetStopPlayerState() { return m_StopPlayerState; } //key로 바꿀?
    PLAYER_STATE GetPlayerState() { return m_PlayerState; }
    int GetPlayerTileX() { return m_iTileX; }
    int GetPlayerTileY() { return m_iTileY; }


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

