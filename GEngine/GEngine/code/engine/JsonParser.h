#pragma once
#include "GameEntity.h"
#include "Descent/DescentEntityFactory.h"
#include <vector>
#include <string>
namespace GEngine 
{
	class JsonToLevelParser
	{
	public:
		JsonToLevelParser() = delete;
		~JsonToLevelParser() = delete;
		JsonToLevelParser(const JsonToLevelParser&) = delete;

		static std::vector<GameEntity> GetGameEntitiesFromLevelJson(const std::string& levelName);
	};
}
