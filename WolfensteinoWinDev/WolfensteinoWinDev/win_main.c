#include "win_common.h"
#include "screen.h"

internal LRESULT CALLBACK MainWindowProc( _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam );
internal void RenderScreen();
internal void FatalError( const char* message );

int CALLBACK WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
   TIMECAPS timeCaps;
   UINT timerResolution;
   WNDCLASSA mainWindowClass = { 0 };
   DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
   RECT expectedWindowRect = { 0 };
   LONG clientPaddingRight, clientPaddingTop;
   MSG msg;
   Wolfenstein_t* wolf = &g_winGlobals.wolf;

   UNUSED_PARAM( hPrevInstance );
   UNUSED_PARAM( lpCmdLine );
   UNUSED_PARAM( nCmdShow );

   if ( !QueryPerformanceFrequency( &( g_winGlobals.performanceFrequency ) ) )
   {
      FatalError( "failed to query performance frequency." );
   }

   if ( timeGetDevCaps( &timeCaps, sizeof( TIMECAPS ) ) != TIMERR_NOERROR )
   {
      FatalError( "failed to set timer resolution." );
   }

   timerResolution = min( max( timeCaps.wPeriodMin, 1 ), timeCaps.wPeriodMax );
   timeBeginPeriod( timerResolution );

   mainWindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
   mainWindowClass.lpfnWndProc = MainWindowProc;
   mainWindowClass.hInstance = hInstance;
   mainWindowClass.lpszClassName = "mainWindowClass";

   if ( !RegisterClassA( &mainWindowClass ) )
   {
      FatalError( "failed to register window class." );
   }

   expectedWindowRect.right = SCREEN_WIDTH;
   expectedWindowRect.bottom = SCREEN_HEIGHT;

   if ( !AdjustWindowRect( &expectedWindowRect, windowStyle, 0 ) )
   {
      FatalError( "failed to adjust window rect." );
   }

   clientPaddingRight = ( expectedWindowRect.right - expectedWindowRect.left ) - SCREEN_WIDTH;
   clientPaddingTop = ( expectedWindowRect.bottom - expectedWindowRect.top ) - SCREEN_HEIGHT;

   g_winGlobals.hWndMain = CreateWindowExA( 0,
                                            mainWindowClass.lpszClassName,
                                            "Wolfensteino Windows Development Tool",
                                            windowStyle,
                                            CW_USEDEFAULT,
                                            CW_USEDEFAULT,
                                            (int)( SCREEN_WIDTH * GRAPHICS_SCALE ) + clientPaddingRight,
                                            (int)( SCREEN_HEIGHT * GRAPHICS_SCALE ) + clientPaddingTop,
                                            0,
                                            0,
                                            hInstance,
                                            0 );

   if ( !g_winGlobals.hWndMain )
   {
      FatalError( "failed to create main window." );
   }

   SetCursor( LoadCursor( 0, IDC_ARROW ) );

   g_winGlobals.hFont = CreateFontA( 16, 0, 0, 0,
                                     FW_BOLD, FALSE, FALSE, FALSE,
                                     ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                     DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
                                     "Consolas" );

   WinPixelBuffer_Init( &( g_winGlobals.screenBuffer ), SCREEN_WIDTH, SCREEN_HEIGHT );
   g_winGlobals.bmpInfo.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
   g_winGlobals.bmpInfo.bmiHeader.biWidth = g_winGlobals.screenBuffer.w;
   g_winGlobals.bmpInfo.bmiHeader.biHeight = -(LONG)( g_winGlobals.screenBuffer.h );
   g_winGlobals.bmpInfo.bmiHeader.biPlanes = 1;
   g_winGlobals.bmpInfo.bmiHeader.biBitCount = 32;
   g_winGlobals.bmpInfo.bmiHeader.biCompression = BI_RGB;

   Wolfenstein_Init( wolf, g_winGlobals.screenBuffer.memory16 );
   g_winGlobals.shutdown = False;

   while ( 1 )
   {
      Clock_StartFrame( &wolf->clock );

      while ( PeekMessageA( &msg, g_winGlobals.hWndMain, 0, 0, PM_REMOVE ) )
      {
         TranslateMessage( &msg );
         DispatchMessageA( &msg );
      }

      Wolfenstein_Tic( wolf );

      InvalidateRect( g_winGlobals.hWndMain, 0, FALSE );
      Clock_EndFrame( &wolf->clock );

      if ( g_winGlobals.shutdown )
      {
         break;
      }
   }

   WinPixelBuffer_CleanUp( &( g_winGlobals.screenBuffer ) );
   return 0;
}

internal LRESULT CALLBACK MainWindowProc( _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam )
{
   LRESULT result = 0;

   switch ( uMsg )
   {
      case WM_QUIT:
      case WM_CLOSE:
      case WM_DESTROY:
         g_winGlobals.shutdown = True;
         break;
      case WM_PAINT:
         RenderScreen();
         break;
      default:
         result = DefWindowProcA( hWnd, uMsg, wParam, lParam );
   }

   return result;
}

// the double-buffering part of this came from Stack Overflow
internal void RenderScreen()
{
   HDC dc, dcMem;
   HBITMAP bmMem;
   HANDLE hOld;
   PAINTSTRUCT ps;
   int winWidth = (int)( SCREEN_WIDTH * GRAPHICS_SCALE );
   int winHeight = (int)( SCREEN_HEIGHT * GRAPHICS_SCALE );

   dc = BeginPaint( g_winGlobals.hWndMain, &ps );

   // create an off-screen DC for double-buffering
   dcMem = CreateCompatibleDC( dc );
   bmMem = CreateCompatibleBitmap( dc, winWidth, winHeight );
   hOld = SelectObject( dcMem, bmMem );

   // actually draw everything
   StretchDIBits(
      dcMem,
      0, 0, (int)( SCREEN_WIDTH * GRAPHICS_SCALE ), (int)( SCREEN_HEIGHT * GRAPHICS_SCALE ), // dest
      0, 0, g_winGlobals.screenBuffer.w, g_winGlobals.screenBuffer.h, // src
      g_winGlobals.screenBuffer.memory32,
      &( g_winGlobals.bmpInfo ),
      DIB_RGB_COLORS, SRCCOPY
   );

   // transfer the off-screen DC to the screen
   BitBlt( dc, 0, 0, winWidth, winHeight, dcMem, 0, 0, SRCCOPY );

   SelectObject( dcMem, hOld );
   DeleteObject( bmMem );
   DeleteDC( dcMem );
   EndPaint( g_winGlobals.hWndMain, &ps );
}

internal void FatalError( const char* message )
{
   char errorMsg[STRING_SIZE_DEFAULT];
   snprintf( errorMsg, STRING_SIZE_DEFAULT, "Windows error: %s", message );
   MessageBoxA( 0, message, "Error", MB_OK | MB_ICONERROR );
   exit( 1 );
}
