#pragma once

#include "component.h"

class CTimeRotate : public dragonbyte_engine::Component
{
public:
    void tick() override;
    Component* clone() const override { return nullptr; };
    
private:
    float time = 0;
};