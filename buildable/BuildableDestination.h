#ifndef BUILDABLEDESTINATION_H
#define BUILDABLEDESTINATION_H

#include <list>
#include <string>

#include "buildable/AbstractXMLBuildableObject.h"

class ParsableDestination;

class BuildableDestination : public AbstractXMLBuildableObject
{
    protected:
        std::list<std::string> m_destinationNames;

    public:
        BuildableDestination(std::list<std::string> destinationNames = std::list<std::string>());

        const std::list<std::string>& getDestinationNames() const;
        const std::string getDestinationName(const int index) const;

        void setDestinationNames(const std::list<std::string>& destinationNames);
        void setDestinationName(const std::string& destinationName, const int index);

        void addDestinationName(const std::string& destinationName);

        void insertDestinationName(const std::string& destinationName, const int index);

        void removeDestinationName(const std::string& destinationName);
        void removeDestinationName(const int index);

        bool containsDestinationName(const std::string& destinationName) const;

        int indexOf(const std::string& destinationName, int offset);
        std::list<std::string>::iterator indexOf(const std::string& destinationName, std::list<std::string>::iterator offset);


        int getNumberOfDestination() const;
        virtual const char* getBuiltElementName() const;
        virtual bool build(AbstractXMLParsableObject* built);

    protected:
        virtual void checkBuildable();
        virtual bool build(ParsableDestination* built);

};

#endif // BUILDABLEDESTINATION_H
