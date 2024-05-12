#include "SmallPickupObserver.h"

void pacman::SmallPickupObserver::Notify(amu::IObserver::Event, amu::Subject*) const
{
	std::cout << "Overlapped\n";
}
