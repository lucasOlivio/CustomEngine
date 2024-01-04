#include "pch.h"

#include "TransparentEntitiesLocator.h"

namespace MyEngine
{
    TransparentEntitiesComponent* TransparentEntitiesLocator::m_pTransparentEntities = new TransparentEntitiesComponent();

    TransparentEntitiesComponent* TransparentEntitiesLocator::Get()
    {
        return m_pTransparentEntities;
    }

    void TransparentEntitiesLocator::Set(TransparentEntitiesComponent* pTransparentEntities)
    {
        delete m_pTransparentEntities;
        m_pTransparentEntities = pTransparentEntities;
    }
}
