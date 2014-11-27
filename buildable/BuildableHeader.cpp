#include "BuildableHeader.h"

#include "parsable/ParsableHeader.h"

using namespace std;
using namespace tinyxml2;

BuildableHeader::BuildableHeader(std::string sourceName,
                                 std::string commandName,
                                 const BuildableDestination& destinationNames) :
                                 AbstractXMLBuildableObject(),
                                 m_sourceName(sourceName),
                                 m_commandName(commandName),
                                 m_destinationNames(destinationNames)

{
    checkBuildable();
}

const string& BuildableHeader::getSourceName() const
{
    return m_sourceName;
}

const string& BuildableHeader::getCommandName() const
{
    return m_commandName;
}

const BuildableDestination& BuildableHeader::getDestinationNames() const
{
    return m_destinationNames;
}

const BuildableDestination* BuildableHeader::getDestinationNamesPtr() const
{
    return &m_destinationNames;
}

void BuildableHeader::setSourceName(const std::string& sourceName)
{
    m_sourceName = sourceName;
    checkBuildable();
}

void BuildableHeader::setCommandName(const std::string& commandName)
{
    m_commandName = commandName;
    checkBuildable();
}

void BuildableHeader::setDestinationNames(const BuildableDestination& destinationNames)
{
    m_destinationNames = destinationNames;
    checkBuildable();
}

const char *BuildableHeader::getBuiltElementName() const
{
    return "ParsableHeader";
}

bool BuildableHeader::build(AbstractXMLParsableObject *built)
{
    if(built == 0 || strcmp(built->getParsedElementName(), "BuildableDestination") != 0)
    return false;

    return build((ParsableDestination*) built);
}

void BuildableHeader::checkBuildable()
{
    m_isBuildable = m_destinationNames.isBuildable() && !m_sourceName.empty() && !m_commandName.empty();
}



bool BuildableHeader::build(ParsableHeader *built)
{
    if(built == 0 || !isBuildable() || !built->hasDocument())
    return false;

    ParsableDestination dest;
    m_destinationNames.build((AbstractXMLParsableObject*) &dest);

    if(!dest.isParsable())
    return false;

    XMLDocument doc;
    XMLElement* element = doc.NewElement(ParsableHeader::HEADER_BALISE_NAME.c_str());

    XMLElement* src = doc.NewElement(ParsableHeader::SRC_BALISE_NAME.c_str());
    src->SetText(m_sourceName.c_str());

    XMLElement* cmd = doc.NewElement(ParsableHeader::CMD_BALISE_NAME.c_str());
    cmd->SetText(m_commandName.c_str());

    element->InsertFirstChild(src);
    dest.appendToParentElement(element);
    element->InsertEndChild(cmd);

    built->setXMLlement(element);

    return built->isParsable();
}

