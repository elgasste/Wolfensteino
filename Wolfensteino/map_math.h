#if !defined( MAP_MATH_H )
#define MAP_MATH_H

#include "common.h"
#include "vector.h"

#define PI           3.14159274f

#define RAD_30       0.523598790f
#define RAD_45       0.785398185f
#define RAD_90       1.57079637f
#define RAD_180      PI
#define RAD_270      4.71238899f
#define RAD_360      6.28318548f

#define RAY_LENGTH   10000.0f;

typedef struct Lineseg_t Lineseg_t;
typedef struct Linedef_t Linedef_t;

#if defined( __cplusplus )
extern "C" {
#endif

Bool_t MapMath_RayIntersectsLineseg( Lineseg_t* lineseg, r32 camPositionX, r32 camPositionY, r32 angle, Vector2r32* intersect );
Bool_t MapMath_IsPositionOnRightSide( Vector2r32* position, Linedef_t* linedef );

#if defined( __cplusplus )
}
#endif

#endif // MAP_MATH_H
