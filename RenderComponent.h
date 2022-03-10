#pragma once
#include "Component.h"
#include "surface.h"
#include "template.h"

#include <map>

typedef unsigned int Pixel;

struct RenderObject
{
    RenderObject(float x, float y, Tmpl8::Sprite& sprite, Tmpl8::Surface* screen) : 
        pos(x, y),
        sprite(sprite),
        dst(screen)
    {}

    RenderObject(Tmpl8::vec2 pos, Tmpl8::Sprite& sprite, Tmpl8::Surface* screen) :
        pos(pos),
        sprite(sprite),
        dst(screen)
    {}

    Tmpl8::vec2 pos;
    Tmpl8::Sprite& sprite;
    Tmpl8::Surface* dst;
};

class RenderComponent :
    public Component
{
public:
    RenderComponent(Tmpl8::Surface* surface, int numFrames) : 
        sprite(surface, numFrames)
    {}

    void Render(Entity& entity, Tmpl8::Surface& screen);

    static void RenderAll();

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

    static std::multimap<float, RenderObject> renderQueue;
};
