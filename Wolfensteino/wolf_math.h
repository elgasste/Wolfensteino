#if !defined( WOLF_MATH_H )
#define WOLF_MATH_H

#include "common.h"
#include "vector.h"
#include "map_geometry.h"

#define PI           3.14159274f

#define RAD_30       0.523598790f
#define RAD_45       0.785398185f
#define RAD_90       1.57079637f
#define RAD_180      PI
#define RAD_270      4.71238899f
#define RAD_360      6.28318548f

#define RAY_LENGTH   10000.0f;

typedef struct Lineseg_t Lineseg_t;

#if defined( __cplusplus )
extern "C" {
#endif

Bool_t Math_RayIntersectsLineseg( Lineseg_t* lineseg, r32 camPositionX, r32 camPositionY, r32 angle, Vector2r32* intersect );
Bool_t Math_IsPositionOnRightSide( Vector2r32* position, Linedef_t* linedef );

#if defined( __cplusplus )
}
#endif

#endif // WOLF_MATH_H
