#include "Message.h"

using namespace std;
using namespace tinyxml2;
using namespace FDWMessage;

const string Message::DECLARATION_VERSION_ATTRIBUTE("1.0");
const string Message::DECLARATION_ENCODING_ATTRIBUTE("UTF-8");
const string Message::DECLARATION_STANDALONE_ATTRIBUTE("no");
const string Message::MESSAGE_BALISE_NAME("MESSAGE");
const string Message::MESSAGE_XMLNS_ATTRIBUTE_NAME("xmlns:xsi");
const string Message::MESSAGE_XSI_ATTRIBUTE_NAME("xsi:noNamespaceSchemaLocation");
const string Message::MESSAGE_XMLNS_ATTRIBUTE("http://www.w3.org/2001/XMLSchema-instance");
const string Message::MESSAGE_XSI_ATTRIBUTE("ressources/message.xsd");

Message::Message(string sourceName,
                 string commandName,
                 const Destination &destinationNames,
                 uint64_t bodySize,
                 unsigned char *body) :
    AbstractBuildableObject(),
    m_header(sourceName, commandName, destinationNames),
    m_body(bodySize, body)
{
    checkBuildable();
}


const char *Message::getDeclaration()
{
    return string("xml version=\"" + DECLARATION_VERSION_ATTRIBUTE
                + "\" encoding=\"" + DECLARATION_ENCODING_ATTRIBUTE
                + "\" standalone=\"" + DECLARATION_STANDALONE_ATTRIBUTE + "\"").c_str();
}


const char *Message::getBuiltElementName() const
{
    return "Message";
}

bool Message::build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent, const int number) const
{
    if(!isBuildable() || !m_header.isBuildable() || !m_body.isBuildable())
    return false;

    XMLDeclaration *declaration = doc.NewDeclaration();
    declaration->SetValue(getDeclaration());
    if(declaration == 0)
    return false;

    doc.InsertFirstChild(declaration);


    XMLElement *elm = doc.NewElement(MESSAGE_BALISE_NAME.c_str());
    if(elm == 0)
    return false;

    elm->SetAttribute(MESSAGE_XMLNS_ATTRIBUTE_NAME.c_str(), MESSAGE_XMLNS_ATTRIBUTE.c_str());
    elm->SetAttribute(MESSAGE_XSI_ATTRIBUTE_NAME.c_str(), MESSAGE_XSI_ATTRIBUTE.c_str());

    if(!m_header.build(doc, elm) || !m_body.build(doc, elm))
    return false;

    XMLElement *antecedant(0);
    antecedant = (parent != 0 ? parent->FirstChildElement(MESSAGE_BALISE_NAME.c_str()) : doc.FirstChildElement(MESSAGE_BALISE_NAME.c_str()));
    for(int i(0), c(number - 1); i < c && antecedant != 0; ++i)
    antecedant = antecedant->NextSiblingElement(MESSAGE_BALISE_NAME.c_str());

    if(parent != 0)
    {
        if(antecedant != 0)
        parent->InsertAfterChild(antecedant, elm);
        else
        parent->InsertEndChild(elm);
    }
    else
    {
        if(antecedant != 0)
        doc.InsertAfterChild(antecedant, elm);
        else
        doc.InsertEndChild(elm);
    }

    return true;
}


bool Message::parse(XMLDocument &doc, XMLElement *parent, const int number)
{
    XMLElement *elm(0);


    elm = (parent != 0 ? parent->FirstChildElement(MESSAGE_BALISE_NAME.c_str()) : doc.FirstChildElement(MESSAGE_BALISE_NAME.c_str()));

    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    elm = elm->NextSiblingElement(MESSAGE_BALISE_NAME.c_str());

    if(elm == 0)
    return (m_isBuildable = false);

    if(!m_header.parse(doc, elm))
    return (m_isBuildable = false);

    if(!m_body.parse(doc,elm))
    return (m_isBuildable = false);

    checkBuildable();

    return m_isBuildable;
}


void Message::checkBuildable()
{
    m_isBuildable = m_header.isBuildable() && m_body.isBuildable();
}
