#pragma once

#include <SDL_scancode.h>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <utility>

class Component;

namespace Tmpl8
{
    class Surface;
}

class Entity
{
public:
    Entity() { printf("map initialized with size: %i\n", (int)components.size()); };

    Entity(const Entity& copy) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity& operator=(Entity&&) = default;
    Entity(Entity&& move) noexcept = default;

    ~Entity();

    /// <summary>
    /// Adds a component to the entity
    /// </summary>
    /// <param name="component"></param>
    template<typename T, typename... Args>
    void AddComponent(Args&&... args);

    /// <summary>
    /// returns the first component with the correct typename in the map
    /// </summary>
    /// <typeparam name="T">The component type to return</typeparam>
    /// <returns></returns>
    template<typename T>
    T* GetComponent() const;

    /// <summary>
    /// returns a list of all the components of the specified type
    /// </summary>
    /// <typeparam name="T">The component type to return</typeparam>
    /// <returns></returns>
    template<typename T>
    std::vector<T*> GetComponents() const;

    /// <summary>
    /// update the Component
    /// </summary>
    void Update();

    /// <summary>
    /// Render the Component
    /// </summary>
    void Render(Tmpl8::Surface& screen);

    /// <summary>
    /// A key was Released
    /// </summary>
    /// <param name="key"></param>
    void KeyUp(SDL_Scancode key);

    /// <summary>
    /// A key was Pressed
    /// </summary>
    /// <param name="key"></param>
    void KeyDown(SDL_Scancode key);

    /// <summary>
    /// The mouse was moved
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    void MouseMove(int x, int y);

    /// <summary>
    /// A mouse button was released
    /// </summary>
    /// <param name="key"></param>
    void MouseUp(int key);

    /// <summary>
    /// A mouse button was pressed
    /// </summary>
    /// <param name="key"></param>
    void MouseDown(int key);

protected:

private:
    std::unordered_multimap<std::type_index, Component*> components;
};

template<typename T, typename... Args>
void Entity::AddComponent(Args&&... args)
{
    components.insert(std::pair<std::type_index, Component*>(typeid(T), new T(std::forward<Args>(args)...)));
}

template<typename T>
inline T* Entity::GetComponent() const
{
    auto iter = components.find(typeid(T));

    if (iter != components.end())
    {
        return dynamic_cast<T*>(iter->second);
    }

    return nullptr;
}

template<typename T>
inline std::vector<T*> Entity::GetComponents() const
{
    auto range = components.equal_range(typeid(T));
    std::vector<T*> res;

    for (auto& it = range.first; it != range.second; ++it) {
        res.push_back(dynamic_cast<T*>(it->second));
    }

    return res;
}