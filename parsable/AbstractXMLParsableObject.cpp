#include "AbstractXMLParsableObject.h"

using namespace tinyxml2;
using namespace std;


AbstractXMLParsableObject::AbstractXMLParsableObject(XMLElement *selfElement) : m_isParsable(false), m_xmlElement(selfElement)
{}

AbstractXMLParsableObject::AbstractXMLParsableObject(const char* elementName, XMLNode *parent) : m_isParsable(false), m_xmlElement(parent->FirstChildElement(elementName))
{}

bool AbstractXMLParsableObject::XMLSuccess(const XMLError& result)
{
    if(result == XML_SUCCESS || result == XML_NO_ERROR)
    return true;

    return false;
}

void AbstractXMLParsableObject::addToParentElement(XMLElement *parent)
{
    parent->InsertEndChild(m_xmlElement);
}

bool AbstractXMLParsableObject::hasElement() const
{
    return m_xmlElement != 0;
}

const XMLElement *AbstractXMLParsableObject::getXMLElement() const
{
    return m_xmlElement;
}

void AbstractXMLParsableObject::setXMLlement(tinyxml2::XMLElement *element)
{
    m_xmlElement = element;
    init();
}

bool AbstractXMLParsableObject::isParsable() const
{
    return hasElement() && m_isParsable;
}

string AbstractXMLParsableObject::toString()
{
    XMLDocument doc;

    doc.InsertFirstChild(m_xmlElement);

    XMLPrinter printer;
    doc.Print(&printer);


    return string(printer.CStr());
}


