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
    if(!isParsable())
    return 0;

    return m_xmlElement->GetText();
}

const vector<unsigned char> ParsableBody::getParsedBody() const
{
    if(!isParsable())
    return vector<unsigned char>();

    return hexValuesStringToByteVector(getUnparsedBody());
}

bool ParsableBody::parse(AbstractXMLBuildableObject *parsed) const
{
    if(parsed == 0 || strcmp(parsed->getBuiltElementName(), "ParsableBody") != 0)
    return false;

    return parse((BuildableBody*) parsed);
}

const char* ParsableBody::getXMLBodySizeAttribute() const
{
    if(!isParsable())
    return 0;

    return m_xmlElement->Attribute("bodysize");
}

void ParsableBody::init()
{
    m_xmlDocument = 0;
    m_isParsable = false;

    if(!hasElement())
    return;

    m_xmlDocument = m_xmlElement->GetDocument();

    m_sizeOfParsedBody = 0;
    {
        const char *xmltxt = m_xmlElement->GetText();
        for(int i(0); *(xmltxt + i) != '\0'; ++i)
        ++m_sizeOfParsedBody;
    }

    {
        uint64_t sizeAttribute(0);
        {
            const char *tmp(m_xmlElement->Attribute("bodysize"));

            for(int i(0); *(tmp + i) != '\0'; ++i)
            ++sizeAttribute;

            if(tmp == 0 || sizeAttribute == 0)
            return;

            sizeAttribute = 0;

            istringstream iss(tmp);

            iss >> sizeAttribute;
        }

        m_isParsable = m_sizeOfParsedBody == sizeAttribute;
    }
}

bool ParsableBody::parse(BuildableBody *parsed) const
{
    if(!isParsable() || parsed == 0)
    return false;

    parsed->setBody(getParsedBody());

    return parsed->isBuildable();
}


