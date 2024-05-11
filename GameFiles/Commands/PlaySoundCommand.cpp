#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "Configuration.h"

void pacman::PlayPacmanChomp::Execute()
{
	using namespace pacman::sound;
	pacman::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(PACMAN_CHOMP.first, PACMAN_CHOMP.second, 10);
}

void pacman::PlayPacmanDeath::Execute()
{
	using namespace pacman::sound;
	pacman::ServiceLocator::GetInstance().GetSoundSystem()->RequestSoundEffect(PACMAN_DEATH.first, PACMAN_DEATH.second, 10);
}