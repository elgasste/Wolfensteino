#if !defined( MAP_MATH_H )
#define MAP_MATH_H

#include "common.h"
#include "vector.h"

#define RAY_LENGTH   10000.0f;

typedef struct Lineseg_t Lineseg_t;
typedef struct Linedef_t Linedef_t;

#if defined( __cplusplus )
extern "C" {
#endif

Bool_t MapMath_RayIntersectsLineseg( Lineseg_t* lineseg, r32 camPositionX, r32 camPositionY, r32 angle, Vector2r32_t* intersect );
Bool_t MapMath_IsPositionOnRightSide( Vector2r32_t* position, Linedef_t* linedef );

#if defined( __cplusplus )
}
#endif

#endif // MAP_MATH_H
