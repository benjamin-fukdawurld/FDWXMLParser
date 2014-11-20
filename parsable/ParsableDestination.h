#ifndef PARSABLEDESTINATION_H
#define PARSABLEDESTINATION_H

#include <vector>
#include <string>

#include "parsable/AbstractXMLParsableObject.h"

#include "buildable/AbstractXMLBuildableObject.h"

class BuildableDestination;

class ParsableDestination : public AbstractXMLParsableObject
{
    public:
        static const std::string DST_BALISE_NAME;

    protected:
        std::vector<tinyxml2::XMLElement*> m_destinationList;

    public:
        ParsableDestination(tinyxml2::XMLElement *selfElement = 0);
        ParsableDestination(tinyxml2::XMLNode *parent);

        virtual int getNumberOfDestination() const;
        virtual const std::vector<tinyxml2::XMLElement*>& getDestinationList() const;
        virtual const char* getDestinationName(const int index) const;

        virtual const char* getParsedElementName() const;
        virtual bool parse(AbstractXMLBuildableObject* parsed) const;

    protected:
        virtual int getXMLNumberAttribute() const;
        virtual void init();
        virtual bool parse(BuildableDestination* parsed) const;

};

#endif // PARSABLEDESTINATION_H
