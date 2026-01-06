#pragma once
#include <PRISM/Engine/Transform.h>
#include <list>
#include <memory>
#include <glm/glm.hpp>
/*
 * @class Entity
 * @brief Base class for all engine entities it holds the Start,Update And Draw function along with a
 */
class Entity
{
protected:
   Transform local;
   glm::mat4 worldMatrix{1.0f};

   // Parent entity pointer
   Entity *parent = nullptr;
   // Entity children, owned by unique ptr to ensure proper memory management
   std::list<std::unique_ptr<Entity>> children;

   bool dirtyTransform = true;

public:
   Entity() {};
   // Create entity with initial transform
   Entity(const Transform &initialTransform)
   {
      GetLocalTransform() = initialTransform;
   }
   // Create entity with parent
   Entity(const Transform &initialTransform, const Entity *parentEntity)
   {
      SetParent(const_cast<Entity *>(parentEntity));
      GetLocalTransform() = initialTransform;
   }
   virtual ~Entity() {};
   virtual void Start() {};
   virtual void Update(float deltaTime);
   virtual void Draw();

   // Transform management
   Transform &GetLocalTransform()
   {
      // Assume dirty when requested
      MarkDirty();
      return local;
   }
   const Transform &GetLocalTransform() const { return local; }

   // Children and Parent management
   const std::list<std::unique_ptr<Entity>> &GetChildren() const { return children; }

   void AddChild(std::unique_ptr<Entity> child)
   {
      child->parent = this;
      child->MarkDirty();
      children.push_back(std::move(child));
   }

   void RemoveChild(Entity *childToRemove)
   {
      children.remove_if([childToRemove](const std::unique_ptr<Entity> &child)
                         {
        if(child.get() == childToRemove){
            child->parent = nullptr;
            return true;
        }
        return false; });
   }

   void MarkDirty()
   {
      dirtyTransform = true;
      // Propagate dirty flag to children
      for (auto &child : children)
      {
         child->MarkDirty();
      }
   }

   void SetParent(Entity *p_parent)
   {
      // Make sure to remove from previous parent, so we don't have dangling references
      if (parent)
      {
         parent->RemoveChild(this);
      }
      parent = p_parent;
   }
};