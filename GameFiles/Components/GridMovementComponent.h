#ifndef PM_GRID_MOVEMENT_COMPONENT_H
#define PM_GRID_MOVEMENT_COMPONENT_H

#include "Component.h"
#include "Configuration.h"
#include "PlayFieldGridComponent.h"
#include "TransformComponent.h"

namespace pacman
{

	class IMovementState
	{
	public:
		IMovementState() = default;
		virtual ~IMovementState() = default;

		IMovementState(IMovementState const& other) = delete;
		IMovementState(IMovementState&& other) = delete;
		IMovementState& operator=(IMovementState const& other) = delete;
		IMovementState& operator=(IMovementState&& other) = delete;

		virtual void Update(amu::GameObject * gameObjectPtr) = 0;
	private:
	};

	class MovementIdle final : public IMovementState
	{
	public:
		MovementIdle() = default;
		virtual ~MovementIdle() = default;

		MovementIdle(MovementIdle const& other) = delete;
		MovementIdle(MovementIdle&& other) = delete;
		MovementIdle& operator=(MovementIdle const& other) = delete;
		MovementIdle& operator=(MovementIdle&& other) = delete;

		virtual void Update(amu::GameObject * gameObjectPtr) override;
	private:
	};

	class MovementUp final : public IMovementState
	{
	public:
		MovementUp() = default;
		virtual ~MovementUp() = default;

		MovementUp(MovementUp const& other) = delete;
		MovementUp(MovementUp&& other) = delete;
		MovementUp& operator=(MovementUp const& other) = delete;
		MovementUp& operator=(MovementUp&& other) = delete;

		virtual void Update(amu::GameObject * gameObjectPtr) override;
	private:
		amu::TransformComponent* m_TransformPtr{ nullptr };
	};

	class MovementDown final : public IMovementState
	{
	public:
		MovementDown() = default;
		virtual ~MovementDown() = default;

		MovementDown(MovementDown const& other) = delete;
		MovementDown(MovementDown&& other) = delete;
		MovementDown& operator=(MovementDown const& other) = delete;
		MovementDown& operator=(MovementDown&& other) = delete;

		virtual void Update(amu::GameObject * gameObjectPtr) override;
	private:
		amu::TransformComponent* m_TransformPtr{ nullptr };
	};

	class MovementLeft final : public IMovementState
	{
	public:
		MovementLeft() = default;
		virtual ~MovementLeft() = default;

		MovementLeft(MovementLeft const& other) = delete;
		MovementLeft(MovementLeft&& other) = delete;
		MovementLeft& operator=(MovementLeft const& other) = delete;
		MovementLeft& operator=(MovementLeft&& other) = delete;

		virtual void Update(amu::GameObject * gameObjectPtr) override;
	private:
		amu::TransformComponent* m_TransformPtr{ nullptr };
	};

	class MovementRight final : public IMovementState
	{
	public:
		MovementRight() = default;
		virtual ~MovementRight() = default;

		MovementRight(MovementRight const& other) = delete;
		MovementRight(MovementRight&& other) = delete;
		MovementRight& operator=(MovementRight const& other) = delete;
		MovementRight& operator=(MovementRight&& other) = delete;

		virtual void Update(amu::GameObject* gameObjectPtr) override;
	private:
		amu::TransformComponent* m_TransformPtr{ nullptr };
	};

	class GridMovementComponent final : public amu::Component
	{
	public:
		GridMovementComponent(amu::GameObject* gameObjectPtr, PlayFieldGridComponent* playFieldGridPtr);
		virtual ~GridMovementComponent() override = default;

		GridMovementComponent(GridMovementComponent const& other) = delete;
		GridMovementComponent(GridMovementComponent&& other) = delete;
		GridMovementComponent& operator=(GridMovementComponent const& other) = delete;
		GridMovementComponent& operator=(GridMovementComponent&& other) = delete;

		void Update() override;
		void ChangeMovementState(std::shared_ptr<IMovementState> newStateSPtr);
	private:
		std::shared_ptr<IMovementState> m_CurrentMovementStateSPtr{ std::make_shared<MovementIdle>() };
		PlayFieldGridComponent* m_PlayFieldGridPtr{ nullptr };
	};

}

#endif //PM_GRID_MOVEMENT_COMPONENT_H