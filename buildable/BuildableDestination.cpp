#include "BuildableDestination.h"

#include <algorithm>

#include "parsable/ParsableDestination.h"

using namespace std;
using namespace tinyxml2;

BuildableDestination::BuildableDestination(std::list<std::string> destinationNames) :
                                            AbstractXMLBuildableObject(),
                                            m_destinationNames(destinationNames)
{
    //ctor
    checkBuildable();
}

const list<string>& BuildableDestination::getDestinationNames() const
{
    return m_destinationNames;
}

const string BuildableDestination::getDestinationName(const int index) const
{
    if(index < 0 || index >= (int) m_destinationNames.size())
    return "";

    list<string>::const_iterator it = m_destinationNames.begin();

    advance(it, index);

    return *it;
}

void BuildableDestination::setDestinationNames(const list<string>& destinationNames)
{
    m_destinationNames.clear();
    m_destinationNames = destinationNames;

    checkBuildable();
}

void BuildableDestination::setDestinationName(const string& destinationName, const int index)
{
    if(destinationName.empty())
    return;

    if(index < 0 || index >= (int) m_destinationNames.size())
    m_destinationNames.push_back(destinationName);

    list<string>::iterator it = m_destinationNames.begin();

    advance(it, index);
    *it = destinationName;

    checkBuildable();
}

void BuildableDestination::addDestinationName(const string& destinationName)
{
    if(destinationName.empty())
    return;

    m_destinationNames.push_back(destinationName);

    checkBuildable();
}

void BuildableDestination::insertDestinationName(const string& destinationName, const int index)
{
    if(destinationName.empty())
    return;

    if(index < 0 || index >= (int) m_destinationNames.size())
    m_destinationNames.push_back(destinationName);

    list<string>::iterator it = m_destinationNames.begin();

    advance(it, index);

    m_destinationNames.insert(it, destinationName);

    checkBuildable();
}

void BuildableDestination::removeDestinationName(const string& destinationName)
{
    m_destinationNames.remove(destinationName);

    checkBuildable();
}


void BuildableDestination::removeDestinationName(const int index)
{
    list<string>::iterator it = m_destinationNames.begin();

    advance(it, index);

    m_destinationNames.erase(it);

    checkBuildable();
}


bool BuildableDestination::containsDestinationName(const string& destinationName) const
{
    list<string>::const_iterator it = find(m_destinationNames.begin(), m_destinationNames.end(), destinationName);
    if(it != m_destinationNames.end())
    return true;

    return false;
}

int BuildableDestination::indexOf(const std::string& destinationName, int offset)
{
    list<string>::iterator it = m_destinationNames.begin();

    advance(it, offset);

    it = indexOf(destinationName, it);

    if(it != m_destinationNames.end())
    return distance(m_destinationNames.begin(), it);

    return -1;
}

std::list<std::string>::iterator BuildableDestination::indexOf(const std::string& destinationName, std::list<std::string>::iterator offset)
{
    return find(offset, m_destinationNames.end(), destinationName);
}

int BuildableDestination::getNumberOfDestination() const
{
    return m_destinationNames.size();
}

const char* BuildableDestination::getBuiltElementName() const
{
    return "ParsableDestination";
}

bool BuildableDestination::build(AbstractXMLParsableObject* built)
{
    if(built == 0 || strcmp(built->getParsedElementName(), "BuildableDestination") != 0)
    return false;

    return build((ParsableDestination*) built);
}



void BuildableDestination::checkBuildable()
{
    m_isBuildable = m_destinationNames.size() > 0;
}

bool BuildableDestination::build(ParsableDestination* built)
{
    if(built == 0 || !isBuildable() || !built->hasDocument())
    return false;

    XMLDocument doc;
    XMLElement* element = doc.NewElement(ParsableDestination::DST_BALISE_NAME.c_str());
    element->SetAttribute("number", getNumberOfDestination());

    for(list<string>::iterator it(m_destinationNames.begin()); it != m_destinationNames.end(); ++it)
    {
        XMLElement* tmp = doc.NewElement("NAME");
        tmp->SetText(it->c_str());

        element->InsertEndChild(tmp);
    }

    built->setXMLlement(element);

    return built->isParsable();
}
