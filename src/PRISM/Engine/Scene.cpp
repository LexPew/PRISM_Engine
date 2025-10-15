#include <PRISM/Engine/Scene.h>

#include <PRISM/Engine/Entity.h>

void Scene::Start(){
    for(auto &entity: entities){
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