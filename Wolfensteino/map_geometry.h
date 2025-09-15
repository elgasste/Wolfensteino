#if !defined( MAP_GEOMETRY_H )
#define MAP_GEOMETRY_H

#include "common.h"
#include "vector.h"

#define SECTOR_MAX_LINEDEFS      32
#define SUBSECTOR_MAX_LINESEGS   32

typedef struct Linedef_t
{
   Vector2r32 start;
   Vector2r32 end;
   u16 color;
}
Linedef_t;

typedef struct Lineseg_t
{
   Linedef_t* linedef;
   Vector2r32 start;
   Vector2r32 end;
}
Lineseg_t;

typedef struct Sector_t
{
   Linedef_t linedefs[SECTOR_MAX_LINEDEFS];
   u32 linedefCount;
}
Sector_t;

typedef struct Subsector_t
{
   Lineseg_t linesegs[SUBSECTOR_MAX_LINESEGS];
   u32 linesegCount;
}
Subsector_t;

#endif // MAP_GEOMETRY_H
