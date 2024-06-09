#ifndef PM_SCORE_COMPONENT_H
#define PM_SCORE_COMPONENT_H

#include "Component.h"
#include "Configuration.h"
#include "TextComponent.h"
#include "IObserver.h"
#include "Subject.h"
#include "GameObject.h"

namespace pacman
{

	class ScoreComponent final : public amu::Component, public amu::IObserver, public amu::Subject
	{
	public:
		ScoreComponent(amu::GameObject* ownerObjectPtr);
		virtual ~ScoreComponent() override = default;

		ScoreComponent(ScoreComponent const&) = delete;
		ScoreComponent(ScoreComponent&&) = delete;
		ScoreComponent& operator=(ScoreComponent const&) = delete;
		ScoreComponent& operator=(ScoreComponent&&) = delete;

		void OnNotify(Event eventType, amu::Subject* subjectPtr) override;
	private:
		amu::TextComponent* m_ScoreTextPtr{ nullptr };
		int m_Score{ 0 };
		int m_NumberOfPickups{ };
		int m_PickupsPerLevel{ 244 };

		int const m_SmallPickupScore{ 10 };
		int const m_BigPickupScore{ 50 };
		
		int const m_GhostScoreBaseValue{ 200 };
		int m_CurrentGhostScoreValue{ m_GhostScoreBaseValue };
		int m_GhostsEaten{ };
	};

}

#endif //PM_SCORE_COMPONENT_H