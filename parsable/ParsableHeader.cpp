#include "ParsableHeader.h"

#include "buildable/BuildableHeader.h"

using namespace tinyxml2;

const std::string ParsableHeader::HEADER_BALISE_NAME("HEADER");
const std::string ParsableHeader::SRC_BALISE_NAME("SRC");
const std::string ParsableHeader::CMD_BALISE_NAME("CMD");

ParsableHeader::ParsableHeader(XMLElement *selfElement) : AbstractXMLParsableObject(selfElement)
{
    init();
}

ParsableHeader::ParsableHeader(XMLNode *parent) : AbstractXMLParsableObject("HEADER", parent)
{
    init();
}


const XMLElement* ParsableHeader::getSource() const
{
    return m_source;
}

const XMLElement* ParsableHeader::getCommand() const
{
    return m_command;
}

const char* ParsableHeader::getSourceText() const
{
    if(getSource() == 0)
    return 0;

    return m_source->GetText();
}

const char* ParsableHeader::getCommandText() const
{
    if(getCommand() == 0)
    return 0;

    return m_command->GetText();
}

const ParsableDestination& ParsableHeader::getDestination() const
{
    return m_destination;
}

const char* ParsableHeader::getParsedElementName() const
{
    return "BuildableHeader";
}



bool ParsableHeader::parse(AbstractXMLBuildableObject* parsed) const
{
    if(parsed == NULL || strcmp(parsed->getBuiltElementName(), "ParsableHeader") != 0)
    return false;

    return parse((BuildableHeader*) parsed);
}



void ParsableHeader::init()
{
    m_xmlDocument = 0;
    m_isParsable = false;

    if(!hasElement())
    return;

    m_xmlDocument = m_xmlElement->GetDocument();

    XMLElement *current = 0;

    current = m_xmlElement->FirstChildElement("SRC");
    if(current == 0)
    return;

    m_source = current;


    current = m_xmlElement->FirstChildElement("CMD");
    if(current == 0)
    return;

    m_command = current;

    current = m_xmlElement->FirstChildElement("DST");
    if(current == 0)
    return;

    m_destination.setXMLlement(current);

    m_isParsable = m_destination.isParsable();
}


bool ParsableHeader::parse(BuildableHeader* parsed) const
{
    if(!isParsable() || parsed == 0 || !m_destination.isParsable())
    return false;

    BuildableDestination dest;
    if(!m_destination.parse((AbstractXMLBuildableObject*) &dest) || !dest.isBuildable())
    return false;

    parsed->setSourceName(getSourceText());
    parsed->setCommandName(getCommandText());
    parsed->setDestinationNames(dest);

    return parsed->isBuildable();
}
