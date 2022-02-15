#pragma once
#include <Engine\CScript.h>


enum class ObjType {
    Player,
    Monster,
    None
}; //����� ����� ������






//�����̻� ����
enum class CC {
    DOWN,
    AIRBORNE,
    INJURE,
    NONE
};
class CHitScript:
	public CScript
{
private:
    ObjType   m_Type;
    int       m_iDamage; //������
    CC        m_CCType;  //�����̻� Ÿ��
    int       m_CCValue; //�����̻� ��ġ

    bool      m_bHitDeleteOn; //�浹�Ǹ� ��������� �ƴ���
    bool      m_bDamageColEnter; //true �����϶� ������ false�� on�϶� ������
    float     m_fDamageTime;  //���ʸ��� ������ ������
    float     m_fTime;



    bool      m_IsDead;
 


    bool      m_Player; //���������


    Ptr<CPrefab>             m_effect;  //��Ÿ




public:
    virtual void update();

public:
    GET_SET(int, iDamage);
    GET_SET(int, CCValue);
    GET_SET(ObjType, Type);
    GET_SET(CC, CCType);
    GET_SET(bool, bHitDeleteOn);
    GET_SET(bool, bDamageColEnter);
    GET_SET(float, fDamageTime);
    GET_SET(bool, Player);


    void Seteffect(Ptr<CPrefab> _Prefab) { m_effect = _Prefab; }

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CLONE(CHitScript);
    CHitScript();
    ~CHitScript();


};

