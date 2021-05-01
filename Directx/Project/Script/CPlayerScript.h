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


class CPlayerScript :
    public CScript
{
private:
    bool                m_IsOnCol;              //�浹��?
    Ptr<CTexture>       m_pPlayerTex;           //�÷��̾� tex
    
    CScript*            m_pTarScript;           //�ε��� Ÿ�� ��ũ��Ʈ
    CGameObject*        m_pTarObj;              //�ε��� Ÿ�� ���� ������Ʈ

    PLAYER_STATE        m_eCurState;            //�÷��̾��� ���� ����
    PLAYER_STATE        m_ePrevState;           //���� ����
    DIR                 m_eCurDir;              //���� ����
    DIR                 m_ePreDir;              //���� ����

    UINT                m_iItem;                //������ �ִ� ������ ( 0 : ���� 1 : ��ź  2 : ȭ�� )
    UINT                m_iHP;                  //�÷��̾� ü��
    float               m_fPlayerSpeed;         //�÷��̾� ���ǵ�
    float               m_fAtime;               //�����ð�

    //vector<tile_info*>& m_vecTileInfo;        //���� ���� Ÿ�� ���� vector (��������� �޾ƿ�)
    //vector<tile_info>   m_vecTileInfo;        //temp

    int                 m_iTileX;               //�÷��̾� Ÿ�� X pos
    int                 m_iTileY;               //�÷��̾� Ÿ�� Y pos

    int                 m_iMapCol;              //���� ���� ũ��
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

