#include "PRISM/Engine/Entity.h"

void Entity::Update(float deltaTime)
{
    if (dirtyTransform)
    {
        glm::mat4 localM = local.GetMatrix();

        if (parent)
            worldMatrix = parent->worldMatrix * localM;
        else
            worldMatrix = localM;

        dirtyTransform = false;
    }

    for (auto &child : children)
        child->Update(deltaTime);
}


void Entity::Draw()
{
    // Draw all children entities
    for (auto &child : children)
    {
        child->Draw();
    }
}