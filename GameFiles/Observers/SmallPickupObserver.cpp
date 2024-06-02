#include "SmallPickupObserver.h"

pacman::SmallPickupObserver::SmallPickupObserver(amu::GameObject* ownerPtr)
	: Component(ownerPtr)
{
}

void pacman::SmallPickupObserver::Notify(amu::IObserver::Event, amu::Subject* subjectPtr) const
{
	std::cout << "This is old and not good";
}
