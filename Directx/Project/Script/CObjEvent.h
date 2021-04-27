#pragma once
#include <Engine\CScript.h>


enum class EventType {
    TriggerOn,
    TriggerOrderOn
};
class CObjEvent :
    public CScript
{
private:
    vector<CObjEvent>   ChildTrigger;
    bool                b_TriggerOn;
    EventType           E_EvnetType;
public:
    virtual void awake();
    virtual void update();

public:
    bool GetTirrger() { return b_TriggerOn;}
    void SetTirrger(bool _Trigger) { b_TriggerOn = b_TriggerOn; }
public:
    CLONE(CObjEvent);
    CObjEvent();
    ~CObjEvent();

};

