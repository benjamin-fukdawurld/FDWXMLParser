#include <iostream>
#include <iomanip>
#include <vector>

#include <sstream>

#include "tinyxml/tinyxml2.h"

#include "buildable/BuildableHeader.h"
#include "parsable/ParsableHeader.h"


#include "buildable/BuildableBody.h"
#include "parsable/ParsableBody.h"


#include "conversion/byteConversion.h"

using namespace std;
using namespace tinyxml2;

bool XMLSuccess(const XMLError& result)
{
    if(result == XML_SUCCESS || result == XML_NO_ERROR)
    return true;

    return false;
}

XMLNode *getMessage(XMLDocument& document)
{
    return document.FirstChildElement("MESSAGE");
}

XMLElement* getHeader(XMLNode* message)
{
    return message->FirstChildElement("HEADER");
}

XMLElement* getBody(XMLNode* message)
{
    return message->FirstChildElement("BODY");
}

int getBodySize(XMLElement* body)
{
    int ret(-1);
    body->QueryIntAttribute("bodysize", &ret);

    return ret;
}

XMLElement* getElementFromHeader(const char* elementName, XMLNode* header)
{
    return header->FirstChildElement(elementName);
}

XMLElement* getSRC(XMLElement* header)
{
    return getElementFromHeader("SRC", header);
}

XMLElement* getCMD(XMLElement* header)
{
    return getElementFromHeader("CMD", header);
}

XMLElement* getDSTList(XMLElement* header)
{
    return getElementFromHeader("DST", header);
}

int getDSTListSize(XMLElement* dstList)
{
    int ret(-1);
    dstList->QueryIntAttribute("number", &ret);

    return ret;
}

vector<XMLElement*> getDST(vector<XMLElement*>& dst, XMLElement* dstList)
{
    dst.clear();
    XMLElement *current = dstList->FirstChildElement("NAME");
    while(current != 0)
    {
        dst.push_back(current);
        current = current->NextSiblingElement("NAME");
    }

    return dst;
}

int oldmain()
{
    XMLDocument doc;
    if (!XMLSuccess(doc.LoadFile("message_example.xml")))
    return EXIT_FAILURE;

    XMLNode* message = getMessage(doc);
    if (message == 0)
    return EXIT_FAILURE;

    XMLElement* header = getHeader(message);

    if(header == 0)
    return EXIT_FAILURE;

    XMLElement* body = getBody(message);

    XMLElement* src = getSRC(header);
    XMLElement* cmd = getCMD(header);

    XMLElement* dstList = getDSTList(header);
    vector<XMLElement*> dst;
    getDST(dst, dstList);
    int dstNumber = getDSTListSize(dstList);


    cout << "SRC : " << src->GetText() << endl;
    cout << "DST (" << dstNumber << ") : " << endl;
    int c(dst.size());
    c = (c > dstNumber ? dstNumber : c);

    for(int i(0); i < c; i++)
    cout << i + 1 << '/' << dstNumber << "\t" << dst[i]->GetText() << endl;

    cout << "CMD : " << cmd->GetText() << endl;

    cout << getBodySize(body) << endl;

    return 0;
}


string bytesToHexString(const unsigned char* byteArray, const size_t arrayLength)
{
    if(arrayLength < 1)
    return string();

    ostringstream oss;

    for(size_t i(0); i < arrayLength; ++i)
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(byteArray[i]) << std::endl;

    string str(oss.str());

    return str;
}

unsigned char *hexStringToBytes(const char* hexString, unsigned char *byteArray, const size_t arrayLength)
{
    istringstream iss(hexString);
    for(size_t i(0); i < arrayLength; ++i)
    {
        unsigned int tmp;
        iss >> hex >> tmp;
        byteArray[i] = static_cast<unsigned char>(tmp);
    }

    return byteArray;
}


int oldmain2()
{
    ostringstream oss;
    string strin("A sample string"), strout, tmp;

    size_t s(strin.size());
    char *cstr(const_cast<char*>(strin.c_str()));

    oss << bytesToHexString((unsigned char*) cstr, strin.size());

    cout << "ici : " << oss.str() << endl;

    {
        string tmp;
        unsigned char* byteArray(new unsigned char[s]);

        hexStringToBytes(oss.str().c_str(), byteArray, s);
        strout += (char*) byteArray;

        delete[] byteArray;
    }

    cout << strout << endl;

    return 0;
}

/*int main()
{
    XMLDocument doc;

    cout << "1" << endl;

    if (!XMLSuccess(doc.LoadFile("message_example.xml")))
    return EXIT_FAILURE;

    cout << "2" << endl;

    XMLPrinter printer;
    doc.Print(&printer);

    cout << "3" << endl;

    string tmp(printer.CStr());

    cout << tmp << endl;

    const char* text = doc.FirstChildElement("MESSAGE")->FirstChildElement("BODY")->GetText();

    cout << "4" << endl;

    cout << text << endl;

    cout << "5" << endl;
}*/

int oldmain4()
{
    ParsableHeader pheader;
    BuildableHeader bheader;

    /*for(int i(0); i < 17; ++i)
    {
        toOtherBase(cout, i, "hex", 2, '0');

        cout << " " << hex << setw(2) << setfill('0');
        cout << i << endl;
    }*/

    string str("coucou les cocos ça va???"), str2;

    unsigned char *tmp = 0;

    tmp = new unsigned char[str.size()];

    toByteArray(tmp, &str);

    fromByteArray(&str2, tmp);

    delete[] tmp;

    cout << str << " => "<< str2 << endl;


    return 0;
}

int main()
{
    XMLDocument doc;
    if (!XMLSuccess(doc.LoadFile("message_example.xml")))
    return EXIT_FAILURE;


    BuildableDestination dest();
    ParsableDestination pdest(&doc);

    if(pdest.isParsable())
    cout << "coucou" << endl;

    /*std::string tmp("bande d'enfoirés!!!");
    XMLDocument doc;
    BuildableBody bbody;
    ParsableBody pbody(&doc);

    bbody.setBody(tmp);

    bbody.build((AbstractXMLParsableObject*) &pbody);

    cout << pbody.getInnerText() << endl << endl;
    cout << pbody.toString() << endl;*/

    return 0;
}
