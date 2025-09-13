#include "player.h"
#include "wolf_math.h"

void Player_TurnLeft( Player_t* player )
{
   player->angle += PLAYER_TURN_INCREMENT;

   if ( player->angle >= RAD_360 )
   {
      player->angle -= RAD_360;
   }
}

void Player_TurnRight( Player_t* player )
{
   player->angle -= PLAYER_TURN_INCREMENT;

   if ( player->angle < 0.0f )
   {
      player->angle = RAD_360 + player->angle;
   }
}
