#pragma once
#include <PRISM/Engine/Transform.h>

// Base class for all entitys providing position,scale and rotation
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

     virtual void Start(){};
     virtual void Update(float deltaTime){};
     virtual void Draw(){};
};