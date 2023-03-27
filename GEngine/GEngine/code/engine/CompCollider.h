#pragma once
#include "Component.h"
#include <vector>
namespace GEngine
{
	class CompCollider : public Component
	{
	public:
		static std::vector<CompCollider*> m_gColliders;

		CompCollider();

		void update() override;
		void destroy() override;
	};
}