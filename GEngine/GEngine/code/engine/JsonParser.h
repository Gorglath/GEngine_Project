#pragma once
#include "json/json.h"
namespace GEngine 
{
	class JsonToLevelParser
	{
	public:
		JsonToLevelParser() = delete;
		~JsonToLevelParser() = delete;
		JsonToLevelParser(const JsonToLevelParser&) = delete;

		static void GetJsonFromLevel(const Json::String& levelName);
	};
}
