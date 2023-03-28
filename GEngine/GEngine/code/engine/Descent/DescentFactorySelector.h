#pragma once
#include "DescentEntityFactory.h"
namespace GEngine 
{
	namespace Descent 
	{
		class DescentFactorySelector 
		{
		public:
			static GameEntity GetEntityFromType(const std::string& name, const std::string& type);
		};
	}
}