#ifndef BUILDABLEHEADER_H
#define BUILDABLEHEADER_H

#include <string>

#include "buildable/AbstractXMLBuildableObject.h"
#include "buildable/BuildableDestination.h"

class ParsableHeader;

class BuildableHeader : public AbstractXMLBuildableObject
{
    protected:
        std::string m_sourceName;
        std::string m_commandName;
        BuildableDestination m_destinationNames;

    public:
        BuildableHeader(std::string sourceName = std::string(),
                        std::string commandName = std::string(),
                        const BuildableDestination& destinationNames = BuildableDestination());

        const std::string& getSourceName() const;
        const std::string& getCommandName() const;
        const BuildableDestination& getDestinationNames() const;
        const BuildableDestination* getDestinationNamesPtr() const;

        void setSourceName(const std::string& sourceName);
        void setCommandName(const std::string& commandName);
        void setDestinationNames(const BuildableDestination& destinationNames);


        virtual const char* getBuiltElementName() const;
        virtual bool build(AbstractXMLParsableObject* built);

    protected:
        virtual void checkBuildable();
        virtual bool build(ParsableHeader* built);
};

#endif // BUILDABLEHEADER_H
