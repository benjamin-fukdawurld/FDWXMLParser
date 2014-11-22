#ifndef PARSABLEBODY_H
#define PARSABLEBODY_H

#include <stdint.h>


#include "parsable/AbstractXMLParsableObject.h"


class ParsableBody : public AbstractXMLParsableObject
{
    public:
        static const std::string BODY_BALISE_NAME;

    protected:
        uint64_t m_xmlBodysize;


    public:
        ParsableBody(tinyxml2::XMLElement *selfElement = 0);
        ParsableBody(tinyxml2::XMLNode *parent);

        virtual uint64_t getBodySize() const;
        virtual const char *getParsedElementName() const;
        virtual bool parse(AbstractXMLBuildableObject* parsed) const;

    protected:
        virtual void init();
};

#endif // PARSABLEBODY_H
