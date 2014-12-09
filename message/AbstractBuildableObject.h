#ifndef ABSTRACTBUILDABLEOBJECT_H
#define ABSTRACTBUILDABLEOBJECT_H

#include <iostream>

#include "tinyxml/tinyxml2.h"

class AbstractBuildableObject
{
    protected:
        bool m_isBuildable;

    public:
        AbstractBuildableObject();


        static bool XMLSuccess(const tinyxml2::XMLError &result);


        virtual bool isBuildable() const;
        virtual const char *getBuiltElementName() const = 0;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const = 0;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) = 0;
        virtual const char *toString() const;
        virtual unsigned char *createSendable() const;

    protected:
        virtual void checkBuildable() = 0;
};

template<typename T>
T &operator<<(T &out, const AbstractBuildableObject &toPrint)
{
    return out << toPrint.toString();
}

#endif // ABSTRACTBUILDABLEOBJECT_H