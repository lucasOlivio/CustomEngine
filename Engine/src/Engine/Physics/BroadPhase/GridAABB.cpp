#include "pch.h"

#include "GridAABB.h"

namespace MyEngine
{
    typedef std::unordered_set<Entity>::iterator itEntities;
    typedef std::unordered_set<sTriangle>::iterator itTriangles;

    void GridAABB::RemoveStaticEntity(Entity entityID)
    {
        itEntities it = m_vecStaticEntities.find(entityID);
        if (it != m_vecStaticEntities.end())
        {
            m_vecStaticEntities.erase(it);

            return;
        }

        return;
    }

    void GridAABB::RemoveNonStaticEntity(Entity entityID)
    {
        itEntities it = m_vecNonStaticEntities.find(entityID);
        if (it != m_vecNonStaticEntities.end())
        {
            m_vecNonStaticEntities.erase(it);

            return;
        }

        return;
    }

    void GridAABB::AddStaticEntity(Entity entityID)
    {
        m_vecStaticEntities.insert(entityID);
    }

    void GridAABB::AddNonStaticEntity(Entity entityID)
    {
        m_vecNonStaticEntities.insert(entityID);
    }

    void GridAABB::AddTriangle(sTriangle* pTriangle)
    {
        m_vecTriangles.insert(pTriangle);
    }

    size_t GridAABB::NumStaticEntities()
    {
        return m_vecStaticEntities.size();
    }

    size_t GridAABB::NumNonStaticEntities()
    {
        return m_vecNonStaticEntities.size();
    }

    size_t GridAABB::NumTriangles()
    {
        return m_vecTriangles.size();
    }

    size_t GridAABB::NumTotal()
    {
        return m_vecNonStaticEntities.size() + m_vecStaticEntities.size() + m_vecTriangles.size();
    }
}
