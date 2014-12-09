#include "AbstractBuildableObject.h"

#include "conversion/byteConversion.h"

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





bool AbstractBuildableObject::XMLSuccess(const tinyxml2::XMLError& result)
{
    if(result == tinyxml2::XML_SUCCESS || result == tinyxml2::XML_NO_ERROR)
    return true;

    return false;
}

