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

void Player_MoveForward( Player_t* player )
{
   r32 dx = cosf( player->angle ) * PLAYER_MOVE_INCREMENT;
   r32 dy = tanf( player->angle ) * dx;
   player->position.x += dx;
   player->position.y -= dy;
}

void Player_MoveBackward( Player_t* player )
{
   r32 dx = cosf( player->angle ) * PLAYER_MOVE_INCREMENT;
   r32 dy = tanf( player->angle ) * dx;
   player->position.x -= dx;
   player->position.y += dy;
}
