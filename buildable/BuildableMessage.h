#ifndef BUILDABLEMESSAGE_H
#define BUILDABLEMESSAGE_H

#include <string>
#include <list>

#include <stdint.h>

#include "buildable/AbstractXMLBuildableObject.h"

#include "buildable/BuildableHeader.h"
#include "buildable/BuildableBody.h"

class BuildableMessage : public AbstractXMLBuildableObject
{
    protected:
        BuildableHeader m_header;
        BuildableBody m_body;

    public:
        BuildableMessage();/*const std::string &sourceName = std::string(),
                         const std::string &commandName = std::string(),
                         const std::list<std::string> &destinationNames = std::list<std::string>(),
                         const uint64_t bodySize = 0,
                         const unsigned char *body = 0);*/
};

#endif // BUILDABLEMESSAGE_H
