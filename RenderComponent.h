#pragma once
#include <map>

#include "Component.h"
#include "surface.h"
#include "template.h"

typedef unsigned int Pixel;

struct RenderObject
{
    RenderObject(float x, float y, tmpl8::Sprite& sprite, tmpl8::Surface* screen) : 
        pos(x, y),
        sprite(sprite),
        dst(screen)
    {}

    RenderObject(tmpl8::vec2 pos, tmpl8::Sprite& sprite, tmpl8::Surface* screen) :
        pos(pos),
        sprite(sprite),
        dst(screen)
    {}

    tmpl8::vec2 pos;
    tmpl8::Sprite& sprite;
    tmpl8::Surface* dst;
};

class RenderComponent :
    public Component
{
public:
    RenderComponent(tmpl8::Surface* surface, int numFrames) : 
        sprite(surface, numFrames)
    {}

    /// <summary>
    /// queues the object for render
    /// </summary>
    /// <param name="entity"></param>
    /// <param name="screen"></param>
    void Render(Entity& entity, tmpl8::Surface& screen);

    /// <summary>
    /// renders the object queue
    /// </summary>
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
    int GetWidth() const;

    /// <summary>
    /// gets the height of the sprite
    /// </summary>
    /// <returns></returns>
    int GetHeight() const;

    /// <summary>
    /// gets the buffer of the sprite surface location
    /// </summary>
    /// <returns></returns>
    Pixel* GetBuffer() const;

    /// <summary>
    /// gets the frames of the sprite
    /// </summary>
    /// <returns></returns>
    unsigned int Frames() const;

protected:

private:
    tmpl8::Sprite sprite;

    static std::multimap<float, RenderObject> renderQueue;
};
