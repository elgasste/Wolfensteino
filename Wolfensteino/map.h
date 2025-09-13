#if !defined( MAP_H )
#define MAP_H

#include "common.h"
#include "map_geometry.h"

#define MAP_MAX_LINEDEFS         1024
#define MAP_MAX_SECTORS          32
#define MAP_MAX_SUBSECTORS       128
#define BSP_MAX_NODES            1024

typedef struct BspNode_t BspNode_t;

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

#if defined( __cplusplus )
extern "C" {
#endif

// wolfenstein_data.c
void Map_Load( Map_t* map );

#if defined( __cplusplus )
}
#endif

#endif // MAP_H
