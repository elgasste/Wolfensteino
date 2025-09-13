#include "wolfenstein.h"
#include "wolf_math.h"

internal void Wolfenstein_HandleInput( Wolfenstein_t* wolf );
internal void Wolfenstein_Draw( Wolfenstein_t* wolf );
internal void Wolfenstein_DrawMap( Wolfenstein_t* wolf );
internal Bool_t Wolfenstein_CheckRayCollisionRecursive( Wolfenstein_t* wolf,
                                                        BspNode_t* node,
                                                        r32 angle,
                                                        Vector2r32* intersectionPoint,
                                                        Linedef_t** intersectingLinedef );

void Wolfenstein_Init( Wolfenstein_t* wolf, u16* screenBuffer )
{
   Clock_Init( &wolf->clock );
   Screen_Init( &wolf->screen, screenBuffer );
   Input_Init( &wolf->input );
   Map_Load( &wolf->map );

   // sub-sector 1
   wolf->player.position.x = 30;
   wolf->player.position.y = 170;
   wolf->player.angle = RAD_45;
   
   wolf->rayAngleIncrement = ( RAD_30 * 2 ) / SCREEN_WIDTH;
}

void Wolfenstein_Tic( Wolfenstein_t* wolf )
{
   Input_Read( &wolf->input );
   Wolfenstein_HandleInput( wolf );
   Wolfenstein_Draw( wolf );
}

internal void Wolfenstein_HandleInput( Wolfenstein_t* wolf )
{
   if ( wolf->input.buttonStates[Button_Left].down )
   {
      Player_TurnLeft( &wolf->player );
   }
   if ( wolf->input.buttonStates[Button_Right].down )
   {
      Player_TurnRight( &wolf->player );
   }
}

internal void Wolfenstein_Draw( Wolfenstein_t* wolf )
{
   Screen_WipeColor( &wolf->screen, COLOR_BLACK );
   Wolfenstein_DrawMap( wolf );
   Screen_RenderBuffer( &wolf->screen );
}

internal void Wolfenstein_DrawMap( Wolfenstein_t* wolf )
{
   u32 i, columnIndex, y, length;
   Vector2r32 intersectionPoint;
   Linedef_t* intersectingLinedef = 0;
   r32 angle = wolf->player.angle + RAD_30;
   r32 rayLength, projectedWallHeight, halfProjectedWallHeight, top, bottom;
   local_persist r32 wallHeight = 100.0f;
   local_persist r32 projectionPlaneDelta = SCREEN_HEIGHT / 1.5f;
   local_persist r32 halfScreenHeight = SCREEN_HEIGHT / 2.0f;
   local_persist r32 lightingScalar = 2.0f;

   for ( i = 0; i < SCREEN_WIDTH; i++, angle -= wolf->rayAngleIncrement )
   {
      if ( angle >= RAD_360 )
      {
         angle -= RAD_360;
      }
      else if ( angle < 0 )
      {
         angle = RAD_360 + angle;
      }

      Wolfenstein_CheckRayCollisionRecursive( wolf, &wolf->map.bspTree.nodes[0], angle, &intersectionPoint, &intersectingLinedef );

      if ( intersectingLinedef )
      {

         columnIndex = i * 2;

         // the old method. it causes fish-eye.
         //auto rayLength = (float)sqrt( pow( intersectionPoint.x - _playerPosition.x, 2 ) + pow( intersectionPoint.y - _playerPosition.y, 2 ) );

         // from the Wolfenstein 3D book. it's supposed to fix fish-eye, but sometimes it seems to cause reverse-fish-eye
         rayLength = ( ( intersectionPoint.x - wolf->player.position.x ) * (r32)cos( wolf->player.angle ) ) - ( ( intersectionPoint.y - wolf->player.position.y ) * (r32)sin( wolf->player.angle ) );

         // this uses the formula ProjectedWallHeight = ( ActualWallHeight / DistanceToWall ) * DistanceToProjectionPlane
         projectedWallHeight = ( ( wallHeight / rayLength ) * projectionPlaneDelta );
         halfProjectedWallHeight = projectedWallHeight / 2.0f;

         // MUFFINS: re-visit light depth adjustment after testing performance on the Arduino
         /*color = intersectingLinedef->color;
         lightAdjustment = ( rayLength == 0.0f ) ? 0.0f : min( rayLength / lightingScalar, 255.0f );
         color.r = (Uint8)max( 0, (int)( color.r - lightAdjustment ) );
         color.g = (Uint8)max( 0, (int)( color.g - lightAdjustment ) );
         color.b = (Uint8)max( 0, (int)( color.b - lightAdjustment ) );*/

         top = halfScreenHeight - halfProjectedWallHeight;
         bottom = halfScreenHeight + halfProjectedWallHeight;

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

         Screen_DrawVerticalLine( &wolf->screen, i, y, length, intersectingLinedef->color );
      }
   }
}

internal Bool_t Wolfenstein_CheckRayCollisionRecursive( Wolfenstein_t* wolf,
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
         if ( Math_RayIntersectsLineseg( &node->subsector->linesegs[i], wolf->player.position.x, wolf->player.position.y, angle, intersectionPoint ) )
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

      if ( Math_IsPositionOnRightSide( &wolf->player.position, node->linedef ) )
      {
         return Wolfenstein_CheckRayCollisionRecursive( wolf, node->rightChild, angle, intersectionPoint, intersectingLinedef )
            ? True
            : Wolfenstein_CheckRayCollisionRecursive( wolf, node->leftChild, angle, intersectionPoint, intersectingLinedef );
      }
      else
      {
         return Wolfenstein_CheckRayCollisionRecursive( wolf, node->leftChild, angle, intersectionPoint, intersectingLinedef )
            ? True
            : Wolfenstein_CheckRayCollisionRecursive( wolf, node->rightChild, angle, intersectionPoint, intersectingLinedef );
      }
   }
}
