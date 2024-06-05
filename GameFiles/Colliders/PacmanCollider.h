#ifndef PM_PACMAN_COLLIDER_H
#define PM_PACMAN_COLLIDER_H
#include "CollisionComponent.h"
#include "Subject.h"
#include <iostream>
namespace pacman
{

	class BaseStatePickupOverlap
	{
	public:
		BaseStatePickupOverlap() = default;
		virtual ~BaseStatePickupOverlap() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) = 0;
		virtual std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() = 0;
	private:
	};

	class WaitingStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		WaitingStateSmallPickupOverlap() = default;
		~WaitingStateSmallPickupOverlap() = default;

		void OnExit() override {}
		void OnEnter() override {}

		std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() override;;
	private:
	};

	class HasEatenStateSmallPickupOverlap final : public BaseStatePickupOverlap
	{
	public:
		HasEatenStateSmallPickupOverlap() = default;
		~HasEatenStateSmallPickupOverlap() = default;

		void OnEnter() override;
		void OnExit() override;

		std::unique_ptr<BaseStatePickupOverlap> Update(double elapsedSec) override;
		std::unique_ptr<BaseStatePickupOverlap> HandleOverlap() override;;
	private:
		double m_Timer{};
		double m_MaxTime{ 0.3 };
	};

	class PacmanCollider final : public amu::CollisionComponent, public amu::Subject
	{
	public:
		PacmanCollider(amu::GameObject* ownerObjectPtr);
		virtual ~PacmanCollider() override = default;

		PacmanCollider(PacmanCollider const&) = delete;
		PacmanCollider(PacmanCollider&&) = delete;
		PacmanCollider& operator=(PacmanCollider const&) = delete;
		PacmanCollider& operator=(PacmanCollider&&) = delete;

		void Update() override;

		void OnCollision(amu::CollisionComponent* otherCollider) override;
	private:
		std::unique_ptr<BaseStatePickupOverlap> m_StatePickupUPtr{};
	};

}
 
#endif //PM_PACMAN_COLLIDER_H