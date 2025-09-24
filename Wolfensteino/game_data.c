#include "game.h"

internal void Map_LoadLinedef( Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY, u16 color );
internal void Map_LoadLineseg( Lineseg_t* lineseg, Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY );
internal void Map_LoadBspNode( BspNode_t* node, Bool_t isLeaf, Linedef_t* linedef, Subsector_t* subsector, BspNode_t* parent, BspNode_t* leftChild, BspNode_t* rightChild );

void Map_Load( Map_t* map )
{
   Sector_t* sector;
   Linedef_t* linedef;
   Subsector_t* subsector;
   Lineseg_t* lineseg;

   map->sectors = (Sector_t*)map->memory;
   map->sectorCount = 6;
   sector = map->sectors;
   linedef = (Linedef_t*)( map->memory + ( sizeof( Sector_t ) * map->sectorCount ) );

   /*************************** SECTORS ***************************/

   // outer sector (blue)
   sector->linedefCount = 15;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 40, 0, 300, 0, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 300, 0, 300, 140.0f + ( 20.0f / 3.0f ), COLOR_BLUE );
   Map_LoadLinedef( linedef++, 300, 140.0f + ( 20.0f / 3.0f ), 260, 130.0f + ( 10.0f / 3.0f ), COLOR_BLUE );
   Map_LoadLinedef( linedef++, 260, 130.0f + ( 10.0f / 3.0f ), 260, 180, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 260, 180, 300, 200, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 300, 200, 300, 250, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 300, 250, 260, 290, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 260, 290, 90, 290, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 90, 290, 90, 230, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 90, 230, 70, 210, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 70, 210, 60, 210, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 60, 210, 60, 290, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 60, 290, 0, 290, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 0, 290, 0, 40, COLOR_BLUE );
   Map_LoadLinedef( linedef++, 0, 40, 40, 0, COLOR_BLUE );
   sector++;

   // inner sector 1 (red)
   sector->linedefCount = 12;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 110, 60, 100, 60, COLOR_RED );
   Map_LoadLinedef( linedef++, 100, 60, 100, 80, COLOR_RED );
   Map_LoadLinedef( linedef++, 100, 80, 50, 80, COLOR_RED );
   Map_LoadLinedef( linedef++, 50, 80, 20, 110, COLOR_RED );
   Map_LoadLinedef( linedef++, 20, 110, 30, 120, COLOR_RED );
   Map_LoadLinedef( linedef++, 30, 120, 60, 90, COLOR_RED );
   Map_LoadLinedef( linedef++, 60, 90, 85, 90, COLOR_RED );
   Map_LoadLinedef( linedef++, 85, 90, 85, 130, COLOR_RED );
   Map_LoadLinedef( linedef++, 85, 130, 95, 130, COLOR_RED );
   Map_LoadLinedef( linedef++, 95, 130, 95, 90, COLOR_RED );
   Map_LoadLinedef( linedef++, 95, 90, 110, 90, COLOR_RED );
   Map_LoadLinedef( linedef++, 110, 90, 110, 60, COLOR_RED );
   sector++;

   // inner sector 2 (green)
   sector->linedefCount = 4;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 230, 60, 170, 60, COLOR_GREEN );
   Map_LoadLinedef( linedef++, 170, 60, 170, 70, COLOR_GREEN );
   Map_LoadLinedef( linedef++, 170, 70, 230, 70, COLOR_GREEN );
   Map_LoadLinedef( linedef++, 230, 70, 230, 60, COLOR_GREEN );
   sector++;

   // inner sector 3 (magenta)
   sector->linedefCount = 4;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 260, 20, 250, 30, COLOR_MAGENTA );
   Map_LoadLinedef( linedef++, 250, 30, 260, 40, COLOR_MAGENTA );
   Map_LoadLinedef( linedef++, 260, 40, 270, 30, COLOR_MAGENTA );
   Map_LoadLinedef( linedef++, 270, 30, 260, 20, COLOR_MAGENTA );
   sector++;

   // inner sector 4 (yellow)
   sector->linedefCount = 5;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 220, 120, 190, 130, COLOR_YELLOW );
   Map_LoadLinedef( linedef++, 190, 130, 190, 140, COLOR_YELLOW );
   Map_LoadLinedef( linedef++, 190, 140, 250, 160, COLOR_YELLOW );
   Map_LoadLinedef( linedef++, 250, 160, 250, 130, COLOR_YELLOW );
   Map_LoadLinedef( linedef++, 250, 130, 220, 120, COLOR_YELLOW );
   sector++;

   // inner sector 5 (cyan)
   sector->linedefCount = 8;
   sector->linedefs = linedef;
   Map_LoadLinedef( linedef++, 175, 185, 165, 185, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 165, 185, 155, 195, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 155, 195, 155, 205, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 155, 205, 165, 215, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 165, 215, 175, 215, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 175, 215, 185, 205, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 185, 205, 185, 195, COLOR_CYAN );
   Map_LoadLinedef( linedef++, 185, 195, 175, 185, COLOR_CYAN );

   /*************************** SUBSECTORS ***************************/
   
   map->subsectors = (Subsector_t*)linedef;
   map->subsectorCount = 30;
   subsector = map->subsectors;
   lineseg = (Lineseg_t*)( (u8*)subsector + ( sizeof( Subsector_t ) * map->subsectorCount ) );

   subsector->linesegCount = 4;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[5], 30, 120, 60, 90 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[11], 60, 210, 60, 290 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[12], 60, 290, 0, 290 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[13], 0, 290, 0, 150 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[4], 20, 110, 30, 120 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[13], 0, 150, 0, 90 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[3], 40, 90, 20, 110 );
   subsector++;

   subsector->linesegCount = 3;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[6], 60, 90, 85, 90 );
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[7], 85, 90, 85, 130 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[10], 70, 210, 60, 210 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[9], 85, 225, 70, 210 );
   subsector++;

   subsector->linesegCount = 4;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[8], 85, 130, 95, 130 );
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[2], 155, 195, 155, 205 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[7], 155, 290, 150, 290 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[9], 90, 230, 85, 225 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[7], 150, 290, 90, 290 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[8], 90, 290, 90, 230 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[9], 95, 130, 95, 90 );
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[10], 95, 90, 110, 90 );
   subsector++;

   subsector->linesegCount = 4;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[13], 0, 90, 0, 40 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[14], 0, 40, 40, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 40, 0, 100, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[3], 50, 80, 40, 90 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[1], 100, 60, 100, 80 );
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[2], 100, 80, 50, 80 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 100, 0, 155, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[0], 110, 60, 100, 60 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[1].linedefs[11], 110, 90, 110, 60 );
   subsector++;

   subsector->linesegCount = 4;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[2], 190, 140, 250, 160 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[3], 260, 160.0f + ( 10.0f / 3.0f ), 260, 180 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[7], 260, 290, 185, 290 );
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[6], 185, 205, 185, 195 );
   subsector++;

   subsector->linesegCount = 3;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[4], 260, 180, 300, 200 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[5], 300, 200, 300, 250 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[6], 300, 250, 260, 290 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[7], 185, 195, 175, 185 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[0], 175, 185, 165, 185 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[1], 165, 185, 155, 195 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[3], 155, 205, 165, 215 );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[7], 185, 290, 155, 290 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[4], 165, 215, 175, 215 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[5].linedefs[5], 175, 215, 185, 205 );
   subsector++;

   subsector->linesegCount = 4;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[1], 300, 0, 300, 140.0f + ( 20.0f / 3.0f ) );
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[2], 300, 140.0f + ( 20.0f / 3.0f ), 260, 130.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[4], 250, 130, 230, 120.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( lineseg++, &map->sectors[3].linedefs[2], 260, 40, 270, 30 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[3], 260, 130.0f + ( 10.0f / 3.0f ), 260, 160.0f + ( 10.0f / 3.0f ) );
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[3], 250, 160, 250, 130 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[3].linedefs[1], 250, 30, 260, 40 );
   Map_LoadLineseg( lineseg++, &map->sectors[2].linedefs[3], 230, 70, 230, 60 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 230, 0, 280, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[3].linedefs[0], 260, 20, 250, 30 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 280, 0, 300, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[3].linedefs[3], 270, 30, 260, 20 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[2].linedefs[2], 170, 70, 230, 70 );
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[4], 230, 120.0f + ( 10.0f / 3.0f ), 220, 120 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[1], 190, 130, 190, 140 );
   subsector++;

   subsector->linesegCount = 1;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[4].linedefs[0], 220, 120, 190, 130 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 155, 0, 170, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[2].linedefs[1], 170, 60, 170, 70 );
   subsector++;

   subsector->linesegCount = 2;
   subsector->linesegs = lineseg;
   Map_LoadLineseg( lineseg++, &map->sectors[0].linedefs[0], 170, 0, 230, 0 );
   Map_LoadLineseg( lineseg++, &map->sectors[2].linedefs[0], 230, 60, 170, 60 );

   /*************************** BSP TREE ***************************/

   map->bspNodes = (BspNode_t*)lineseg;
   map->bspNodeCount = 59;

   // C5 (this is the root node)
   Map_LoadBspNode( &map->bspNodes[0], False, &map->sectors[5].linedefs[2], 0, 0, &map->bspNodes[24], &map->bspNodes[1] );

   // G1
   Map_LoadBspNode( &map->bspNodes[1], False, &map->sectors[1].linedefs[6], 0, &map->bspNodes[0], &map->bspNodes[17], &map->bspNodes[2] );

   // H1
   Map_LoadBspNode( &map->bspNodes[2], False, &map->sectors[1].linedefs[7], 0, &map->bspNodes[1], &map->bspNodes[12], &map->bspNodes[3] );

   // L0
   Map_LoadBspNode( &map->bspNodes[3], False, &map->sectors[0].linedefs[11], 0, &map->bspNodes[2], &map->bspNodes[9], &map->bspNodes[4] );

   // F1
   Map_LoadBspNode( &map->bspNodes[4], False, &map->sectors[1].linedefs[5], 0, &map->bspNodes[3], &map->bspNodes[6], &map->bspNodes[5] );

   // 1
   Map_LoadBspNode( &map->bspNodes[5], True, 0, &map->subsectors[0], &map->bspNodes[4], 0, 0 );

   // E1
   Map_LoadBspNode( &map->bspNodes[6], False, &map->sectors[1].linedefs[4], 0, &map->bspNodes[4], &map->bspNodes[8], &map->bspNodes[7] );

   // 2
   Map_LoadBspNode( &map->bspNodes[7], True, 0, &map->subsectors[1], &map->bspNodes[6], 0, 0 );

   // 3
   Map_LoadBspNode( &map->bspNodes[8], True, 0, &map->subsectors[2], &map->bspNodes[6], 0, 0 );

   // K0
   Map_LoadBspNode( &map->bspNodes[9], False, &map->sectors[0].linedefs[10], 0, &map->bspNodes[3], &map->bspNodes[11], &map->bspNodes[10] );

   // 4
   Map_LoadBspNode( &map->bspNodes[10], True, 0, &map->subsectors[3], &map->bspNodes[9], 0, 0 );

   // 5
   Map_LoadBspNode( &map->bspNodes[11], True, 0, &map->subsectors[4], &map->bspNodes[9], 0, 0 );

   // I1
   Map_LoadBspNode( &map->bspNodes[12], False, &map->sectors[1].linedefs[8], 0, &map->bspNodes[2], &map->bspNodes[16], &map->bspNodes[13] );

   // J0
   Map_LoadBspNode( &map->bspNodes[13], False, &map->sectors[0].linedefs[9], 0, &map->bspNodes[12], &map->bspNodes[15], &map->bspNodes[14] );

   // 6
   Map_LoadBspNode( &map->bspNodes[14], True, 0, &map->subsectors[5], &map->bspNodes[13], 0, 0 );

   // 7
   Map_LoadBspNode( &map->bspNodes[15], True, 0, &map->subsectors[6], &map->bspNodes[13], 0, 0 );

   // 8
   Map_LoadBspNode( &map->bspNodes[16], True, 0, &map->subsectors[7], &map->bspNodes[12], 0, 0 );

   // B1
   Map_LoadBspNode( &map->bspNodes[17], False, &map->sectors[1].linedefs[1], 0, &map->bspNodes[1], &map->bspNodes[21], &map->bspNodes[18] );

   // D1
   Map_LoadBspNode( &map->bspNodes[18], False, &map->sectors[1].linedefs[3], 0, &map->bspNodes[17], &map->bspNodes[20], &map->bspNodes[19] );

   // 9
   Map_LoadBspNode( &map->bspNodes[19], True, 0, &map->subsectors[8], &map->bspNodes[18], 0, 0 );

   // 10
   Map_LoadBspNode( &map->bspNodes[20], True, 0, &map->subsectors[9], &map->bspNodes[18], 0, 0 );

   // A1
   Map_LoadBspNode( &map->bspNodes[21], False, &map->sectors[1].linedefs[0], 0, &map->bspNodes[17], &map->bspNodes[23], &map->bspNodes[22] );

   // 11
   Map_LoadBspNode( &map->bspNodes[22], True, 0, &map->subsectors[10], &map->bspNodes[21], 0, 0 );

   // 12
   Map_LoadBspNode( &map->bspNodes[23], True, 0, &map->subsectors[11], &map->bspNodes[21], 0, 0 );

   // C4
   Map_LoadBspNode( &map->bspNodes[24], False, &map->sectors[4].linedefs[2], 0, &map->bspNodes[0], &map->bspNodes[40], &map->bspNodes[25] );

   // G5
   Map_LoadBspNode( &map->bspNodes[25], False, &map->sectors[5].linedefs[6], 0, &map->bspNodes[24], &map->bspNodes[29], &map->bspNodes[26] );

   // D0
   Map_LoadBspNode( &map->bspNodes[26], False, &map->sectors[0].linedefs[3], 0, &map->bspNodes[25], &map->bspNodes[28], &map->bspNodes[27] );

   // 13
   Map_LoadBspNode( &map->bspNodes[27], True, 0, &map->subsectors[12], &map->bspNodes[26], 0, 0 );

   // 14
   Map_LoadBspNode( &map->bspNodes[28], True, 0, &map->subsectors[13], &map->bspNodes[26], 0, 0 );

   // H5
   Map_LoadBspNode( &map->bspNodes[29], False, &map->sectors[5].linedefs[7], 0, &map->bspNodes[25], &map->bspNodes[31], &map->bspNodes[30] );

   // 15
   Map_LoadBspNode( &map->bspNodes[30], True, 0, &map->subsectors[14], &map->bspNodes[29], 0, 0 );

   // A5
   Map_LoadBspNode( &map->bspNodes[31], False, &map->sectors[5].linedefs[0], 0, &map->bspNodes[29], &map->bspNodes[33], &map->bspNodes[32] );

   // 16
   Map_LoadBspNode( &map->bspNodes[32], True, 0, &map->subsectors[15], &map->bspNodes[31], 0, 0 );

   // B5
   Map_LoadBspNode( &map->bspNodes[33], False, &map->sectors[5].linedefs[1], 0, &map->bspNodes[31], &map->bspNodes[35], &map->bspNodes[34] );

   // 17
   Map_LoadBspNode( &map->bspNodes[34], True, 0, &map->subsectors[16], &map->bspNodes[33], 0, 0 );

   // D5
   Map_LoadBspNode( &map->bspNodes[35], False, &map->sectors[5].linedefs[3], 0, &map->bspNodes[33], &map->bspNodes[37], &map->bspNodes[36] );

   // 18
   Map_LoadBspNode( &map->bspNodes[36], True, 0, &map->subsectors[17], &map->bspNodes[35], 0, 0 );

   // E5
   Map_LoadBspNode( &map->bspNodes[37], False, &map->sectors[5].linedefs[4], 0, &map->bspNodes[35], &map->bspNodes[39], &map->bspNodes[38] );

   // 19
   Map_LoadBspNode( &map->bspNodes[38], True, 0, &map->subsectors[18], &map->bspNodes[37], 0, 0 );

   // 20
   Map_LoadBspNode( &map->bspNodes[39], True, 0, &map->subsectors[19], &map->bspNodes[37], 0, 0 );

   // D2
   Map_LoadBspNode( &map->bspNodes[40], False, &map->sectors[2].linedefs[3], 0, &map->bspNodes[24], &map->bspNodes[50], &map->bspNodes[41] );

   // C3
   Map_LoadBspNode( &map->bspNodes[41], False, &map->sectors[3].linedefs[2], 0, &map->bspNodes[40], &map->bspNodes[45], &map->bspNodes[42] );

   // C0
   Map_LoadBspNode( &map->bspNodes[42], False, &map->sectors[0].linedefs[2], 0, &map->bspNodes[41], &map->bspNodes[44], &map->bspNodes[43] );

   // 21
   Map_LoadBspNode( &map->bspNodes[43], True, 0, &map->subsectors[20], &map->bspNodes[42], 0, 0 );

   // 22
   Map_LoadBspNode( &map->bspNodes[44], True, 0, &map->subsectors[21], &map->bspNodes[42], 0, 0 );

   // B3
   Map_LoadBspNode( &map->bspNodes[45], False, &map->sectors[3].linedefs[1], 0, &map->bspNodes[41], &map->bspNodes[47], &map->bspNodes[46] );

   // 23
   Map_LoadBspNode( &map->bspNodes[46], True, 0, &map->subsectors[22], &map->bspNodes[45], 0, 0 );

   // A3
   Map_LoadBspNode( &map->bspNodes[47], False, &map->sectors[3].linedefs[0], 0, &map->bspNodes[45], &map->bspNodes[49], &map->bspNodes[48] );

   // 24
   Map_LoadBspNode( &map->bspNodes[48], True, 0, &map->subsectors[23], &map->bspNodes[47], 0, 0 );

   // 25
   Map_LoadBspNode( &map->bspNodes[49], True, 0, &map->subsectors[24], &map->bspNodes[47], 0, 0 );

   // C2
   Map_LoadBspNode( &map->bspNodes[50], False, &map->sectors[2].linedefs[2], 0, &map->bspNodes[40], &map->bspNodes[56], &map->bspNodes[51] );

   // E4
   Map_LoadBspNode( &map->bspNodes[51], False, &map->sectors[4].linedefs[4], 0, &map->bspNodes[50], &map->bspNodes[53], &map->bspNodes[52] );

   // 26
   Map_LoadBspNode( &map->bspNodes[52], True, 0, &map->subsectors[25], &map->bspNodes[51], 0, 0 );

   // B4
   Map_LoadBspNode( &map->bspNodes[53], False, &map->sectors[4].linedefs[1], 0, &map->bspNodes[51], &map->bspNodes[55], &map->bspNodes[54] );

   // 27
   Map_LoadBspNode( &map->bspNodes[54], True, 0, &map->subsectors[26], &map->bspNodes[53], 0, 0 );

   // 28
   Map_LoadBspNode( &map->bspNodes[55], True, 0, &map->subsectors[27], &map->bspNodes[53], 0, 0 );

   // B2
   Map_LoadBspNode( &map->bspNodes[56], False, &map->sectors[2].linedefs[1], 0, &map->bspNodes[50], &map->bspNodes[58], &map->bspNodes[57] );

   // 29
   Map_LoadBspNode( &map->bspNodes[57], True, 0, &map->subsectors[28], &map->bspNodes[56], 0, 0 );

   // 30
   Map_LoadBspNode( &map->bspNodes[58], True, 0, &map->subsectors[29], &map->bspNodes[56], 0, 0 );
}

internal void Map_LoadLinedef( Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY, u16 color )
{
   linedef->start.x = startX;
   linedef->start.y = startY;
   linedef->end.x = endX;
   linedef->end.y = endY;
   linedef->color = color;
}

internal void Map_LoadLineseg( Lineseg_t* lineseg, Linedef_t* linedef, r32 startX, r32 startY, r32 endX, r32 endY )
{
   lineseg->linedef = linedef;
   lineseg->start.x = startX;
   lineseg->start.y = startY;
   lineseg->end.x = endX;
   lineseg->end.y = endY;
}

internal void Map_LoadBspNode( BspNode_t* node, Bool_t isLeaf, Linedef_t* linedef, Subsector_t* subsector, BspNode_t* parent, BspNode_t* leftChild, BspNode_t* rightChild )
{
   node->isLeaf = isLeaf;
   node->linedef = linedef;
   node->subsector = subsector;
   node->parent = parent;
   node->leftChild = leftChild;
   node->rightChild = rightChild;
}
