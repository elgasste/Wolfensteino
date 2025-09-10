#include "giga_shield.h"
#include "wolfenstein.h"

Wolfenstein_t g_wolf;
GigaShield g_gigaShield;

void Program_Log( const char* msg )
{
#if defined( DEBUG_SERIAL )
   Serial.println( msg );
#endif
}

void setup()
{
#if defined( DEBUG_SERIAL )
   Serial.begin( SERIAL_BAUD );
#endif

   g_gigaShield.begin();
   Wolfenstein_Init( &g_wolf, g_gigaShield.getBuffer() );
}

void loop()
{
   Clock_StartFrame( &g_wolf.clock );
   Wolfenstein_Tic( &g_wolf );
   Clock_EndFrame( &g_wolf.clock );
}

void Screen_RenderBuffer( Screen_t* screen )
{
   g_gigaShield.drawScreen();
}
