#include "JsonParser.h"
#include <iostream>
#include <fstream>

void GEngine::JsonToLevelParser::GetJsonFromLevel(const Json::String& levelName)
{
	Json::String path = "./assets/levels/" + levelName;
	std::ifstream file(path);

	Json::Reader reader;

	Json::Value completeJsonData;

	bool ok = reader.parse(file, completeJsonData,true);

	std::cout << "Completed json data : " << std::endl << completeJsonData << std::endl;
}
