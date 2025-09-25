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

void Screen_DrawLine( Screen_t* screen, u32 x1, u32 y1, u32 x2, u32 y2, u16 color )
{
   u32 x, y, prevY, w;
   r32 adjacent, opposite, theta, tanTheta;
   u16* bufferPos;
   Bool_t flipY = False;

   if ( x1 == x2 )
   {
      Screen_DrawVerticalLine( screen, x1, ( y1 < y2 ) ? y1 : y2, abs( (i32)y2 - (i32)y1 ), color );
   }
   else if ( y1 == y2 )
   {
      x = ( x1 < x2 ) ? x1 : x2;
      w = (u32)abs( (i32)x2 - (i32)x1 );
      bufferPos = screen->buffer + ( ( y1 * SCREEN_WIDTH ) + x );

      for (; x < w; x++, bufferPos++ )
      {
         *bufferPos = color;
      }
   }
   else
   {
      // ensure left-to-right drawing
      if ( x2 < x1 ) { x = x2; x2 = x1; x1 = x; y = y2; y2 = y1; y1 = y; }

      adjacent = (r32)x2 - (r32)x1;
      opposite = (r32)y2 - (r32)y1;

      if ( opposite < 0.0f )
      {
         opposite = -opposite;
         flipY = True;
      }

      theta = atanf( opposite / adjacent );
      tanTheta = tanf( theta );
      bufferPos = screen->buffer;
      prevY = y1;

      if ( flipY )
      {
         for ( x = x1; x <= x2; x++ )
         {
            y = y1 - (u32)( ( x - x1 ) * tanTheta );
            bufferPos[( y * SCREEN_WIDTH ) + x] = color;

            while ( ( prevY - y ) > 1 )
            {
               prevY--;
               bufferPos[( prevY * SCREEN_WIDTH ) + ( x - 1 )] = color;
            }

            prevY = y;
         }
      }
      else
      {
         for ( x = x1; x <= x2; x++ )
         {
            y = y1 + (u32)( ( x - x1 ) * tanTheta );
            bufferPos[( y * SCREEN_WIDTH ) + x] = color;

            while ( ( y - prevY ) > 1 )
            {
               prevY++;
               bufferPos[( prevY * SCREEN_WIDTH ) + ( x - 1 )] = color;
            }

            prevY = y;
         }
      }
   }
}
