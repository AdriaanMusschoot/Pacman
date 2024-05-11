#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "Configuration.h"

void amu::PlayPacmanChomp::Execute()
{
	using namespace pacman::sound;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(PACMAN_CHOMP.first, PACMAN_CHOMP.second, 10);
}

void amu::PlayPacmanDeath::Execute()
{
	using namespace pacman::sound;
	amu::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(PACMAN_DEATH.first, PACMAN_DEATH.second, 10);
}