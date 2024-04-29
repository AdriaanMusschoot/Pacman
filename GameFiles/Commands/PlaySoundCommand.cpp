#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "Configuration.h"

using SoundId = pacman::config::SoundId;

void pacman::PlayPacmanChomp::Execute()
{
	using namespace pacman::config;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(static_cast<int>(PACMAN_CHOMP.first), PACMAN_CHOMP.second, 10);
}

void pacman::PlayPacmanDeath::Execute()
{
	using namespace pacman::config;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(static_cast<int>(PACMAN_DEATH.first), PACMAN_DEATH.second, 10);
}
