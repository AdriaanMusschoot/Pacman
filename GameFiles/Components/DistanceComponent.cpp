#include "DistanceComponent.h"

pacman::DistanceComponent::DistanceComponent(amu::GameObject* ownerObjectPtr)
    : amu::Component(ownerObjectPtr)
{
}

bool pacman::DistanceComponent::Check(glm::vec2 const& center1, glm::vec2 const& center2, std::float_t const& distance)
{
    double x{ center1.x - center2.x };
    double y{ center1.y - center2.y };
    return x * x + y * y < distance * distance;
}
