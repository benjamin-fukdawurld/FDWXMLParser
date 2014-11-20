#ifndef ABSTRACTXMLBUILDABLEOBJECT_H
#define ABSTRACTXMLBUILDABLEOBJECT_H

class AbstractXMLParsableObject;

class AbstractXMLBuildableObject
{
    protected:
        bool m_isBuildable;

    public:
        AbstractXMLBuildableObject();

        virtual bool isBuildable() const;
        virtual const char* getBuiltElementName() const = 0;
        virtual bool build(AbstractXMLParsableObject* built) = 0;

    protected:
        virtual void checkBuildable() = 0;
};

#endif // ABSTRACTXMLBUILDABLEOBJECT_H
