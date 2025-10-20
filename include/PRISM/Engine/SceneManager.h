#pragma once

#include <Scene.h>
#include <memory>
class SceneManager
{
private:
    SceneManager();

public:
    static SceneManager &Get()
    {
        static SceneManager instance;
        return instance;
    }


    void SetScene(const Scene scene) { currentScene = scene; };
    Scene &GetScene() { return currentScene; };

    void Start() { currentScene.Start(); };

    void Update(float deltaTime) { currentScene.Update(deltaTime); };

    void Draw() { currentScene.Draw(); };
}