#pragma once
#include <Engine\CScript.h>

enum class EventType {
    TriggerOn,
    TriggerOrderOn
};
class CObjEventScript :
    public CScript
{
private:
    vector<CObjEventScript>   ChildTrigger;
    bool                b_TriggerOn;
    EventType           E_EvnetType;

public:
    virtual void awake();
    virtual void update();

public:
    bool GetTrigger() { return b_TriggerOn; }
    void SetTrigger(bool _Trigger) { b_TriggerOn = b_TriggerOn; }

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

public:
    CLONE(CObjEventScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CObjEventScript();
    ~CObjEventScript();
};
