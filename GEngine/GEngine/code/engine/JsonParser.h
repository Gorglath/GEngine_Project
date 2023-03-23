#pragma once
#include "json/json.h"
#include <vector>
namespace GEngine 
{
	class GameEntity;
	class JsonToLevelParser
	{
	public:
		JsonToLevelParser() = delete;
		~JsonToLevelParser() = delete;
		JsonToLevelParser(const JsonToLevelParser&) = delete;

		static void GetGameEntitiesFromLevelJson(const Json::String& levelName);
	};
}
