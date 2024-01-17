#include "pch.h"
#include "Scene.h"

namespace MyEngine
{
    Scene::Scene()
    {
        m_pEntityManager = new EntityManager();
    }

    Scene::~Scene()
    {
        delete m_pEntityManager;

        using ComponentMapPair = std::pair<ComponentType, BiMap<Entity, ComponentId>*>;
        for (ComponentMapPair componentMap : m_componentMaps)
        {
            delete componentMap.second;
        }

        using ComponentPoolPair = std::pair<ComponentType, ComponentPool*>;
        for (ComponentPoolPair componentPool : m_componentPools)
        {
            delete componentPool.second;
        }
    }

    Entity Scene::CreateEntity()
    {
        // Initial mask always empty for now
        Entity entityId = m_pEntityManager->AddEntity(EntityMask());
        return entityId;
    }

    void Scene::RemoveEntity(Entity entityId)
    {
        m_entitiesToDestroy.push_back(entityId);
    }

    void Scene::DestroyEntities()
    {
        for (Entity entityId : m_entitiesToDestroy)
        {
            // Go through every component the entity have
            EntityMask entityMask = m_pEntityManager->GetMask(entityId);
            for (int componentType = 0; componentType < entityMask.size(); componentType++)
            {
                if (!entityMask[componentType])
                {
                    continue;
                }

                BiMap<Entity, ComponentId>* pComponentMap = m_componentMaps[componentType];
                ComponentPool* pComponentPool = m_componentPools[componentType];

                // Component to remove and new location for moved component
                ComponentId componentId;
                pComponentMap->GetByKey(entityId, componentId);

                // Remove the component from the pool
                ComponentId componentIdOld;
                pComponentPool->Remove(componentId, componentIdOld);

                // Remove the relation mapping
                pComponentMap->RemoveByKey(entityId);

                // Get entity id that had component moved
                Entity entityIdMoved;
                pComponentMap->GetByValue(componentIdOld, entityIdMoved);

                // Update the relation for the moved component
                pComponentMap->Update(entityIdMoved, componentId);
            }

            // Remove entity from entity manager list
            m_pEntityManager->RemoveEntity(entityId);
        }
    }

    EntityManager* Scene::GetEntitymanager()
    {
        return m_pEntityManager;
    }
}
