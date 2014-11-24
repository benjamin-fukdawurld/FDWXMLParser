#ifndef BUILDABLEBODY_H
#define BUILDABLEBODY_H

#include "buildable/AbstractXMLBuildableObject.h"

#include <vector>
#include <string>

#include <stdint.h>

class ParsableBody;

class BuildableBody : public AbstractXMLBuildableObject
{
    protected:
        uint64_t m_bodySize;
        unsigned char *m_body;

    public:
        BuildableBody(uint64_t bodySize = 0, unsigned char *body = 0);

        virtual ~BuildableBody();

        const uint64_t &getBodysize() const;
        const unsigned char *getBody() const;

        void setBody(const std::string &body);
        void setBody(const std::vector<unsigned char> &body);
        void setBody(unsigned char *body, const uint64_t &bodySize);

        const char *getBuiltElementName() const;
        virtual bool build(AbstractXMLParsableObject* built);

    protected:
        virtual void checkBuildable();
        virtual bool build(ParsableBody* built);
};

#endif // BUILDABLEBODY_H
