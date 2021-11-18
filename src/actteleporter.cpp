/*-------------------------------------------------------------------------------

	BARONY
	File: actladder.cpp
	Desc: behavior function for ladders

	Copyright 2013-2016 (c) Turning Wheel LLC, all rights reserved.
	See LICENSE for details.

-------------------------------------------------------------------------------*/

#include "main.hpp"
#include "game.hpp"
#include "stat.hpp"
#include "engine/audio/sound.hpp"
#include "entity.hpp"
#include "scores.hpp"
#include "net.hpp"
#include "collision.hpp"
#include "player.hpp"

/*-------------------------------------------------------------------------------

	act*

	The following function describes an entity behavior. The function
	takes a pointer to the entity that uses it as an argument.

-------------------------------------------------------------------------------*/

void actTeleporter(Entity* my)
{
	if ( !my )
	{
		return;
	}

	my->actTeleporter();
}

void Entity::actTeleporter()
{
	int i;

	if ( this->ticks == 1 )
	{
		createWorldUITooltip();
	}

	teleporterAmbience--;
	if ( teleporterAmbience <= 0 )
	{
		teleporterAmbience = TICKS_PER_SECOND * 30;
		playSoundEntityLocal(this, 149, 64);
	}

	// use teleporter
	if ( multiplayer != CLIENT )
	{
		for ( i = 0; i < MAXPLAYERS; i++ )
		{
			if ( selectedEntity[i] == this || client_selected[i] == this )
			{
				if ( inrange[i] )
				{
					switch ( teleporterType )
					{
						case 0:
							messagePlayer(i, language[2378]);
							break;
						case 1:
							messagePlayer(i, language[506]);
							break;
						case 2:
							messagePlayer(i, language[510]);
							break;
						default:
							break;
					}
					players[i]->entity->teleporterMove(teleporterX, teleporterY, teleporterType);
					return;
				}
			}
		}
	}

	if ( teleporterType == 2 )
	{
		if ( !light )
		{
			light = lightSphereShadow(x / 16, y / 16, 3, 255);
		}
		yaw += 0.01; // rotate slowly on my axis
		sprite = 620;
		if ( ((this->ticks / 20 ) % 4) > 0 )
		{
			sprite = 992 + ((this->ticks / 20) % 4) - 1; // animate through 992, 993, 994
		}
	}
}