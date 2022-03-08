#pragma once
#include "Component.h"
#include "template.h"

class Transform :
    public Component
{
public:
    Transform() : position(0.0f) {};
    Transform(Tmpl8::vec2 position) : 
        position(position)
    {};

    /// <summary>
    /// set the position
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Tmpl8::vec2 position);

    /// <summary>
    /// adds the position to the current position
    /// </summary>
    /// <param name="position"></param>
    void AddPosition(Tmpl8::vec2 position);

    /// <summary>
    /// returns the position
    /// </summary>
    /// <returns></returns>
    Tmpl8::vec2 GetPosition();

protected:
private:
    Tmpl8::vec2 position;
};
