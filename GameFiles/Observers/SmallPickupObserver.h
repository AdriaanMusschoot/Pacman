#ifndef PM_SMALL_PICKUP_OBSERVER
#define PM_SMALL_PICKUP_OBSERVER

#include "IObserver.h"
#include "Configuration.h"

namespace pacman
{

	class SmallPickupObserver final :  public amu::IObserver
	{
	public:
		SmallPickupObserver() = default;
		~SmallPickupObserver() = default;

		SmallPickupObserver(SmallPickupObserver const&) = delete;
		SmallPickupObserver(SmallPickupObserver&&) = delete;
		SmallPickupObserver& operator=(SmallPickupObserver const&) = delete;
		SmallPickupObserver& operator=(SmallPickupObserver&&) = delete;

		void Notify(amu::IObserver::Event eventType, amu::Subject* subjectPtr) const override;
		void NotifyDestruction() override {};
	private:
	};

}

#endif //PM_SMALL_PICKUP_OBSERVER
