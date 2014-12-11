#include "Body.h"

#include "conversion/byteConversion.h"

using namespace std;
using namespace tinyxml2;

const std::string Body::BODY_BALISE_NAME("BODY");
const std::string Body::BODYSIZE_ATTRIBUTE_NAME("bodysize");

Body::Body(uint64_t bodySize, unsigned char *body) : AbstractBuildableObject(),
                                                     m_bodySize(bodySize),
                                                     m_body(body)
{

}

Body::~Body()
{
    if(m_body != 0)
    {
        delete[] m_body;
    }
}

const uint64_t &Body::getBodysize() const
{
    return m_bodySize;
}

const unsigned char *Body::getBody() const
{
    return m_body;
}

void Body::setBody(const std::string &body)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = body.size();
    if(m_bodySize <= 0)
    return;

    m_body = new unsigned char[m_bodySize];
    strToByteArray(m_body, &body);

    checkBuildable();
}

void Body::setBody(const std::vector<unsigned char> &body)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = body.size();
    if(m_bodySize <= 0)
    return;

    m_body = new unsigned char[m_bodySize];

    for(uint64_t i(0); i < m_bodySize; ++i)
    m_body[i] = body[i];

    checkBuildable();
}

void Body::setBody(unsigned char *body, const uint64_t &bodySize)
{
    if(m_body != 0)
    delete[] m_body;

    m_bodySize = bodySize;
    if(m_bodySize <= 0)
    return;

    m_body = new unsigned char[m_bodySize];


    anyToByteArray(m_body, (void*) body, m_bodySize);

    checkBuildable();
}

const char *Body::getBuiltElementName() const
{
    return "Body";
}

bool Body::build(XMLDocument &doc, XMLElement *parent, const int number) const
{
    if(!isBuildable())
    return false;

    XMLElement *elm = doc.NewElement(BODY_BALISE_NAME.c_str());

    {
        ostringstream oss;
        oss << m_bodySize;
        elm->SetAttribute(BODYSIZE_ATTRIBUTE_NAME.c_str(), oss.str().c_str());
        if(m_bodySize > 0)
        {
            std::string text(byteArrayToHexValuesString(m_body, m_bodySize));
            elm->SetText(text.c_str());
        }
    }

    XMLElement *antecedant(0);
    antecedant = (parent != 0 ? parent->FirstChildElement(BODY_BALISE_NAME.c_str()) : doc.FirstChildElement(BODY_BALISE_NAME.c_str()));
    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    antecedant = antecedant->NextSiblingElement(BODY_BALISE_NAME.c_str());

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

bool Body::parse(XMLDocument &doc, XMLElement *parent, const int number)
{
    XMLElement *elm(0);

    elm = (parent != 0 ? parent->FirstChildElement(BODY_BALISE_NAME.c_str()) : doc.FirstChildElement(BODY_BALISE_NAME.c_str()));

    for(int i(0), c(number - 1); i < c && elm != 0; ++i)
    elm = elm->NextSiblingElement(BODY_BALISE_NAME.c_str());

    if(elm == 0)
    return (m_isBuildable = false);

    if(elm->Attribute(BODYSIZE_ATTRIBUTE_NAME.c_str()) == 0)
    return (m_isBuildable = false);

    {
        {
            const char * tmp = elm->Attribute(BODYSIZE_ATTRIBUTE_NAME.c_str());
            if(tmp == 0)
            return (m_isBuildable = false);

            istringstream iss(tmp);
            iss >> m_bodySize;

        }

        if(m_bodySize > 0)
        {
            vector<unsigned char> vect = hexValuesStringToByteVector(elm->GetText());

            if(vect.size() != m_bodySize)
            return (m_isBuildable = false);

            m_body = new unsigned char[m_bodySize];

            for(uint64_t i(0); i < m_bodySize; ++i)
            {
                m_body[i] = vect[i];
            }
        }
    }

    checkBuildable();

    return m_isBuildable;
}

void Body::checkBuildable()
{
    m_isBuildable = (m_body != 0 && m_bodySize > 0) || (m_body == 0 && m_bodySize == 0);
}

