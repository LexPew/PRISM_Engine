#include <PRISM/Examples/CubeScene.h>
#include <PRISM/Renderer/Cube.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Engine/ModelEntity.h>
#include <PRISM/Utils/PMath.h>
#include <PRISM/Renderer/Plane.h>
#include <PRISM/Core/AssetManger.h>
#include <PRISM/Engine/Light.h>
std::shared_ptr<OrbitalCameraEntity> camera;
std::shared_ptr<ModelEntity> floorEntity; // Keep floor as a member to skip rotation

void CubeScene::Start()
{

    camera = std::make_shared<OrbitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);

    auto cubeMesh = std::make_shared<RubiksCubeExample>();
    auto monkeyMesh = AssetManager::LoadMesh("examples/Monkey.obj");
    auto grassTexture = AssetManager::LoadTexture("examples/Grass.png");
    auto boxTexture = AssetManager::LoadTexture("examples/crate1/crate1_diffuse.png");

    auto plane = std::make_shared<Plane>();

    // Floor entity (stationary, scaled up, positioned below cubes)
    std::shared_ptr<ModelEntity> floorEntity = std::make_shared<ModelEntity>();
    floorEntity->SetMesh(plane);
    floorEntity->SetTexture(grassTexture);
    floorEntity->transform.position = {0.0f, -1.0f, 0.0f}; // Move floor down
    floorEntity->transform.scale = {20.0f, 1.0f, 20.0f};   // Scale it up
    AddEntity(floorEntity);

    for (int i = 0; i < 3; i++)
    {
        auto light = std::make_shared<Light>(.3f);
        light->transform.position.x += (-10 +(10 * i));
        light->transform.position.y = (i * 5);
        light->SetAttenuation((5 + i * 8));
        AddEntity(light);
    }

    // Spawn random cubes
    for (int i = 0; i < 10; i++)
    {
        auto newCube = std::make_shared<ModelEntity>();

        float rX = PMath::RandomRange(-5, 5);
        float rY = PMath::RandomRange(0, 5); // Above floor
        float rZ = PMath::RandomRange(-5, 5);

        float rand = PMath::RandomRange(0.0f, 1.0f);
        if (rand >= .5f)
        {

            newCube->SetMesh(cubeMesh);
            newCube->SetTexture(boxTexture);
        }
        else
        {
            newCube->SetMesh(monkeyMesh);
        }

        newCube->transform.position = {rX, rY, rZ};
        newCube->transform.scale = {1.0f, 1.0f, 1.0f};
        AddEntity(newCube);
    }

    Scene::Start();
}

void CubeScene::Update(float deltaTime)
{
    for (auto &entity : GetEntities())
    {
        // Skip camera and floor from rotation
        if (entity.get() != camera.get() && entity->transform.scale != glm::vec3(20.0f, 1.0f, 20.0f))
        {
            entity->transform.rotation.y += deltaTime * 10.0f;
            entity->transform.rotation.x += deltaTime * 20.0f;
        }
    }

    Scene::Update(deltaTime);
}
