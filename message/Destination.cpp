#include "Destination.h"


#include <iterator>
#include <algorithm>

#include <cstring>

using namespace std;
using namespace tinyxml2;


const std::string Destination::DST_BALISE_NAME("DST");
const std::string Destination::DSTNAME_BALISE_NAME("NAME");
const std::string Destination::DSTNUMBER_ATTRIBUT_NAME("number");


Destination::Destination(const list<string> &destinationNames) :
                         AbstractBuildableObject(),
                         m_destinationNames(destinationNames)
{
    //ctor
    checkBuildable();
}

const list<string> &Destination::getDestinationNames() const
{
    return m_destinationNames;
}

const string Destination::getDestinationName(const int index) const
{
    if(index < 0 || index >= (int) m_destinationNames.size())
    return string();

    list<string>::const_iterator it = m_destinationNames.begin();

    if (index > 0)
    advance(it, index);

    return *it;
}

void Destination::setDestinationNames(const list<string> &destinationNames)
{
    m_destinationNames.clear();
    m_destinationNames = destinationNames;

    checkBuildable();
}

void Destination::setDestinationName(const string &destinationName, const int index)
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

void Destination::addDestinationName(const string &destinationName)
{
    if(destinationName.empty())
    return;

    m_destinationNames.push_back(destinationName);

    checkBuildable();
}

void Destination::insertDestinationName(const string &destinationName, const int index)
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

void Destination::removeDestinationName(const string &destinationName)
{
    m_destinationNames.remove(destinationName);

    checkBuildable();
}


void Destination::removeDestinationName(const int index)
{
    list<string>::iterator it = m_destinationNames.begin();

    advance(it, index);

    m_destinationNames.erase(it);

    checkBuildable();
}


bool Destination::containsDestinationName(const string &destinationName) const
{
    list<string>::const_iterator it = find(m_destinationNames.begin(), m_destinationNames.end(), destinationName);
    if(it != m_destinationNames.end())
    return true;

    return false;
}

int Destination::indexOf(const string &destinationName, int offset)
{
    list<string>::iterator it = m_destinationNames.begin();

    advance(it, offset);

    it = indexOf(destinationName, it);

    if(it != m_destinationNames.end())
    return distance(m_destinationNames.begin(), it);

    return -1;
}

list<string>::iterator Destination::indexOf(const string &destinationName, list<string>::iterator &offset)
{
    return find(offset, m_destinationNames.end(), destinationName);
}

int Destination::getNumberOfDestination() const
{
    return m_destinationNames.size();
}

const char* Destination::getBuiltElementName() const
{
    return "Destination";
}

bool Destination::build(XMLDocument &doc, XMLElement *parent, const int number) const
{
    if(!isBuildable())
    return false;

    XMLElement *elm = doc.NewElement(DST_BALISE_NAME.c_str());
    if(elm == 0)
    return false;

    int nbOfDestination(getNumberOfDestination());
    if(nbOfDestination <= 0)
    return false;

    elm->SetAttribute(DSTNUMBER_ATTRIBUT_NAME.c_str(), nbOfDestination);

    for(int i(0); i < nbOfDestination; ++i)
    {
        XMLElement *nameElm = doc.NewElement(DSTNAME_BALISE_NAME.c_str());
        if(nameElm == 0)
        return false;

        nameElm->SetText(getDestinationName(i).c_str());
        elm->InsertEndChild(nameElm);
    }

    XMLElement *antecedant(0);
    antecedant = (parent != 0 ? parent->FirstChildElement(DST_BALISE_NAME.c_str()) : doc.FirstChildElement(DST_BALISE_NAME.c_str()));
    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    antecedant = antecedant->NextSiblingElement(DST_BALISE_NAME.c_str());


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

bool Destination::parse(XMLDocument &doc, XMLElement *parent, const int number)
{
    XMLElement *elm(0);

    elm = (parent != 0 ? parent->FirstChildElement(DST_BALISE_NAME.c_str()) : doc.FirstChildElement(DST_BALISE_NAME.c_str()));

    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    elm = elm->NextSiblingElement(DST_BALISE_NAME.c_str());

    if(elm == 0)
    return (m_isBuildable = false);


    if(elm->Attribute(DSTNUMBER_ATTRIBUT_NAME.c_str()) == 0)
    return (m_isBuildable = false);

    int tmpnumber;

    if(!XMLSuccess(elm->QueryIntAttribute(DSTNUMBER_ATTRIBUT_NAME.c_str(), &tmpnumber)) || tmpnumber <= 0)
    return (m_isBuildable = false);

    XMLElement *name = elm->FirstChildElement(DSTNAME_BALISE_NAME.c_str());

    while(name != 0)
    {
        m_destinationNames.push_back(name->GetText());
        name = name->NextSiblingElement(DSTNAME_BALISE_NAME.c_str());
    }

    if(getNumberOfDestination() != tmpnumber)
    return (m_isBuildable = false);

    checkBuildable();

    return m_isBuildable;
}

void Destination::checkBuildable()
{
    m_isBuildable = m_destinationNames.size() > 0;
}

