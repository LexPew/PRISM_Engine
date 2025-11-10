#pragma once
#include <PRISM/Engine/Transform.h>

/*
 * @class Entity
 * @brief Base class for all engine entities it holds the Start,Update And Draw function along with a
 */
class Entity
{
public:

   Transform transform;

   Entity() {};
   Entity(const glm::vec3 &p_position, const glm::vec3 &p_rotation, const glm::vec3 &p_scale)
   {
      transform.position = p_position;
      transform.rotation = p_rotation;
      transform.scale = p_scale;
   };
   virtual ~Entity(){};
   virtual void Start() {};
   virtual void Update(float deltaTime) {};
   virtual void Draw() {};
};