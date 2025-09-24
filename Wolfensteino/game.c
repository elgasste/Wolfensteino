#include "game.h"
#include "map_math.h"

internal void Game_HandleInput( Game_t* game );
internal void Game_Draw( Game_t* game );
internal void Game_DrawBackdrop( Game_t* game );
internal void Game_DrawMap( Game_t* game );
internal Bool_t Game_CheckRayCollisionRecursive( Game_t* game,
                                                 BspNode_t* node,
                                                 r32 angle,
                                                 Vector2r32* intersectionPoint,
                                                 Linedef_t** intersectingLinedef );

void Game_Init( Game_t* game, u16* screenBuffer )
{
   Clock_Init( &game->clock );
   Screen_Init( &game->screen, screenBuffer );
   Input_Init( &game->input );
   Map_Load( &game->map );

   // sub-sector 1
   game->player.position.x = 30;
   game->player.position.y = 170;
   game->player.angle = RAD_45;
   
   game->rayAngleIncrement = ( RAD_30 * 2 ) / SCREEN_WIDTH;
}

void Game_Tic( Game_t* game )
{
   Input_Read( &game->input );
   Game_HandleInput( game );
   Game_Draw( game );
}

internal void Game_HandleInput( Game_t* game )
{
   if ( game->input.buttonStates[Button_Left].down )
   {
      if ( game->input.buttonStates[Button_B].down )
      {
         Player_StrafeLeft( &game->player );
      }
      else
      {
         Player_TurnLeft( &game->player );
      }
   }
   if ( game->input.buttonStates[Button_Right].down )
   {
      if ( game->input.buttonStates[Button_B].down )
      {
         Player_StrafeRight( &game->player );
      }
      else
      {
         Player_TurnRight( &game->player );
      }
   }

   if ( game->input.buttonStates[Button_Up].down )
   {
      Player_MoveForward( &game->player );
   }
   if ( game->input.buttonStates[Button_Down].down )
   {
      Player_MoveBackward( &game->player );
   }
}

internal void Game_Draw( Game_t* game )
{
   Game_DrawBackdrop( game );
   Game_DrawMap( game );
   Screen_RenderBuffer( &game->screen );
}

internal void Game_DrawBackdrop( Game_t* game )
{
   u32 row, col;
   r32 intensity;
   local_persist r32 intensityIncrement = 1.0f / HALF_SCREEN_HEIGHT;

   for ( row = 0, intensity = 1.0f; row < HALF_SCREEN_HEIGHT; row++, intensity -= intensityIncrement )
   {
      for ( col = 0; col < SCREEN_WIDTH; col++ )
      {
         game->screen.buffer[( row * SCREEN_WIDTH ) + col] =
            ( (u16)( 0xF * intensity ) << 11 ) |
            ( (u16)( 0x1F * intensity ) << 5 ) |
            (u16)( 0xF * intensity );
      }
   }

   for ( row = SCREEN_HEIGHT - 1, intensity = 1.0f; row >= HALF_SCREEN_HEIGHT; row--, intensity -= intensityIncrement )
   {
      for ( col = 0; col < SCREEN_WIDTH; col++ )
      {
         game->screen.buffer[( row * SCREEN_WIDTH ) + col] =
            ( (u16)( 0xF * intensity ) << 11 ) |
            ( (u16)( 0x1F * intensity ) << 5 ) |
            (u16)( 0xF * intensity );
      }
   }
}

internal void Game_DrawMap( Game_t* game )
{
   u32 i, columnIndex, y, length;
   u32 yCache = 0, lengthCache = 0;
   u16 color;
   Vector2r32 intersectionPoint;
   Linedef_t* intersectingLinedef = 0;
   r32 angle = game->player.angle + RAD_30;
   r32 rayLength, projectedWallHeight, halfProjectedWallHeight, top, bottom, lightFactor, lightAdjustment, lightPercentage;
   local_persist r32 wallHeight = 100.0f;
   local_persist r32 projectionPlaneDelta = SCREEN_HEIGHT / 1.5f;
   local_persist r32 lightingScalar = 2.0f;
   local_persist Linedef_t* intersectingLinedefCache = 0;

   for ( i = 0; i < SCREEN_WIDTH; i++, angle -= game->rayAngleIncrement )
   {
      if ( angle >= RAD_360 )
      {
         angle -= RAD_360;
      }
      else if ( angle < 0 )
      {
         angle = RAD_360 + angle;
      }

      Game_CheckRayCollisionRecursive( game, &game->map.bspNodes[0], angle, &intersectionPoint, &intersectingLinedef );

      if ( intersectingLinedef )
      {
         columnIndex = i * 2;

         // the old method. it causes fish-eye.
         //auto rayLength = (float)sqrt( pow( intersectionPoint.x - _playerPosition.x, 2 ) + pow( intersectionPoint.y - _playerPosition.y, 2 ) );

         // from the Wolfenstein 3D book. it's supposed to fix fish-eye, but sometimes it seems to cause reverse-fish-eye
         rayLength = ( ( intersectionPoint.x - game->player.position.x ) * (r32)cosf( game->player.angle ) ) - ( ( intersectionPoint.y - game->player.position.y ) * (r32)sinf( game->player.angle ) );

         // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
         projectedWallHeight = ( ( wallHeight / rayLength ) * projectionPlaneDelta );
         halfProjectedWallHeight = projectedWallHeight / 2.0f;

         lightFactor = rayLength / lightingScalar;
         lightAdjustment = min( lightFactor, 255.0f );
         lightPercentage = 1.0f - ( lightAdjustment / 255.0f );

         // light diminishing
         color = intersectingLinedef->color;
         color = ( (u16)( (r32)( color >> 11 ) * lightPercentage ) << 11 ) |
            ( (u16)( (r32)( ( color >> 5 ) & 0x3F ) * lightPercentage ) << 5 ) |
            ( (u16)( (r32)( color & 0x1F ) * lightPercentage ) );

         top = HALF_SCREEN_HEIGHT - halfProjectedWallHeight;
         bottom = HALF_SCREEN_HEIGHT + halfProjectedWallHeight;

         if ( top < 0.0f )
         {
            top = 0.0f;
         }
         if ( bottom >= SCREEN_HEIGHT )
         {
            bottom = SCREEN_HEIGHT;
         }

         length = (u32)( bottom - top );
         y = (u32)( ( SCREEN_HEIGHT - length ) / 2 );

         if ( intersectingLinedef != intersectingLinedefCache )
         {
            intersectingLinedefCache = intersectingLinedef;
            Screen_DrawVerticalLine( &game->screen, i, y, length, COLOR_BLACK );

            if ( ( i > 0 ) && ( length < lengthCache ) )
            {
               Screen_DrawVerticalLine( &game->screen, i - 1, yCache, lengthCache, COLOR_BLACK );
            }
         }
         else
         {
            Screen_DrawVerticalLine( &game->screen, i, y, length, color );
         }

         lengthCache = length;
         yCache = y;
      }
   }
}

internal Bool_t Game_CheckRayCollisionRecursive( Game_t* game,
                                                 BspNode_t* node,
                                                 r32 angle,
                                                 Vector2r32* intersectionPoint,
                                                 Linedef_t** intersectingLinedef )
{
   u32 i;

   if ( node->isLeaf )
   {
      for ( i = 0; i < node->subsector->linesegCount; i++ )
      {
         if ( MapMath_RayIntersectsLineseg( &node->subsector->linesegs[i], game->player.position.x, game->player.position.y, angle, intersectionPoint ) )
         {
            *intersectingLinedef = node->subsector->linesegs[i].linedef;
            return True;
         }
      }

      return False;
   }
   else
   {
      *intersectingLinedef = node->linedef;

      if ( MapMath_IsPositionOnRightSide( &game->player.position, node->linedef ) )
      {
         return Game_CheckRayCollisionRecursive( game, node->rightChild, angle, intersectionPoint, intersectingLinedef )
            ? True
            : Game_CheckRayCollisionRecursive( game, node->leftChild, angle, intersectionPoint, intersectingLinedef );
      }
      else
      {
         return Game_CheckRayCollisionRecursive( game, node->leftChild, angle, intersectionPoint, intersectingLinedef )
            ? True
            : Game_CheckRayCollisionRecursive( game, node->rightChild, angle, intersectionPoint, intersectingLinedef );
      }
   }
}
