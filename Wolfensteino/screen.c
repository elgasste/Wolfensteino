#include "screen.h"

void Screen_Init( Screen_t* screen, u16* buffer )
{
   screen->buffer = buffer;
}

void Screen_WipeColor( Screen_t* screen, u16 color )
{
   u32 i;
   u16* bufferPos = screen->buffer;

   for ( i = 0; i < SCREEN_PIXELS; i++ )
   {
      *bufferPos = color;
      bufferPos++;
   }
}

void Screen_DrawVerticalLine( Screen_t* screen, u32 x, u32 y, u32 length, u16 color )
{
   u32 i;
   u16* bufferPos = screen->buffer + ( ( y * SCREEN_WIDTH ) + x );

   for ( i = 0; i < length; i++ )
   {
      *bufferPos = ( i == 0 || i == ( length - 1 ) ) ? COLOR_BLACK : color;
      bufferPos += SCREEN_WIDTH;
   }
}
