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
      *bufferPos = color;
      bufferPos += SCREEN_WIDTH;
   }
}

void Screen_DrawVerticalLineWithBorder( Screen_t* screen, u32 x, u32 y, u32 length, u16 lineColor, u16 borderColor )
{
   u16* bufferPos = screen->buffer + ( ( y * SCREEN_WIDTH ) + x );

   *bufferPos = borderColor;
   Screen_DrawVerticalLine( screen, x, y + 1, length - 2, lineColor );
   bufferPos += ( SCREEN_WIDTH * ( length - 1 ) );
   *bufferPos = borderColor;
}
