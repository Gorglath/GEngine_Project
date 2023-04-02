#pragma once
#include "GameEntity.h"
#include "Descent/DescentEntityFactory.h"
#include "Descent/DescentJsonParsingData.h"
#include <vector>
#include <string>
namespace GEngine 
{
	class JsonToLevelParser
	{
        static Descent::EDescentObjectType StringToDescentEnum(const std::string& objectType);
		static GameEntity BuildGameEntityFromType(const std::string& objectName, const std::string& objectType, const std::string& objectData, const TransformDataStruct& transformData);
	public:
		JsonToLevelParser() = delete;
		~JsonToLevelParser() = delete;
		JsonToLevelParser(const JsonToLevelParser&) = delete;

		static std::vector<GameEntity> GetGameEntitiesFromLevelJson(const std::string& levelName);
	};
}
