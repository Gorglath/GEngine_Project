#include "JsonParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace GEngine;
//first get the file completly
//Split the file into readable jsons.
//Parse each json into his corresponding type.

//void GEngine::JsonToLevelParser::GetJsonFromLevel(const Json::String& levelName)
//{
//	Json::String path = "./assets/levels/" + levelName;
//	std::ifstream file(path);
//
//	Json::Reader reader;
//
//	Json::Value completeJsonData;
//
//	bool ok = reader.parse(file, completeJsonData,true);
//
//	std::cout << "Completed json data : " << std::endl << completeJsonData << std::endl;
//}

void GEngine::JsonToLevelParser::GetGameEntitiesFromLevelJson(const Json::String& levelName)
{
    std::ifstream inFile;
    Json::String path = "./assets/levels/" + levelName;
    inFile.open(path);

    std::stringstream strStream;
    strStream << inFile.rdbuf();

    std::string str = strStream.str();
    std::string segment;
    std::vector<std::string> splitObjects;
    while (std::getline(strStream, segment, '='))
    {
        splitObjects.push_back(segment);
    }
    
    std::string globalData;
    std::string placeHolder;
    std::string transformData;
    for (size_t i = 0; i < splitObjects.size(); i++)
    {
        globalData = splitObjects[i].substr(0, splitObjects[i].find('~'));
        placeHolder = splitObjects[i].substr(splitObjects[i].find('~') + 1, splitObjects[i].size());
        transformData = placeHolder.substr(0, placeHolder.find('~'));
    }
}
