#ifndef PM_DISTANCE_COMPONENT_H
#define PM_DISTANCE_COMPONENT_H
#include "Configuration.h"
#include "Component.h"
#include <glm/glm.hpp>

namespace pacman
{

	class DistanceComponent final : public amu::Component
	{
	public:
		DistanceComponent(amu::GameObject* ownerObjectPtr);
		virtual ~DistanceComponent() override = default;

		DistanceComponent(DistanceComponent const& other) = delete;
		DistanceComponent(DistanceComponent&& other) = delete;
		DistanceComponent& operator=(DistanceComponent const& other) = delete;
		DistanceComponent& operator=(DistanceComponent&& other) = delete;

		bool Check(glm::vec2 const& center1, glm::vec2 const& center2, std::float_t const& distance);
	private:
	};

}

#endif //PM_DISTANCE_COMPONENT_H