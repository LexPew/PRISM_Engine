#pragma once
#include <PRISM/Engine/Entity.h>
#include <vector>
#include <memory>
class Scene
{
private:
    std::vector<std::shared_ptr<Entity>> entities;
public:
    Scene(){};

    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Draw();
    virtual void Destroy(){};

    virtual void AddEntity(const std::shared_ptr<Entity>& entity){entities.push_back(entity);}
    std::vector<std::shared_ptr<Entity>>& GetEntities(){return entities;};
};