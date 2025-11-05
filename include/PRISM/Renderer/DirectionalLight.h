#pragma once
#include <glm/vec3.hpp> 
/**
 * @class   DirectionalLight
 * 
 * @brief   Structure representing a directional light source in the scene.
 *          A directional light has no position; it shines from a certain direction uniformly in all directions.
 *
 *          It consists of three components:
 *          1. direction - The direction vector that the light is coming from.
 *          2. colour   - The color or brightness of the light as perceived by an observer.
 *          3. intensity - A measure of how much light there is, in a given direction.
 */
struct DirectionalLight
{
    glm::vec3 direction; // The direction vector that the light is coming from
    glm::vec3 colour;   // The color or brightness of the light as perceived by an observer
    float intensity;     // A measure of how much light there is, in a given direction
};
