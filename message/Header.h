#ifndef HEADER_H
#define HEADER_H


#include "message/FDWMessage.h"
#include "message/AbstractBuildableObject.h"
#include "message/Destination.h"



class FDWMessage::Header : public AbstractBuildableObject
{
    public:
        static const std::string HEADER_BALISE_NAME;
        static const std::string SRC_BALISE_NAME;
        static const std::string CMD_BALISE_NAME;



    protected:
        std::string m_sourceName;
        std::string m_commandName;
        FDWMessage::Destination m_destinationNames;



    public:
        Header(std::string sourceName = std::string(),
               std::string commandName = std::string(),
               const FDWMessage::Destination& destinationNames = FDWMessage::Destination());

        const std::string& getSourceName() const;
        const std::string& getCommandName() const;
        const FDWMessage::Destination& getDestinations() const;
        const FDWMessage::Destination* getDestinationsPtr() const;

        void setSourceName(const std::string& sourceName);
        void setCommandName(const std::string& commandName);
        void setDestinations(const FDWMessage::Destination& destinations);


        virtual const char* getBuiltElementName() const;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1);



    protected:
        virtual void checkBuildable();
};

#endif // HEADER_H
