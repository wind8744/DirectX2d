#pragma once
#include "D:\2dÆ÷Æú\Directx\External\Include\Engine\CScript.h"


enum class EventType {
    TriggerOn,

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
    bool GetTirrger() { return b_TriggerOn; }

public:
    CLONE(CObjEvent);
    CObjEvent();
    ~CObjEvent();

};

