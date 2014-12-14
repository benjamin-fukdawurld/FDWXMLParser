#include "AbstractBuildableObject.h"

#include <algorithm>

#include "conversion/byteConversion.h"



using namespace std;
using namespace FDWMessage;




AbstractBuildableObject::AbstractBuildableObject() : m_isBuildable(false){}





bool AbstractBuildableObject::isBuildable() const
{
    return m_isBuildable;
}





const char *AbstractBuildableObject::toString() const
{
    tinyxml2::XMLDocument doc;
    build(doc);

    tinyxml2::XMLPrinter printer;

    doc.Print(&printer);

    std::string str(printer.CStr());

    return str.c_str();
}





bool AbstractBuildableObject::fromString(const string &xml)
{
    return fromString(xml.c_str(), xml.size());
}





bool AbstractBuildableObject::fromString(const char *xml, size_t size)
{

    tinyxml2::XMLDocument doc;
    if(XMLSuccess(doc.Parse(xml, size)))
    return parse(doc);

    return false;
}





unsigned char *AbstractBuildableObject::createSendable() const
{
    std::string str(toString());
    unsigned char *ret(0);

    {
        uint64_t size(str.size() * sizeof(char));
        size += sizeof(uint64_t);
        ret = new unsigned char[size];
        toByteArray(ret, &size);
    }

    toByteArray(ret + sizeof(uint64_t), str.c_str());

    return ret;
}





bool AbstractBuildableObject::fromSendable(unsigned char **sendable, const bool doDelete)
{
    if(*sendable == 0)
    return false;

    uint64_t size(0);

    if(fromByteArray<uint64_t>(&size, *sendable, sizeof(uint64_t)) == 0)
    return false;

    if(size <= 0)
    return false;

    size -= sizeof(uint64_t);
    char *received = new char[size + 1];
    received[size] = '\0';

    if(fromByteArray(received, *sendable + sizeof(uint64_t), size) == 0)
    {
        delete[] received;
        return false;
    }

    bool ret(false);
    ret = fromString(received, size + 1);
    delete[] received;

    if(ret && doDelete)
    {
        delete[] *sendable;
        *sendable = 0;
    }

    return ret;
}



bool AbstractBuildableObject::save(const char *filePath)
{
    tinyxml2::XMLDocument doc;
    if(filePath != 0 && build(doc))
    {
        return XMLSuccess(doc.SaveFile(filePath));
    }

    return false;
}





bool AbstractBuildableObject::XMLSuccess(const tinyxml2::XMLError &result)
{
    if(result == tinyxml2::XML_SUCCESS || result == tinyxml2::XML_NO_ERROR)
    return true;

    return false;
}

const char *AbstractBuildableObject::escapeCharacters(const string &xml)
{
    string ret(xml);

    for(size_t i(0), c(ret.size()); i < c; ++i)
    {
        switch(ret.at(i))
        {
            case '&':
                ret.erase(ret.begin() + i);
                ret.insert(i, "&amp", 4);
            break;

            case '<':
                ret.erase(ret.begin() + i);
                ret.insert(i, "&lt", 3);
            break;

            case '>':
                ret.erase(ret.begin() + i);
                ret.insert(i, "&gt", 4);
            break;

            case '"':
                ret.erase(ret.begin() + i);
                ret.insert(i, "&quot", 5);
            break;

            case '\'':
                ret.erase(ret.begin() + i);
                ret.insert(i, "&apos", 5);
            break;

            default:
            break;
        }
    }

    return ret.c_str();
}

