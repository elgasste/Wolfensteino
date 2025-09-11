#if !defined( MAP_H )
#define MAP_H

#include "common.h"
#include "vector.h"

#define SECTOR_MAX_LINEDEFS      32
#define SUBSECTOR_MAX_LINESEGS   32
#define MAP_MAX_LINEDEFS         1024
#define MAP_MAX_SECTORS          32
#define MAP_MAX_SUBSECTORS       128
#define BSP_MAX_NODES            1024

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
   Linedef_t linedefs[SECTOR_MAX_LINEDEFS];
   u32 linedefCount;
}
Sector_t;

typedef struct Subsector_t
{
   Lineseg_t* linesegs[SUBSECTOR_MAX_LINESEGS];
   u32 linedefCount;
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

typedef struct BspTree_t
{
   BspNode_t nodes[BSP_MAX_NODES];
   u32 nodeCount;
}
BspTree_t;

typedef struct Map_t
{
   Sector_t sectors[MAP_MAX_SECTORS];
   u32 sectorCount;
   Subsector_t subsectors[MAP_MAX_SUBSECTORS];
   u32 subsectorCount;

   BspTree_t bspTree;
}
Map_t;

#endif // MAP_H
