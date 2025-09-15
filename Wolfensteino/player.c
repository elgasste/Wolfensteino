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

void Player_StrafeLeft( Player_t* player )
{
   r32 dx, dy;
   r32 strafeAngle = player->angle + RAD_90;

   if ( strafeAngle >= RAD_360 )
   {
      strafeAngle -= RAD_360;
   }

   dx = cosf( strafeAngle ) * PLAYER_MOVE_INCREMENT;
   dy = tanf( strafeAngle ) * dx;
   player->position.x += dx;
   player->position.y -= dy;
}

void Player_TurnRight( Player_t* player )
{
   player->angle -= PLAYER_TURN_INCREMENT;

   if ( player->angle < 0.0f )
   {
      player->angle = RAD_360 + player->angle;
   }
}

void Player_StrafeRight( Player_t* player )
{
   r32 dx, dy;
   r32 strafeAngle = player->angle - RAD_90;

   if ( strafeAngle < 0 )
   {
      strafeAngle = RAD_360 + strafeAngle;
   }

   dx = cosf( strafeAngle ) * PLAYER_MOVE_INCREMENT;
   dy = tanf( strafeAngle ) * dx;
   player->position.x += dx;
   player->position.y -= dy;
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
