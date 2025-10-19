#include <PRISM/Examples/TerrainScene.h>
#include <PRISM/Examples/TerrainGenerator.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>



void TerrainScene::Start()
{
    auto camera = std::make_shared<OribitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);

    auto gen = std::make_shared<TerrainGenerator>(50,50);
    AddEntity(gen);
    Scene::Start();
}


