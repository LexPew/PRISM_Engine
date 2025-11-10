#include <PRISM/Examples/TerrainScene.h>
#include <PRISM/Engine/Terrain.h>
#include <PRISM/Engine/OrbitalCameraEntity.h>
#include <PRISM/Examples/Panels/EditorSceneTerrainPanel.h>
void TerrainScene::Start()
{
    auto camera = std::make_shared<OrbitalCameraEntity>();
    camera->transform.position = {0, 0, 15.0f};
    AddEntity(camera);
    std::shared_ptr<Terrain> gen = std::make_shared<Terrain>(400, 249, FLoader::LoadImage(FLoader::GetAssetPath("examples/custom_hmap.png")));
    AddEntity(gen);
    Scene::Start();
}

void TerrainScene::Panel()
{
    PRISM::Editor::EditorSceneTerrainPanel::Panel();
}
