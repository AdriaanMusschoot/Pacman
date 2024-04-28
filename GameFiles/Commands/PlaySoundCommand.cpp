#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "Configuration.h"

using SoundId = pacman::config::SoundId;

void pacman::PlayPacmanChomp::Execute()
{
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(static_cast<int>(SoundId::PacmanChomp), 10);
}

void pacman::PlayPacmanDeath::Execute()
{
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(static_cast<int>(SoundId::PacmanDeath), 10);
}
