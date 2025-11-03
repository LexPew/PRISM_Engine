#include <PRISM/Examples/TerrainScene.h>
#include <PRISM/Engine/Terrain.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>

void TerrainScene::Start()
{
    int terrainSize = 200;
    auto camera = std::make_shared<OrbitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);
    //TODO:ADD ASSET PATH
    std::shared_ptr<Terrain> gen = std::make_shared<Terrain>(400,249,FLoader::LoadImage("/media/sharedrive/Year_3/3D_Graphics/Learning_Material/PRISM_Renderer/hmap.jpg"));
      // std::shared_ptr<Terrain> gen = std::make_shared<Terrain>(500,500,0.01f,4);
       
    gen.get()->transform.position.x -= terrainSize / 2;
    gen.get()->transform.position.z -= terrainSize / 2;
    AddEntity(gen);
    Scene::Start();
}
