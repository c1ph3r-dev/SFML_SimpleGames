#include <iostream>

#include "Launcher.h"
#include "BlockClicker/BlockClicker.h"
#include "SpaceShooter/SpaceShooter.h"
#include "SwagBalls/SwagBalls.h"

int main()
{
	while (true)
	{
		// Init Game engine
		Launcher launcher;
		EGame game;
		
		launcher.Run(game);

		if (game == EGame::BlockClicker)
		{
			BlockClicker Game;
			Game.Run();
		}
		else if (game == EGame::SwagBalls)
		{
			SwagBalls Game;
			Game.Run();
		}
		else if (game == EGame::SpaceShooter)
		{
			SpaceShooter Game;
			Game.Run();
		}
		else
		{
			break;
		}
	}
	
	// End of application
	return 0;
}
