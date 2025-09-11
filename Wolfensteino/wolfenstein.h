#if !defined( WOLFENSTEIN_H )
#define WOLFENSTEIN_H

#include "common.h"
#include "clock.h"
#include "screen.h"
#include "input.h"

typedef struct Wolfenstein_t
{
   Clock_t clock;
   Screen_t screen;
   Input_t input;
}
Wolfenstein_t;

#if defined( __cplusplus )
extern "C" {
#endif

void Wolfenstein_Init( Wolfenstein_t* wolf, u16* screenBuffer );
void Wolfenstein_Tic( Wolfenstein_t* wolf );

#if defined( __cplusplus )
}
#endif

#endif // WOLFENSTEIN_H
