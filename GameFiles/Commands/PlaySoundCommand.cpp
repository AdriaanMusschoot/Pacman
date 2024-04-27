#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "SoundIds.h"

void pacman::PlaySoundCommand::Execute()
{
	using SoundId = pacman::config::SoundId;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->PlaySoundEffect(static_cast<int>(SoundId::PacManDeath), 10);
}