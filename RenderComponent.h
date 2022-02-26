#pragma once
#include "Component.h"
#include "surface.h"

typedef unsigned int Pixel;

class RenderComponent :
    public Component
{
public:
    RenderComponent() = default;
    RenderComponent(Tmpl8::Surface* surface, int numFrames) : 
        sprite(surface, numFrames)
    {}

    /// <summary>
    /// renders the entity tp the screen
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="screen"></param>
    virtual void Render(Entity& entity, Tmpl8::Surface& screen) override;

    /// <summary>
    /// set the frame
    /// </summary>
    /// <param name="a_Index"></param>
    void SetFrame(unsigned int a_Index);

    /// <summary>
    /// gets the width of the sprite
    /// </summary>
    /// <returns></returns>
    int GetWidth();

    /// <summary>
    /// gets the height of the sprite
    /// </summary>
    /// <returns></returns>
    int GetHeight();

    /// <summary>
    /// gets the buffer of the sprite surface location
    /// </summary>
    /// <returns></returns>
    Pixel* GetBuffer();

    /// <summary>
    /// gets the frames of the sprite
    /// </summary>
    /// <returns></returns>
    unsigned int Frames();

protected:

private:
    Tmpl8::Sprite sprite;
};

