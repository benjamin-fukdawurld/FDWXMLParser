#include "Header.h"
using namespace std;
using namespace tinyxml2;

const std::string Header::HEADER_BALISE_NAME("HEADER");
const std::string Header::SRC_BALISE_NAME("SRC");
const std::string Header::CMD_BALISE_NAME("CMD");

Header::Header(std::string sourceName,
                                 std::string commandName,
                                 const Destination& destinationNames) :
                                 AbstractBuildableObject(),
                                 m_sourceName(sourceName),
                                 m_commandName(commandName),
                                 m_destinationNames(destinationNames)

{
    checkBuildable();
}

const string& Header::getSourceName() const
{
    return m_sourceName;
}

const string& Header::getCommandName() const
{
    return m_commandName;
}

const Destination& Header::getDestinations() const
{
    return m_destinationNames;
}

const Destination* Header::getDestinationsPtr() const
{
    return &m_destinationNames;
}

void Header::setSourceName(const std::string& sourceName)
{
    m_sourceName = sourceName;
    checkBuildable();
}

void Header::setCommandName(const std::string& commandName)
{
    m_commandName = commandName;
    checkBuildable();
}

void Header::setDestinations(const Destination& destinationNames)
{
    m_destinationNames = destinationNames;
    checkBuildable();
}

const char *Header::getBuiltElementName() const
{
    return "Header";
}

bool Header::build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent, const int number) const
{
    if(!isBuildable() || !m_destinationNames.isBuildable())
    return false;

    XMLElement *elm = doc.NewElement(HEADER_BALISE_NAME.c_str());
    if(elm == 0)
    return false;

    XMLElement* src = doc.NewElement(SRC_BALISE_NAME.c_str());
    if(src == 0)
    return false;

    XMLElement* cmd = doc.NewElement(CMD_BALISE_NAME.c_str());
    if(cmd == 0)
    return false;

    src->SetText(m_sourceName.c_str());
    cmd->SetText(m_commandName.c_str());

    elm->InsertFirstChild(src);

    if(!m_destinationNames.build(doc, elm))
    return false;

    elm->InsertEndChild(cmd);

    XMLElement *antecedant(0);
    antecedant = (parent != 0 ? parent->FirstChildElement(HEADER_BALISE_NAME.c_str()) : doc.FirstChildElement(HEADER_BALISE_NAME.c_str()));
    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    antecedant = antecedant->NextSiblingElement(HEADER_BALISE_NAME.c_str());


    if(parent != 0)
    {
        if(antecedant != 0)
        parent->InsertAfterChild(antecedant, elm);
        else
        parent->InsertFirstChild(elm);
    }
    else
    {
        if(antecedant != 0)
        doc.InsertAfterChild(antecedant, elm);
        else
        doc.InsertFirstChild(elm);
    }

    return true;
}

bool Header::parse(XMLDocument &doc, XMLElement *parent, const int number)
{
    XMLElement *elm(0);

    elm = (parent != 0 ? parent->FirstChildElement("HEADER") : doc.FirstChildElement("HEADER"));

    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    elm = elm->NextSiblingElement(HEADER_BALISE_NAME.c_str());

    if(elm == 0)
    return (m_isBuildable = false);

    XMLElement *src = elm->FirstChildElement(SRC_BALISE_NAME.c_str());
    m_sourceName = src->GetText();

    m_destinationNames.parse(doc, elm);
    if(!m_destinationNames.isBuildable())
    return (m_isBuildable = false);

    XMLElement *cmd = elm->FirstChildElement(CMD_BALISE_NAME.c_str());
    m_commandName = cmd->GetText();

    checkBuildable();

    return m_isBuildable;
}

void Header::checkBuildable()
{
    m_isBuildable = m_destinationNames.isBuildable() && !m_sourceName.empty() && !m_commandName.empty();
}



