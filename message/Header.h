#ifndef HEADER_H
#define HEADER_H

#include <message/AbstractBuildableObject.h>
#include <message/Destination.h>

class Header : public AbstractBuildableObject
{
    public:
    static const std::string HEADER_BALISE_NAME;
    static const std::string SRC_BALISE_NAME;
    static const std::string CMD_BALISE_NAME;

    protected:
        std::string m_sourceName;
        std::string m_commandName;
        Destination m_destinationNames;

    public:
        Header(std::string sourceName = std::string(),
               std::string commandName = std::string(),
               const Destination& destinationNames = Destination());

        const std::string& getSourceName() const;
        const std::string& getCommandName() const;
        const Destination& getDestinations() const;
        const Destination* getDestinationsPtr() const;

        void setSourceName(const std::string& sourceName);
        void setCommandName(const std::string& commandName);
        void setDestinations(const Destination& destinations);


        virtual const char* getBuiltElementName() const;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1);

    protected:
        virtual void checkBuildable();
};

#endif // HEADER_H
