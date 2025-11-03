#include <PRISM/Engine/Scene.h>

#include <PRISM/Engine/Entity.h>
#include <imgui.h>

void Scene::Start()
{
    for (auto &entity : entities)
    {
        entity->Start();
    }
}

void Scene::Update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->Update(deltaTime);
    }
}
void Scene::Draw()
{
    for (auto &entity : entities)
    {
        entity->Draw();
    }
}
void Scene::GUI()
{
    // Scene Heirarchy
    // Entities List
    if (ImGui::Begin("Scene Heirarchy"))
    {
        for (size_t i = 0; i < entities.size(); i++)
        {
            if (ImGui::TreeNode(entities[i].get(), "Entity %zu", i))
            {
                ImGui::DragFloat3("##pos", &entities[i]->transform.position.x, 0.1f);
                ImGui::Text("Rotation: (%.2f, %.2f, %.2f)", entities[i]->transform.rotation.x, entities[i]->transform.rotation.y, entities[i]->transform.rotation.z);
                ImGui::Text("Scale:    (%.2f, %.2f, %.2f)", entities[i]->transform.scale.x, entities[i]->transform.scale.y, entities[i]->transform.scale.z);

                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}