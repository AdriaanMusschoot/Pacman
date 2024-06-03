#ifndef PM_PACMAN_COLLIDER_H
#define PM_PACMAN_COLLIDER_H
#include "CollisionComponent.h"
#include "Subject.h"
#include <iostream>
namespace pacman
{

	class BaseStateSmallPickupOverlap
	{
	public:
		BaseStateSmallPickupOverlap() = default;
		virtual ~BaseStateSmallPickupOverlap() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual std::unique_ptr<BaseStateSmallPickupOverlap> Update(double elapsedSec) = 0;
		virtual std::unique_ptr<BaseStateSmallPickupOverlap> HandleOverlap() = 0;
	private:
	};

	class WaitingStateSmallPickupOverlap final : public BaseStateSmallPickupOverlap
	{
	public:
		WaitingStateSmallPickupOverlap() = default;
		~WaitingStateSmallPickupOverlap() = default;

		void OnExit() override {}
		void OnEnter() override {}

		std::unique_ptr<BaseStateSmallPickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStateSmallPickupOverlap> HandleOverlap() override;;
	private:
	};

	class HasEatenStateSmallPickupOverlap final : public BaseStateSmallPickupOverlap
	{
	public:
		HasEatenStateSmallPickupOverlap() = default;
		~HasEatenStateSmallPickupOverlap() = default;

		void OnEnter() override;
		void OnExit() override;

		std::unique_ptr<BaseStateSmallPickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStateSmallPickupOverlap> HandleOverlap() override;;
	private:
		double m_Timer{};
		double m_MaxTime{ 0.6 };
	};

	class PacmanCollider final : public amu::CollisionComponent, public amu::Subject
	{
	public:
		PacmanCollider(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanCollider() override = default;

		PacmanCollider(PacmanCollider const& other) = delete;
		PacmanCollider(PacmanCollider&& other) = delete;
		PacmanCollider& operator=(PacmanCollider const& other) = delete;
		PacmanCollider& operator=(PacmanCollider&& other) = delete;

		void Update() override;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
		std::unique_ptr<BaseStateSmallPickupOverlap> m_StateSmallPickupUPtr{};
	};

}
 
#endif //PM_PACMAN_COLLIDER_H