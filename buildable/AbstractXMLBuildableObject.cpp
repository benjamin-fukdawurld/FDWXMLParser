#include "AbstractXMLBuildableObject.h"

AbstractXMLBuildableObject::AbstractXMLBuildableObject() : m_isBuildable(false)
{
}

bool AbstractXMLBuildableObject::isBuildable() const
{
    return m_isBuildable;
}
