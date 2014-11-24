#include "ParsableBody.h"

#include <sstream>


#include "buildable/BuildableBody.h"

#include "conversion/byteConversion.h"


using namespace std;
using namespace tinyxml2;

const std::string ParsableBody::BODY_BALISE_NAME("BODY");

ParsableBody::ParsableBody(XMLElement *selfElement) : AbstractXMLParsableObject(selfElement)
{
    init();
}

ParsableBody::ParsableBody(XMLNode *parent) : AbstractXMLParsableObject(BODY_BALISE_NAME.c_str(), parent)
{
    init();
}

uint64_t ParsableBody::getSizeOfBody() const
{
    if(!isParsable())
    return 0;

    return m_sizeOfParsedBody;
}

const char *ParsableBody::getParsedElementName() const
{
    return "BuildableBody";
}

const char *ParsableBody::getUnparsedBody() const
{
    return m_xmlElement->GetText();
}

const std::vector<unsigned char> ParsableBody::getParsedBody() const
{
    return hexValuesStringToByteVector(getUnparsedBody());
}

bool ParsableBody::parse(AbstractXMLBuildableObject *parsed) const
{
    if(parsed == NULL || strcmp(parsed->getBuiltElementName(), "ParsableBody") != 0)
    return false;

    return parse((BuildableBody*) parsed);
}

const char* ParsableBody::getXMLBodySizeAttribute() const
{
    if(isParsable())
    return m_xmlElement->Attribute("bodysize");

    return 0;
}

void ParsableBody::init()
{
    m_sizeOfParsedBody = strlen(m_xmlElement->GetText());
    m_isParsable = false;


    uint64_t sizeAttribute(0);

    const char *tmp(getXMLBodySizeAttribute());
    if(strlen(tmp) == 0)
    return;

    istringstream iss(tmp);

    iss >> sizeAttribute;



    m_isParsable = m_sizeOfParsedBody != sizeAttribute;
}

bool ParsableBody::parse(BuildableBody *parsed) const
{
    if(!isParsable() || parsed == NULL)
    return false;

    parsed->setBody(getParsedBody());

    return parsed->isBuildable();
}


