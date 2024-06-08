//#include "BlinkyAIComponent.h"
//#include "GridMovementComponent.h"
//#include "GameTime.h"
//pacman::BlinkyAIComponent::BlinkyAIComponent(amu::GameObject* gameObjectPtr, amu::TransformComponent* pacmanTransformPtr)
//	: Component(gameObjectPtr)
//    , Subject(gameObjectPtr)
//	, m_PacmanTransformPtr{ pacmanTransformPtr }
//{
//    m_TransformPtr = GetComponentOwner()->GetComponent<amu::TransformComponent>();
//    m_GridMovementPtr = GetComponentOwner()->GetComponent<GridMovementComponent>();
//    m_GridMovementPtr->ChangeMovementState(config::VEC_LEFT);
//
//    m_GhostStateUPtrVec.emplace_back(std::make_unique<HuntPacmanState>());
//    m_GhostStateUPtrVec.emplace_back(std::make_unique<AvoidingPacmanState>());
//
//    m_CurrentStatePtr = GetState<HuntPacmanState>();
//}
//
//void pacman::BlinkyAIComponent::Update()
//{
//    if (BaseGhostState * newState{ m_CurrentStatePtr->Update(this, amu::GameTime::GetInstance().GetDeltaTime()) }; newState != nullptr)
//    {
//        m_CurrentStatePtr->OnExit(this);
//        m_CurrentStatePtr = newState;
//        m_CurrentStatePtr->OnEnter(this);
//    }
//}
//
//void pacman::BlinkyAIComponent::OnNotify(Event eventType, amu::Subject* subjectPtr)
//{
//    if (eventType == events::GHOST_INPUT_REQUIRED)
//    {
//        std::vector<glm::vec2> possibleDirectionVec{ m_GridMovementPtr->PossibleDirections() };
//        glm::vec2 const& optimalDirection{ m_CurrentStatePtr->GetOptimalDirection(this, possibleDirectionVec) };
//        if (optimalDirection != config::VEC_INVALID)
//        {
//            m_GridMovementPtr->ChangeMovementState(optimalDirection);
//            m_PreviousDirection = optimalDirection;
//        }
//        else
//        {
//            auto& safetyDirection = possibleDirectionVec[0];
//            m_GridMovementPtr->ChangeMovementState(safetyDirection);
//            m_PreviousDirection = optimalDirection;
//        }
//    }
//    if (BaseGhostState* newState{ m_CurrentStatePtr->HandleEvent(this, eventType, subjectPtr) }; newState != nullptr)
//    {
//        m_CurrentStatePtr->OnExit(this);
//        m_CurrentStatePtr = newState;
//        m_CurrentStatePtr->OnEnter(this);
//    }
//}
//
//glm::vec2 const& pacman::BlinkyAIComponent::GetPreviousDirection()
//{
//    return m_PreviousDirection;
//}
//
//glm::vec2 const& pacman::BlinkyAIComponent::GetPacmanPosition()
//{
//    return m_PacmanTransformPtr->GetWorldPosition();
//}
//
//glm::vec2 const& pacman::BlinkyAIComponent::GetGhostPosition()
//{
//    return m_TransformPtr->GetWorldPosition();
//}
//
//pacman::GridMovementComponent* pacman::BlinkyAIComponent::GetGridMoveComp() const
//{
//    return m_GridMovementPtr;
//}
//
//pacman::BaseGhostState* pacman::HuntPacmanState::Update(BlinkyAIComponent*, double)
//{
//    return nullptr;
//}
//
//pacman::BaseGhostState* pacman::HuntPacmanState::HandleOverlap(BlinkyAIComponent*, amu::CollisionComponent*)
//{
//    return nullptr;
//}
//
//pacman::BaseGhostState* pacman::HuntPacmanState::HandleEvent(BlinkyAIComponent* ownerPtr, amu::IObserver::Event eventType, amu::Subject*)
//{
//    if (eventType == events::PACMAN_EAT_BIG_PICKUP)
//    {
//        return ownerPtr->GetState<AvoidingPacmanState>();
//    }
//    if (eventType == events::GRID_DIRECTION_CHANGES)
//    {
//        ownerPtr->NotifyObservers(events::GRID_DIRECTION_CHANGES);
//    }
//    return nullptr;
//}
//
//glm::vec2 const& pacman::HuntPacmanState::GetOptimalDirection(BlinkyAIComponent* ownerPtr, std::vector<glm::vec2> const& possibleDirections)
//{
//    auto& pacmanPosition = ownerPtr->GetPacmanPosition();
//    auto& ghostPosition = ownerPtr->GetGhostPosition();
//    float deltaX = pacmanPosition.x - ghostPosition.x;
//    float deltaY = pacmanPosition.y - ghostPosition.y;
//
//
//    if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
//    {
//        m_PreferredDirectionVec[0] = (GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[1] = (GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[2] = (-GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[3] = (-GetOptimalVerticalDirection(deltaY));
//    }
//    else
//    {
//        m_PreferredDirectionVec[0] = (GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[1] = (GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[2] = (-GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[3] = (-GetOptimalHorizontalDirection(deltaX));
//    }
//    for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
//    {
//        if (preferredDirection == -ownerPtr->GetPreviousDirection())
//        {
//            continue;
//        }
//
//        if (std::any_of(possibleDirections.begin(), possibleDirections.end(),
//            [&](glm::vec2 const& possibleDirection)
//            {
//                return possibleDirection == preferredDirection;
//            }))
//        {
//            return preferredDirection;
//        }
//    }
//
//    return config::VEC_INVALID;
//}
//
//void pacman::AvoidingPacmanState::OnEnter(BlinkyAIComponent* ownerPtr)
//{
//    GridMovementComponent* gridCompPtr{ ownerPtr->GetGridMoveComp() };
//    gridCompPtr->ChangeMovementState(-gridCompPtr->GetCurrentDirection());
//    m_Timer = 0.0;
//}
//
//void pacman::AvoidingPacmanState::OnExit(BlinkyAIComponent*)
//{
//    m_Timer = 0.0;
//}
//
//pacman::BaseGhostState* pacman::AvoidingPacmanState::Update(BlinkyAIComponent* ownerPtr, double elapsedSec)
//{
//    
//}
//
//pacman::BaseGhostState* pacman::AvoidingPacmanState::HandleOverlap(BlinkyAIComponent*, amu::CollisionComponent*)
//{
//    return nullptr;
//}
//
//pacman::BaseGhostState* pacman::AvoidingPacmanState::HandleEvent(BlinkyAIComponent*, amu::IObserver::Event eventType, amu::Subject*)
//{
//    if (eventType == events::PACMAN_EAT_BIG_PICKUP)
//    {
//        m_Timer = 0.0;
//    }
//    return nullptr;
//}
//
//glm::vec2 const& pacman::AvoidingPacmanState::GetOptimalDirection(BlinkyAIComponent* ownerPtr, std::vector<glm::vec2> const& possibleDirections)
//{
//    auto& pacmanPosition = ownerPtr->GetPacmanPosition();
//    auto& ghostPosition = ownerPtr->GetGhostPosition();
//    float deltaX = pacmanPosition.x - ghostPosition.x;
//    float deltaY = pacmanPosition.y - ghostPosition.y;
//
//    if (GetOptimalAxis(deltaX, deltaY) == Axis::X)
//    {
//        m_PreferredDirectionVec[0] = (-GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[1] = (-GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[2] = (GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[3] = (GetOptimalHorizontalDirection(deltaX));
//    }
//    else
//    {
//        m_PreferredDirectionVec[0] = (-GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[1] = (-GetOptimalVerticalDirection(deltaY));
//        m_PreferredDirectionVec[2] = (GetOptimalHorizontalDirection(deltaX));
//        m_PreferredDirectionVec[3] = (GetOptimalVerticalDirection(deltaY));
//    }
//    for (glm::vec2 const& preferredDirection : m_PreferredDirectionVec)
//    {
//        if (preferredDirection == -ownerPtr->GetPreviousDirection())
//        {
//            continue;
//        }
//
//        if (std::any_of(possibleDirections.begin(), possibleDirections.end(),
//            [&](glm::vec2 const& possibleDirection)
//            {
//                return possibleDirection == preferredDirection;
//            }))
//        {
//            return preferredDirection;
//        }
//    }
//
//    return config::VEC_INVALID;
//}
