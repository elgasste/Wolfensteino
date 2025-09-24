#if !defined( GAME_H )
#define GAME_H

#include "common.h"
#include "clock.h"
#include "screen.h"
#include "input.h"
#include "map.h"
#include "player.h"

typedef struct Game_t
{
   Clock_t clock;
   Screen_t screen;
   Input_t input;

   Map_t map;
   Player_t player;
}
Game_t;

#if defined( __cplusplus )
extern "C" {
#endif

void Game_Init( Game_t* game, u16* screenBuffer );
void Game_Tic( Game_t* game );

#if defined( __cplusplus )
}
#endif

#endif // GAME_H
