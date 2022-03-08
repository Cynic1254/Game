#pragma once
#include "Component.h"

#include "template.h"

class Entity;

class Fysics :
    public Component
{
public:
    bool Move(Tmpl8::vec2 move, Entity& entity);
protected:
private:
};
