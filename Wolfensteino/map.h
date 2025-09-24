#if !defined( MAP_H )
#define MAP_H

#include "common.h"
#include "vector.h"

#define MAP_MEMORY_SIZE_BYTES       131072   // 128k

#define MAP_WALL_HEIGHT             100.0f
#define MAP_PROJECTED_PLANE_DELTA   ( SCREEN_HEIGHT / 1.5f )
#define MAP_LIGHTING_SCALAR         2.0f
#define MAP_RAY_ANGLE_INCREMENT     ( RAD_30 * 2 ) / SCREEN_WIDTH

typedef struct BspNode_t BspNode_t;

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
   Linedef_t* linedefs;
   u32 linedefCount;
}
Sector_t;

typedef struct Subsector_t
{
   Lineseg_t* linesegs;
   u32 linesegCount;
}
Subsector_t;

typedef struct BspNode_t
{
   Bool_t isLeaf;
   
   BspNode_t* parent;
   BspNode_t* leftChild;
   BspNode_t* rightChild;

   Linedef_t* linedef;
   Subsector_t* subsector;
}
BspNode_t;

typedef struct Map_t
{
   u8 memory[MAP_MEMORY_SIZE_BYTES];

   Sector_t* sectors;
   u32 sectorCount;
   Subsector_t* subsectors;
   u32 subsectorCount;
   BspNode_t* bspNodes;
   u32 bspNodeCount;
}
Map_t;

#if defined( __cplusplus )
extern "C" {
#endif

// map_data.c
void Map_Load( Map_t* map );

#if defined( __cplusplus )
}
#endif

#endif // MAP_H
