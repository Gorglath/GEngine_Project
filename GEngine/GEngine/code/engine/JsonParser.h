#pragma once
#include "GameEntity.h"
#include "Descent/DescentEntityFactory.h"
//#include "Descent/"
#include <vector>
#include <string>
namespace GEngine 
{
	class JsonToLevelParser
	{

		GameEntity GetGameEntityFromType(const std::string& objectType, const std::string& objectData);
	public:
		JsonToLevelParser() = delete;
		~JsonToLevelParser() = delete;
		JsonToLevelParser(const JsonToLevelParser&) = delete;

		static std::vector<GameEntity> GetGameEntitiesFromLevelJson(const std::string& levelName);
	};
}
