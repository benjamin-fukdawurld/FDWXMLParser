#ifndef PARSABLEBODY_H
#define PARSABLEBODY_H

#include <vector>

#include <stdint.h>

#include "parsable/AbstractXMLParsableObject.h"

class BuildableBody;

class ParsableBody : public AbstractXMLParsableObject
{
    public:
        static const std::string BODY_BALISE_NAME;

    protected:
        uint64_t m_sizeOfParsedBody;


    public:
        ParsableBody(tinyxml2::XMLElement *selfElement = 0);
        ParsableBody(tinyxml2::XMLNode *parent);

        virtual uint64_t getSizeOfBody() const;
        virtual const char *getParsedElementName() const;
        virtual const char *getUnparsedBody() const;
        virtual const std::vector<unsigned char> getParsedBody() const;
        virtual bool parse(AbstractXMLBuildableObject* parsed) const;

    protected:
        virtual const char* getXMLBodySizeAttribute() const;
        virtual void init();
        virtual bool parse(BuildableBody* parsed) const;
};

#endif // PARSABLEBODY_H
