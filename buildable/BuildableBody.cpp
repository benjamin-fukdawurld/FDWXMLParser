#include "BuildableBody.h"

#include "parsable/ParsableBody.h"

#include "conversion/byteConversion.h"

using namespace tinyxml2;


BuildableBody::BuildableBody(uint64_t bodySize, unsigned char *body) : AbstractXMLBuildableObject(),
                                                              m_bodySize(bodySize),
                                                              m_body(body)
{

}

BuildableBody::~BuildableBody()
{
    if(m_body != 0)
    {
        delete[] m_body;
    }
}

const uint64_t &BuildableBody::getBodysize() const
{
    return m_bodySize;
}

const unsigned char *BuildableBody::getBody() const
{
    return m_body;
}

void BuildableBody::setBody(const std::string &body)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = body.size();
    m_body = new unsigned char[m_bodySize];
    strToByteArray(m_body, &body);

    checkBuildable();
}

void BuildableBody::setBody(const std::vector<unsigned char> &body)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = body.size();
    m_body = new unsigned char[m_bodySize];

    for(uint64_t i(0); i < m_bodySize; ++i)
    m_body[i] = body[i];

    checkBuildable();
}

void BuildableBody::setBody(unsigned char *body, const uint64_t &bodySize)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = bodySize;
    m_body = body;

    checkBuildable();
}

const char *BuildableBody::getBuiltElementName() const
{
    return "ParsableBody";
}

bool BuildableBody::build(AbstractXMLParsableObject *built)
{
    if(built == 0 || strcmp(built->getParsedElementName(), "BuildableBody") != 0)
    return false;

    return build((ParsableBody*) built);
}

void BuildableBody::checkBuildable()
{
    m_isBuildable = (m_body != 0 && m_bodySize > 0) || (m_body == 0 && m_bodySize == 0);
}

bool BuildableBody::build(ParsableBody *built)
{
    XMLDocument doc;
    XMLElement *element = doc.NewElement(ParsableBody::BODY_BALISE_NAME.c_str());


    element->SetAttribute("bodysize", "" + m_bodySize);
    if(m_bodySize > 0)
    {
        std::string text(byteArrayToHexValuesString(m_body, m_bodySize));
        element->SetText(text.c_str());
    }

    built->setXMLlement(element);

    return false;
}



