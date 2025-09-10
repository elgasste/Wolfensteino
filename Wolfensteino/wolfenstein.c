#include "wolfenstein.h"

internal void Wolfenstein_Draw( Wolfenstein_t* wolf );

void Wolfenstein_Init( Wolfenstein_t* wolf, u16* screenBuffer )
{
   Clock_Init( &wolf->clock );
   Screen_Init( &wolf->screen, screenBuffer );
}

void Wolfenstein_Tic( Wolfenstein_t* wolf )
{
   Wolfenstein_Draw( wolf );
}

internal void Wolfenstein_Draw( Wolfenstein_t* wolf )
{
   // MUFFINS: for testing purposes
   Screen_WipeColor( &wolf->screen, COLOR_BLUE );

   Screen_RenderBuffer( &wolf->screen );
}
