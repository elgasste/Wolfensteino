#if !defined( VECTOR_H )
#define VECTOR_H

#include "common.h"

typedef struct Vector2r32_t
{
   r32 x;
   r32 y;
}
Vector2r32_t;

typedef struct Vector4u32_t
{
   u32 x;
   u32 y;
   u32 w;
   u32 h;
}
Vector4u32_t;

typedef struct Vector4r32_t
{
   r32 x;
   r32 y;
   r32 w;
   r32 h;
}
Vector4r32_t;

#endif // VECTOR_H
