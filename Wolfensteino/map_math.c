#include "map_math.h"
#include "map.h"

#define CROSS_PRODUCT( px, py, ox, oy, dx, dy ) ( ( dx * ( py - oy ) ) - ( dy * ( px - ox ) ) )

internal Bool_t MapMath_LineIntersectsLineseg( Lineseg_t* lineseg, r32 p1x, r32 p1y, r32 p2x, r32 p2y, Vector2r32* intersect );

Bool_t MapMath_RayIntersectsLineseg( Lineseg_t* lineseg, r32 camPositionX, r32 camPositionY, r32 angle, Vector2r32* intersect )
{
   r32 dx = cosf( angle ) * RAY_LENGTH;
   r32 dy = tanf( angle ) * dx;

   return MapMath_LineIntersectsLineseg( lineseg, camPositionX, camPositionY, camPositionX + dx, camPositionY - dy, intersect );
}

internal Bool_t MapMath_LineIntersectsLineseg( Lineseg_t* lineseg, r32 p1x, r32 p1y, r32 p2x, r32 p2y, Vector2r32* intersect )
{
   r32 pdx = p2x - p1x;
   r32 pdy = p2y - p1y;
   r32 ldx = lineseg->end.x - lineseg->start.x;
   r32 ldy = lineseg->end.y - lineseg->start.y;
   r32 cp = -ldx * pdy + pdx * ldy;

   if ( cp == 0.0f )
   {
      // lines are parallel or collinear
      return False;
   }

   r32 s = ( -pdy * ( p1x - lineseg->start.x ) + pdx * ( p1y - lineseg->start.y ) ) / cp;
   r32 t = ( ldx * ( p1y - lineseg->start.y ) - ldy * ( p1x - lineseg->start.x ) ) / cp;

   if ( s >= 0 && s <= 1 && t >= 0 && t <= 1 )
   {
      // collision detected
      intersect->x = p1x + ( t * pdx );
      intersect->y = p1y + ( t * pdy );
      return True;
   }

   return False;
}

Bool_t MapMath_IsPositionOnRightSide( Vector2r32* position, Linedef_t* linedef )
{
   r32 dx = linedef->end.x - linedef->start.x;
   r32 dy = linedef->end.y - linedef->start.y;

   // shortcut if linedef is vertical
   if ( dx == 0 )
   {
      return ( dy > 0 ) ? position->x <= linedef->start.x : position->x > linedef->start.x;
   }

   // shortcut if linedef is horizontal
   if ( dy == 0 )
   {
      return ( dx > 0 ) ? position->y > linedef->start.y : position->y <= linedef->start.y;
   }

   return CROSS_PRODUCT( position->x, position->y, linedef->start.x, linedef->start.y, dx, dy ) > 0.0f;
}
