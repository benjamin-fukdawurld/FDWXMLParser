#include "AbstractXMLParsableObject.h"

#include <iostream>

using namespace tinyxml2;
using namespace std;

AbstractXMLParsableObject::AbstractXMLParsableObject(XMLElement *selfElement) : m_isParsable(false), m_xmlDocument(0), m_xmlElement(selfElement)
{}

AbstractXMLParsableObject::AbstractXMLParsableObject(const char* elementName, XMLNode *parent) : m_isParsable(false), m_xmlDocument(0), m_xmlElement(parent->FirstChildElement(elementName))
{}

bool AbstractXMLParsableObject::XMLSuccess(const XMLError& result)
{
    if(result == XML_SUCCESS || result == XML_NO_ERROR)
    return true;

    return false;
}

void AbstractXMLParsableObject::appendToParentElement(XMLElement *parent)
{
    parent->InsertEndChild(m_xmlElement);
}

bool AbstractXMLParsableObject::hasDocument() const
{
    return m_xmlDocument != 0;
}

XMLDocument *AbstractXMLParsableObject::getXMLDocument() const
{
    return m_xmlDocument;
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

string AbstractXMLParsableObject::getInnerText()
{
    if(!hasElement())
    return "";

    return m_xmlElement->GetText();
}

string AbstractXMLParsableObject::toString()
{
    if(!hasElement() || !hasDocument())
    return string();

    XMLPrinter printer;
    m_xmlDocument->Print(&printer);

    return printer.CStr();
}


