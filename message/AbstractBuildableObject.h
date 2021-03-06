#ifndef ABSTRACTBUILDABLEOBJECT_H
#define ABSTRACTBUILDABLEOBJECT_H


#include "message/FDWMessage.h"

#include "tinyxml/tinyxml2.h"

#include <iostream>



class FDWMessage::AbstractBuildableObject
{
    protected:
        bool m_isBuildable;



    public:
        AbstractBuildableObject();



        static bool XMLSuccess(const tinyxml2::XMLError &result);
        static const char *escapeCharacters(const std::string& xml);



        virtual bool isBuildable() const;

        virtual const char *getBuiltElementName() const = 0;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const = 0;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) = 0;

        virtual const char *toString() const;
        virtual bool fromString(const std::string& xml);
        virtual bool fromString(const char *xml, size_t size = (size_t) -1);
        virtual unsigned char *createSendable() const;
        virtual bool fromSendable(unsigned char **sendable, const bool doDelete = true);
        virtual bool save(const char *filePath);



    protected:
        virtual void checkBuildable() = 0;
};



template<typename T>
T &operator<<(T &out, const FDWMessage::AbstractBuildableObject &toPrint)
{
    return out << toPrint.toString();
}

template<typename T>
T &operator>>(T &in, FDWMessage::AbstractBuildableObject &toRead)
{
    std::string str;

    in >> str;

    toRead.fromString(str);

    return in;
}

#endif // ABSTRACTBUILDABLEOBJECT_H
