#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Renderer/Cube.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Utils/PMath.h>
#include <PRISM/Renderer/Plane.h>
#include <PRISM/Core/AssetManger.h>
#include <PRISM/Engine/Light.h>
#include <fmt/core.h>

#include <PRISM/Engine/OrbitalCameraEntity.h>
void CubeScene::Start()
{
    entities.clear();
    
    // Camera is a root-level entity owned by the scene

    EmplaceEntity(std::make_unique<OrbitalCameraEntity>());

    auto cubeMesh = std::make_shared<Cube>();
    auto monkeyMesh = AssetManager::LoadMesh("examples/Monkey.obj");
    auto grassTexture = AssetManager::LoadTexture("examples/Grass.png");
    auto boxTexture = AssetManager::LoadTexture("examples/crate1/crate1_diffuse.png");

    auto plane = std::make_shared<Plane>();

    // Environment root (owns floor and lights)
    auto environmentRoot = std::make_unique<Entity>();

    // Floor entity (child of environment)
    {
        auto floorEntity = std::make_unique<ModelEntity>();
        floorEntity->SetMesh(plane);
        floorEntity->SetTexture(grassTexture);
        floorEntity->GetLocalTransform().position = {0.0f, -1.0f, 0.0f}; // Move floor down
        floorEntity->GetLocalTransform().scale = {20.0f, 1.0f, 20.0f};   // Scale it up
        environmentRoot->AddChild(std::move(floorEntity));
    }
    auto lightRoot = std::make_unique<Entity>();
    // Lights (children of environment)
    for (int i = 0; i < 3; i++)
    {
        auto light = std::make_unique<Light>(.3f);
        light->GetLocalTransform().position.x += (-10 + (10 * i));
        light->GetLocalTransform().position.y = (i * 5);
        light->SetAttenuation((5 + i * 8));
        lightRoot->AddChild(std::move(light));
    }

    // Add environment root to scene
    EmplaceEntity(std::move(environmentRoot));
    // Add light root to scene
    EmplaceEntity(std::move(lightRoot));

    // Objects root (owns the random cubes/monkeys)
    auto objectsRoot = std::make_unique<Entity>();

    // Spawn random cubes/monkeys under objects root
    for (int i = 0; i < 10; i++)
    {
        auto newObject = std::make_unique<ModelEntity>();

        float rX = PMath::RandomRange(-5, 5);
        float rY = PMath::RandomRange(0, 5); // Above floor
        float rZ = PMath::RandomRange(-5, 5);

        float rand = PMath::RandomRange(0.0f, 1.0f);
        if (rand >= .5f)
        {
            newObject->SetMesh(cubeMesh);
            newObject->SetTexture(boxTexture);
        }
        else
        {
            newObject->SetMesh(monkeyMesh);
        }

        newObject->GetLocalTransform().position = {rX, rY, rZ};
        newObject->GetLocalTransform().scale = {1.0f, 1.0f, 1.0f};
        objectsRoot->AddChild(std::move(newObject));
    }

    // Add objects root to scene
    EmplaceEntity(std::move(objectsRoot));

    Scene::Start();
}

void CubeScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}
