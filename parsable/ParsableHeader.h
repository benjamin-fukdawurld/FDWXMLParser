#ifndef PARSABLEHEADER_H
#define PARSABLEHEADER_H

#include "parsable/AbstractXMLParsableObject.h"
#include "parsable/ParsableDestination.h"

class BuildableHeader;

class ParsableHeader : public AbstractXMLParsableObject
{
    public:
        static const std::string HEADER_BALISE_NAME;
        static const std::string SRC_BALISE_NAME;
        static const std::string CMD_BALISE_NAME;

    protected:
        tinyxml2::XMLElement* m_source;
        tinyxml2::XMLElement* m_command;
        ParsableDestination m_destination;

    public:
        ParsableHeader(tinyxml2::XMLElement *selfElement = 0);
        ParsableHeader(tinyxml2::XMLNode *parent);

        const tinyxml2::XMLElement* getSource() const;
        const tinyxml2::XMLElement* getCommand() const;
        const ParsableDestination& getDestination() const;

        const char* getSourceText() const;
        const char* getCommandText() const;

        virtual const char* getParsedElementName() const;
        virtual bool parse(AbstractXMLBuildableObject* parsed) const;

    protected:
        virtual void init();
        virtual bool parse(BuildableHeader* parsed) const;

};

#endif // PARSABLEHEADER_H
