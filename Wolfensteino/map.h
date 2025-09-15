#if !defined( MAP_H )
#define MAP_H

#include "common.h"
#include "map_geometry.h"

#define MAP_MEMORY_SIZE_BYTES    131072   // 128k

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

// wolfenstein_data.c
void Map_Load( Map_t* map );

#if defined( __cplusplus )
}
#endif

#endif // MAP_H
