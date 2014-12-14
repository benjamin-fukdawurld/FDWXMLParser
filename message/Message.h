#ifndef MESSAGE_H
#define MESSAGE_H


#include "message/FDWMessage.h"
#include "message/AbstractBuildableObject.h"
#include "message/Header.h"
#include "message/Body.h"



class FDWMessage::Message : public FDWMessage::AbstractBuildableObject
{
    public:
        static const std::string DECLARATION_VERSION_ATTRIBUTE;
        static const std::string DECLARATION_ENCODING_ATTRIBUTE;
        static const std::string DECLARATION_STANDALONE_ATTRIBUTE;
        static const std::string MESSAGE_BALISE_NAME;
        static const std::string MESSAGE_XMLNS_ATTRIBUTE_NAME;
        static const std::string MESSAGE_XSI_ATTRIBUTE_NAME;
        static const std::string MESSAGE_XMLNS_ATTRIBUTE;
        static const std::string MESSAGE_XSI_ATTRIBUTE;


    protected:
        FDWMessage::Header m_header;
        FDWMessage::Body m_body;

    public:
        Message(std::string sourceName = std::string(),
                std::string commandName = std::string(),
                const FDWMessage::Destination& destinationNames = FDWMessage::Destination(),
                uint64_t bodySize = 0,
                unsigned char *body = 0);


        static const char* getDeclaration();


        FDWMessage::Header getHeader();
        FDWMessage::Body getBody();

        virtual const char *getBuiltElementName() const;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1);


    protected:
        virtual void checkBuildable();

};

#endif // MESSAGE_H
