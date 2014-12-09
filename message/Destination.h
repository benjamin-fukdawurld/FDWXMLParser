#ifndef DESTINATION_H
#define DESTINATION_H


#include "message/AbstractBuildableObject.h"

#include <list>
#include <string>



class Destination : public AbstractBuildableObject
{
    public:
        static const std::string DST_BALISE_NAME;
        static const std::string DSTNAME_BALISE_NAME;
        static const std::string DSTNUMBER_ATTRIBUT_NAME;

    protected:
        std::list<std::string> m_destinationNames;

    public:
        Destination(const std::list<std::string> &destinationNames = std::list<std::string>());

        const std::list<std::string> &getDestinationNames() const;
        const std::string getDestinationName(const int index) const;

        void setDestinationNames(const std::list<std::string> &destinationNames);
        void setDestinationName(const std::string &destinationName, const int index = -1);

        void addDestinationName(const std::string &destinationName);

        void insertDestinationName(const std::string &destinationName, const int index);

        void removeDestinationName(const std::string &destinationName);
        void removeDestinationName(const int index);

        bool containsDestinationName(const std::string &destinationName) const;

        int indexOf(const std::string &destinationName, int offset);
        std::list<std::string>::iterator indexOf(const std::string &destinationName, std::list<std::string>::iterator &offset);


        int getNumberOfDestination() const;
        virtual const char *getBuiltElementName() const;
        virtual bool build(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1) const;
        virtual bool parse(tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *parent = 0, const int number = 1);
        

    protected:
        virtual void checkBuildable();
};

#endif // DESTINATION_H
