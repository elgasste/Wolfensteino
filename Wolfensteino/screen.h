#if !defined( SCREEN_H )
#define SCREEN_H

#include "common.h"

#define SCREEN_WIDTH                   420
#define SCREEN_HEIGHT                  240
#define HALF_SCREEN_HEIGHT             120
#define SCREEN_PIXELS                  100800

#define COLOR_BLACK                    0x0000
#define COLOR_WHITE                    0xFFFF
#define COLOR_RED                      0xF800
#define COLOR_GREEN                    0x07E0
#define COLOR_BLUE                     0x001F
#define COLOR_MAGENTA                  0xF81F
#define COLOR_YELLOW                   0xFFE0
#define COLOR_CYAN                     0x07FF

typedef struct Screen_t
{
   u16* buffer;
}
Screen_t;

#if defined( __cplusplus )
extern "C" {
#endif

   void Screen_Init( Screen_t* screen, u16* buffer );
   void Screen_WipeColor( Screen_t* screen, u16 color );
   void Screen_DrawVerticalLine( Screen_t* screen, u32 x, u32 y, u32 length, u16 color );
   void Screen_DrawVerticalLineWithBorder( Screen_t* screen, u32 x, u32 y, u32 length, u16 lineColor, u16 borderColor );
   void Screen_DrawLine( Screen_t* screen, u32 x1, u32 y1, u32 x2, u32 y2, u16 color );
   void Screen_DrawCircle( Screen_t* screen, u32 centerX, u32 centerY, u32 radius, u16 color );

   // platform-specific
   void Screen_RenderBuffer( Screen_t* screen );

#if defined( __cplusplus )
}
#endif

#endif // SCREEN_H
