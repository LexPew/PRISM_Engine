#pragma once
#include <PRISM/Engine/Entity.h>
#include <PRISM/Engine/SceneLighting.h>
#include <PRISM/Renderer/CubeMap.h>
#include <glm/vec3.hpp>
#include <vector>
#include <memory>


/**
 * @class Scene
 * @brief Represents a 3D scene containing entities and lighting.
 *
 * The Scene class manages all entities and lighting within a particular scene.
 * It provides methods for lifecycle events (Start, Update, Draw, Destroy)
 * and handles the addition and retrieval of entities.
 */
class Scene
{
protected:
    /**
     * @brief Lighting information for the scene.
     */
    SceneLighting sceneLighting;

    /**
     * @brief List of all entities currently in the scene.
     */
    std::vector<std::shared_ptr<Entity>> entities;

    /**
     * @brief Optional skybox for the scene.
     */
    std::shared_ptr<CubeMap> skybox{nullptr};

public:
    /**
     * @brief Default constructor for the Scene.
     */
    Scene() {};

    ~Scene(){entities.clear();};

    /**
     * @brief Called when the scene starts.
     * Override this method to initialize scene-specific logic.
     */
    virtual void Start();

    /**
     * @brief Called every frame to update scene logic.
     * @param deltaTime Time elapsed since the last frame.
     */
    virtual void Update(float deltaTime);

    /**
     * @brief Called every frame to draw the scene.
     * Override this method to render custom objects.
     */
    virtual void Draw();

    /**
     * @brief Called when the scene is destroyed.
     * Override this to clean up resources.
     */
    virtual void Destroy() {};

    /**
     * @brief Adds a new entity to the scene.
     * @param entity Shared pointer to the entity to add.
     */
    virtual void AddEntity(const std::shared_ptr<Entity> &entity) { entities.push_back(entity); }

    /**
     * @brief Returns a reference to the list of entities.
     * @return Reference to the internal entities vector.
     */
    std::vector<std::shared_ptr<Entity>> &GetEntities() { return entities; };

    /**
     * @brief Returns all entities in the scene.
     * Alias for GetEntities() for clarity.
     * @return Reference to the internal entities vector.
     */
    std::vector<std::shared_ptr<Entity>> &GetAllEntities() { return entities; }

    /**
     * @brief Retrieves the current scene lighting.
     * @return Reference to the SceneLighting struct.
     */
    SceneLighting &GetSceneLighting() { return sceneLighting; }

    /**
     * @brief Sets the scene lighting to a new value.
     * @param newLighting The new lighting configuration.
     */
    void SetSceneLighting(const SceneLighting &newLighting) { sceneLighting = newLighting; }

    //TODO: Make this better, more flexible or something
    //Scene Specific Panels
    virtual void Panel() {/*PANEL STUFF*/};
};
