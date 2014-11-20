#include "ParsableDestination.h"

#include <cstring>

#include "buildable/BuildableDestination.h"

using namespace std;

using namespace tinyxml2;

const std::string ParsableDestination::DST_BALISE_NAME("DST");


ParsableDestination::ParsableDestination(XMLElement *selfElement) : AbstractXMLParsableObject(selfElement)
{}

ParsableDestination::ParsableDestination(tinyxml2::XMLNode *parent) : AbstractXMLParsableObject(DST_BALISE_NAME.c_str(), parent)
{}

int ParsableDestination::getNumberOfDestination() const
{
    if(isParsable())
    return m_destinationList.size();

    return 0;
}

const vector<XMLElement*>& ParsableDestination::getDestinationList() const
{
    return m_destinationList;
}

const char* ParsableDestination::getDestinationName(const int index) const
{
    if(index >= 0 && index < getNumberOfDestination())
    return m_destinationList[index]->GetText();

    return "";
}

const char* ParsableDestination::getParsedElementName() const
{
    return "BuildableDestination";
}

bool ParsableDestination::parse(AbstractXMLBuildableObject* parsed) const
{
    if(parsed == NULL || strcmp(parsed->getBuiltElementName(), "ParsableDestination") != 0)
    return false;

    return parse((BuildableDestination*) parsed);
}

bool ParsableDestination::parse(BuildableDestination* parsed) const
{
    if(!isParsable() || parsed == NULL)
    return false;

    for(int i(0), c(getNumberOfDestination()); i < c; ++i)
    parsed->addDestinationName(getDestinationName(i));

    return parsed->isBuildable();
}

int ParsableDestination::getXMLNumberAttribute() const
{
    int ret(-1);
    m_xmlElement->QueryIntAttribute("number", &ret);

    return ret;
}

void ParsableDestination::init()
{
    m_destinationList.clear();
    if(!hasElement())
    {
        m_isParsable = false;
        return;
    }

    XMLElement *current = m_xmlElement->FirstChildElement("NAME");
    if(current == 0)
    {
        m_isParsable = false;
        return;
    }

    while(current != 0)
    {
        m_destinationList.push_back(current);
        current = current->NextSiblingElement("NAME");
    }

    if(static_cast<int>(m_destinationList.size()) != getNumberOfDestination())
    {
        m_destinationList.clear();
        m_isParsable = false;
        return;
    }

    m_isParsable = true;
}
