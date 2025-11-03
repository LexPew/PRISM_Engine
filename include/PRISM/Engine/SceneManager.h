#pragma once

#include <PRISM/Engine/Scene.h>
#include <memory>
class SceneManager
{
private:
    SceneManager() {};
    std::shared_ptr<Scene> currentScene;

public:
    static SceneManager &Get()
    {
        static SceneManager instance;
        return instance;
    }

    void SetScene(std::shared_ptr<Scene> scene)
    {
        // Passing by value increments the shared_ptr refcount once.
        // Using std::move here avoids an extra redundant refcount increment/decremnt on assignment.
        currentScene = std::move(scene);
    }

    std::shared_ptr<Scene> GetScene() { return currentScene; }

    void Start()
    {
        if (currentScene)
            currentScene->Start();
    }
    void Update(float deltaTime)
    {
        if (currentScene)
            currentScene->Update(deltaTime);
    }
    void Draw()
    {
        if (currentScene)
            currentScene->Draw();
    }
    void GUI();
};