#include "ParsableBody.h"

const std::string ParsableBody::BODY_BALISE_NAME("BODY");

ParsableBody::ParsableBody(tinyxml2::XMLElement *selfElement) : AbstractXMLParsableObject(selfElement)
{
    init();
}

ParsableBody::ParsableBody(tinyxml2::XMLNode *parent) : AbstractXMLParsableObject(BODY_BALISE_NAME.c_str(), parent)
{
    init();
}

uint64_t ParsableBody::getBodySize() const
{
    if(isParsable())
    return m_xmlBodysize;

    return 0;
}

const char *ParsableBody::getParsedElementName() const
{
    return "BuildableBody";
}

bool ParsableBody::parse(AbstractXMLBuildableObject *parsed) const
{
    return false;
}

void ParsableBody::init()
{

}


