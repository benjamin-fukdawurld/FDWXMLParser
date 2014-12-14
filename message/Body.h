#ifndef BODY_H
#define BODY_H


#include "message/FDWMessage.h"
#include "message/AbstractBuildableObject.h"

#include <stdint.h>

#include <string>
#include <vector>



class FDWMessage::Body : public AbstractBuildableObject
{
    public:
        static const std::string BODY_BALISE_NAME;
        static const std::string BODYSIZE_ATTRIBUTE_NAME;



    protected:
        uint64_t m_bodySize;
        unsigned char *m_body;



    public:
        Body(uint64_t bodySize = 0, unsigned char *body = 0);

        virtual ~Body();

        const uint64_t &getBodysize() const;
        const unsigned char *getBody() const;

        void setBody(const std::string &body);
        void setBody(const std::vector<unsigned char> &body);
        void setBody(unsigned char *body, const uint64_t &bodySize);

        const char *getBuiltElementName() const;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1);



    protected:
        virtual void checkBuildable();
};

#endif // BODY_H
