#if !defined( PLAYER_H )
#define PLAYER_H

#include "common.h"
#include "vector.h"

// RAD_45 / 30
#define PLAYER_TURN_INCREMENT    0.02618f

typedef struct Player_t
{
   Vector2r32 position;
   r32 angle;
}
Player_t;

#if defined( __cplusplus )
extern "C" {
#endif

void Player_TurnLeft( Player_t* player );
void Player_TurnRight( Player_t* player );

#if defined( __cplusplus )
}
#endif

#endif // PLAYER_H
