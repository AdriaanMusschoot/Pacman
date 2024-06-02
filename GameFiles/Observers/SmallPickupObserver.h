#ifndef PM_SMALL_PICKUP_OBSERVER
#define PM_SMALL_PICKUP_OBSERVER

#include "IObserver.h"
#include "Configuration.h"
#include "Component.h"
#include "GameObject.h"
#include "Subject.h"
namespace pacman
{

	class SmallPickupObserver final : public amu::Component, public amu::IObserver
	{
	public:
		SmallPickupObserver(amu::GameObject* ownerPtr);
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
