#ifndef ABSTRACTXMLPARSABLEOBJECT_H
#define ABSTRACTXMLPARSABLEOBJECT_H

#include <string>

#include "tinyxml/tinyxml2.h"

class AbstractXMLBuildableObject;

class AbstractXMLParsableObject
{
    protected:
        bool m_isParsable;
        tinyxml2::XMLDocument* m_xmlDocument;
        tinyxml2::XMLElement* m_xmlElement;

    public:
        AbstractXMLParsableObject(tinyxml2::XMLElement* selfElement = 0);
        AbstractXMLParsableObject(const char* elementName, tinyxml2::XMLNode* parent);

        static bool XMLSuccess(const tinyxml2::XMLError& result);

        void appendToParentElement(tinyxml2::XMLElement* parent);

        virtual bool hasDocument() const;
        virtual tinyxml2::XMLDocument *getXMLDocument() const;

        virtual bool hasElement() const;
        virtual const tinyxml2::XMLElement *getXMLElement() const;
        virtual void setXMLlement(tinyxml2::XMLElement *element);

        virtual bool isParsable() const;
        virtual const char* getParsedElementName() const = 0;
        virtual bool parse(AbstractXMLBuildableObject* parsed) const = 0;

        virtual std::string getInnerText();
        virtual std::string toString();

protected:
        virtual void init() = 0;

};

#endif // ABSTRACTXMLPARSABLEOBJECT_H
