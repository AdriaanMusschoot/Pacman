#include "PacmanCollider.h"
#include <iostream>
pacman::PacmanCollider::PacmanCollider(amu::GameObject* ownerObjectPtr)
	: CollisionComponent(ownerObjectPtr, std::vector<std::string>{ "PickupSmall" })
{
}

void pacman::PacmanCollider::OnCollision(amu::CollisionComponent*)
{
	std::cout << "Pacman overlapped\n";
}
