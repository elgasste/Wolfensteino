#if !defined( SCREEN_H )
#define SCREEN_H

#include "common.h"

#define SCREEN_WIDTH                   480
#define SCREEN_HEIGHT                  360
#define SCREEN_PIXELS                  172800

#define COLOR_BLACK                    0x0000
#define COLOR_WHITE                    0xFFFF
#define COLOR_RED                      0xF800
#define COLOR_GREEN                    0x07E0
#define COLOR_BLUE                     0x001F

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

   // platform-specific
   void Screen_RenderBuffer( Screen_t* screen );

#if defined( __cplusplus )
}
#endif

#endif // SCREEN_H
