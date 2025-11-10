#pragma once 

#include <PRISM/Renderer/DirectionalLight.h>
/**
 * @struct SceneLighting
 * @brief Contains all lighting information for a scene.
 *
 * Stores a directional light and an ambient light color.
 */
//TODO: Update to make directional light use transform rotation style
struct SceneLighting
{
    /**
     * @brief Main directional light for the scene.
     */
    DirectionalLight directionalLight
    {
        
        {6,-1.0f,0},
        {.021f,.022f,.025f},
        {1}
    };

    /**
     * @brief Ambient light color applied to the entire scene.
     * Defaults to a warm, low-intensity orange color.
     */
    glm::vec3 ambientLightColour{0.2f, 0.2f, 0.2f};
};